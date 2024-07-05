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
  cam = camera(screen_width, screen_height);
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
      std::vector<int> selected_elements =
          select_random_colors(total_elements, start_index, rays_to_send,
                               screen_width * screen_height * rays_per_pixel);

      // Calculate each pixel color
      // If we are using OpenMP, we can parallelize the loop
#ifdef USE_OPENMP
#pragma omp parallel for
#endif
      for (size_t f = 0; f < selected_elements.size(); f++) {
        const int index = selected_elements[f];
        const int j = index / screen_width / rays_per_pixel;
        const int i = index / rays_per_pixel % screen_width;

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
      Color pixel_color = {0, 0, 0, 255};
      for (size_t k = 0; k < rays_per_pixel; k++) {
        int index = (j * screen_width + i) * rays_per_pixel + k;
        if (index < screen_width * screen_height * rays_per_pixel) {
          const Color cp = pixels[index];
          pixel_color.r += cp.r / rays_per_pixel;
          pixel_color.g += cp.g / rays_per_pixel;
          pixel_color.b += cp.b / rays_per_pixel;
        }
      }

      // Assign the averaged color to the final pixel position
      image_pixels[j * screen_width + i] = pixel_color;
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
  total_elements.clear();
  total_elements.reserve(total_pixels);
  const int offset = GetRandomValue(0, total_pixels);
  for (size_t i = 0; i < total_pixels; i++) {
    total_elements[i] = shuffled_index_array[(i + offset) % total_pixels];
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

std::vector<int> RaytraceWindow::select_random_colors(
    std::vector<size_t>& indices, size_t& start_index, size_t num_to_select,
    size_t total_elements) {
  std::vector<int> result;
  result.reserve(num_to_select);

  int end_index = start_index + num_to_select;

  if (end_index > total_elements) {
    end_index = total_elements;
    num_to_select = end_index - start_index;
  }

  for (size_t i = start_index; i < end_index; ++i) {
    result.push_back(indices[i]);
  }

  start_index = end_index;

  return result;
}