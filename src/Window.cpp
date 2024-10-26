/**
 * @file Window.cpp
 * @author Bogdan Ciurea (ciureabogdanalexandru@gmail.com)
 * @brief  Implementing the RaytraceWindow class
 * @version 0.1
 * @date 2024-04-27
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "Window.hpp"

#include <chrono>

RaytraceWindow::RaytraceWindow(const int screen_width, const int screen_height,
                               const char* title, const shared_ptr<camera> cam)
    : screen_width(screen_width), screen_height(screen_height), cam(cam) {
  InitWindow(screen_width, screen_height, title);
  SetTargetFPS(target_fps);

  shuffled_index_array = std::vector<int>(screen_width * screen_height);
  std::iota(shuffled_index_array.begin(), shuffled_index_array.end(), 0);
  shuffle_indices(shuffled_index_array, 0);

  reset_pixels();
}

RaytraceWindow::~RaytraceWindow() { CloseWindow(); }

void RaytraceWindow::draw() {
  auto last = Clock::now();

  while (!WindowShouldClose()) {
    // ---- Calculate necessary information ----

    // Update state
    const auto now = Clock::now();
    float dt = std::chrono::duration_cast<Secondsf>(now - last).count();
    last = now;

    // Activate or deactivate camera movement using the space key
    if (IsKeyPressed(KEY_SPACE)) cam->is_moving = !cam->is_moving;
    if (IsKeyPressed(KEY_R)) reset_pixels();
    if (IsKeyPressed(KEY_P)) TakeScreenshot("screenshot.png");

    if (cam->update_state(dt)) reset_pixels();

    int rays_to_send = 0;
    {
      // Calculate the time it takes to send a ray
      const float ray_duration = get_ray_random_duration();

      // Calculate how many rays we can send in the time it takes to send one
      rays_to_send = (int)(1.0 / ray_duration / target_fps);

      // If we can't send at least one ray per frame, send one
      if (rays_to_send < 1) rays_to_send = 1;

#ifdef USE_OPENMP
      rays_to_send *= omp_get_max_threads();
#endif
    }

    const bool is_done = current_renders >= max_renders + 1;
    if (!is_done) {
      const int end_index =
          start_index + rays_to_send >= shuffled_index_array.size()
              ? (int)shuffled_index_array.size()
              : start_index + rays_to_send;
// Calculate each pixel color
// If we are using OpenMP, we can parallelize the loop
#ifdef USE_OPENMP
#pragma omp parallel for schedule(dynamic)
#endif
      for (int f = start_index; f < end_index; f++) {
        const int index = shuffled_index_array[f];
        float j = index / screen_width + random_float() - 0.5f;
        float i = index % screen_width + random_float() - 0.5f;

        vec3 color = cam->send_ray(world, i, j);

        // We already calculate everything in float, so we just do gamma
        // correction before putting it integer format
        // Linear to Gamma: 255 * pow(linearvalue / 255 (if in Color), 1 / 2.2)
        color.e[0] = pow(color.r(), 1 / 2.2f);
        color.e[1] = pow(color.g(), 1 / 2.2f);
        color.e[2] = pow(color.b(), 1 / 2.2f);

        const vec3 old_color =
            vec3(pixels[index].r, pixels[index].g, pixels[index].b) / 255.0f;

        const float weight = 1.0f / (current_renders + 1);
        color = (1 - weight) * old_color + weight * color;

        pixels[index] = color.to_color(255);
      }

      start_index = end_index;

      if (start_index >= shuffled_index_array.size()) {
        start_index = 0;
        current_renders++;

        TraceLog(LOG_INFO, "Render %d/%d", current_renders, max_renders);
      }
    }

    BeginDrawing();

    // Clear the screen
    ClearBackground(BLACK);

    // Generate the texture with the newly calculated pixels if the process is
    // not done or draw the texture if it is
    !is_done ? draw_pixels() : DrawTexture(texture, 0, 0, WHITE);

    EndDrawing();
  }
}

void RaytraceWindow::draw_pixels() {
  // Generate an image with a blank (transparent) background
  Image image = GenImageColor(screen_width, screen_height, BLANK);
  Color* image_pixels = (Color*)image.data;

  // Loop through each pixel
  for (int j = 0; j < screen_height; j++)
    for (int i = 0; i < screen_width; i++)
      image_pixels[j * screen_width + i] = pixels[j * screen_width + i];

  SetTraceLogLevel(LOG_NONE);  // Disable logging as it will be spammed
  // Load texture from the updated image data
  if (texture.id > 0)
    UnloadTexture(texture);  // Unload previous texture if exists

  texture = LoadTextureFromImage(image);
  // Unload image from CPU memory
  UnloadImage(image);
  // Draw the texture on the screen
  DrawTexture(texture, 0, 0, WHITE);
  SetTraceLogLevel(LOG_ALL);  // Reset log level
}

void RaytraceWindow::reset_pixels() {
  const int total_pixels = screen_width * screen_height;
  // All pixels related to the window
  if (pixels.size() != total_pixels) pixels.resize(total_pixels);

  // Make every pixel black
  for (int i = 0; i < total_pixels; i++) pixels[i] = Color{0, 0, 0, 255};

  start_index = 0;
  current_renders = 0;
}

float RaytraceWindow::get_ray_random_duration() {
  auto start_time = Clock::now();
  cam->send_ray(world, (float)GetRandomValue(0, screen_width),
                (float)GetRandomValue(0, screen_height));
  return std::chrono::duration_cast<Secondsf>(Clock::now() - start_time)
      .count();
}

void RaytraceWindow::shuffle_indices(std::vector<int>& indices,
                                     int start_index) {
  std::random_device rd;
  std::mt19937 gen(rd());

  for (size_t i = start_index; i < indices.size(); ++i) {
    std::uniform_int_distribution<> dis((int)i, (int)indices.size() - 1);
    std::swap(indices[i], indices[dis(gen)]);
  }
}
