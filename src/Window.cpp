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

RaytraceWindow::RaytraceWindow(const size_t screen_width,
                               const size_t screen_height, const char* title)
    : screen_width(screen_width), screen_height(screen_height) {
  InitWindow(screen_width, screen_height, title);
  SetTargetFPS(target_fps);

  shuffled_index_array =
      std::vector<size_t>(screen_width * screen_height * rays_per_pixel);
  std::iota(shuffled_index_array.begin(), shuffled_index_array.end(), 0);
  shuffle_indices(shuffled_index_array, 0);

  reset_pixels();
  cam = camera(screen_width, screen_height, 10);
}

RaytraceWindow::~RaytraceWindow() {
  CloseWindow();
  cam.~camera();
  delete[] pixels;
}

void RaytraceWindow::draw() {
  auto last = Clock::now();

  while (!WindowShouldClose()) {
    // ---- Calculate necessary information ----

    // Update state
    const auto now = Clock::now();
    float dt = std::chrono::duration_cast<Secondsf>(now - last).count();
    last = now;

    // Activate or deactivate camera movement using the space key
    if (IsKeyPressed(KEY_SPACE)) cam.is_moving = !cam.is_moving;
    if (IsKeyPressed(KEY_R)) reset_pixels();
    if (IsKeyPressed(KEY_P)) TakeScreenshot("screenshot.png");

    if (cam.update_state(dt)) reset_pixels();

    int rays_to_send = 0;
    {
      // Calculate the time it takes to send a ray
      const double ray_duration = get_ray_random_duration();

      // Calculate how many rays we can send in the time it takes to send one
      rays_to_send = (int)(1.0 / ray_duration / target_fps);

      // If we can't send at least one ray per frame, send one
      if (rays_to_send < 1) rays_to_send = 1;

#ifdef USE_OPENMP
      rays_to_send *= omp_get_max_threads();
#endif
    }

    const bool is_done =
        start_index >= screen_width * screen_height * rays_per_pixel;
    if (!is_done) {
      // Calculate which pixels to update
      std::vector<size_t> selected_elements =
          select_random_samples(total_samples, start_index, rays_to_send);

      // Calculate each pixel color
      // If we are using OpenMP, we can parallelize the loop
#ifdef USE_OPENMP
#pragma omp parallel for schedule(dynamic)
#endif
      for (size_t f = 0; f < selected_elements.size(); f++) {
        const size_t index = selected_elements[f];
        double j = index / rays_per_pixel / screen_width;
        double i = index / rays_per_pixel % screen_width;

        // Now randomise the ray a bit
        i += random_double() - 0.5;
        j += random_double() - 0.5;

        pixels[index] = cam.send_ray(world, i, j);
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
  for (size_t j = 0; j < screen_height; j++) {
    for (size_t i = 0; i < screen_width; i++) {
      vec4 pixel_color(0, 0, 0, 255);
      for (size_t k = 0; k < rays_per_pixel; k++) {
        int index = (j * screen_width + i) * rays_per_pixel + k;
        if (index < screen_width * screen_height * rays_per_pixel) {
          const Color sample = pixels[index];
          pixel_color += vec4(sample.r, sample.g, sample.b, 0);
        }
      }

      // Average the color
      pixel_color /= rays_per_pixel;
      pixel_color.e[3] = 255;

      // We already calculate everything in float, so we just do gamma
      // correction before putting it integer format.
      // Linear to Gamma: 255 * pow(linearvalue / 255, 1 / 2.2)
      pixel_color.e[0] = pow(pixel_color.r() / 255, 1 / 2.2f);
      pixel_color.e[1] = pow(pixel_color.g() / 255, 1 / 2.2f);
      pixel_color.e[2] = pow(pixel_color.b() / 255, 1 / 2.2f);

      // Assign the averaged color to the final pixel position
      image_pixels[j * screen_width + i] = pixel_color.to_color(255);
    }
  }

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
  const size_t total_pixels = screen_width * screen_height * rays_per_pixel;
  // All pixels related to the window
  if (!pixels) pixels = new Color[total_pixels];
  if (pixels == nullptr) {
    std::cerr << "Failed to allocate memory for pixels" << std::endl;
    exit(1);
  }
  // Make every pixel black
  for (size_t i = 0; i < total_pixels; i++) pixels[i] = Color{0, 0, 0, 255};

  // We already have a shuffled array of indices so we can copy it
  // We are going to copy the shuffled array of indices to the total elements
  // array but not exactly from the start but with a random offset
  // This way we can ensure that we are not going to send the same rays
  // every time
  total_samples.clear();
  total_samples.reserve(total_pixels);
  const int offset = GetRandomValue(0, total_pixels);
  for (size_t i = 0; i < total_pixels; i++) {
    total_samples[i] = shuffled_index_array[(i + offset) % total_pixels];
  }

  start_index = 0;
}

double RaytraceWindow::get_ray_random_duration() {
  auto start_time = Clock::now();
  cam.send_ray(world, GetRandomValue(0, screen_width),
               GetRandomValue(0, screen_height));
  return std::chrono::duration_cast<Secondsf>(Clock::now() - start_time)
      .count();
}

void RaytraceWindow::shuffle_indices(std::vector<size_t>& indices,
                                     size_t start_index) {
  std::random_device rd;
  std::mt19937 gen(rd());

  for (size_t i = start_index; i < indices.size(); ++i) {
    std::uniform_int_distribution<> dis(i, indices.size() - 1);
    std::swap(indices[i], indices[dis(gen)]);
  }
}

std::vector<size_t> RaytraceWindow::select_random_samples(
    std::vector<size_t>& indices, size_t& start_index, size_t num_to_select) {
  std::vector<size_t> result;
  result.reserve(num_to_select);

  size_t end_index = start_index + num_to_select;

  if (end_index > shuffled_index_array.size()) {
    end_index = shuffled_index_array.size();
    num_to_select = end_index - start_index;
  }

  for (size_t i = start_index; i < end_index; ++i) result.push_back(indices[i]);

  start_index = end_index;

  return result;
}