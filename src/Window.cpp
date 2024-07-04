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

RaytraceWindow::RaytraceWindow(int screen_width, int screen_height,
                               const char* title)
    : screen_width(screen_width), screen_height(screen_height) {
  InitWindow(screen_width, screen_height, title);
  SetTargetFPS(60);
  pixels = new Color[screen_width * screen_height];
  cam = camera(screen_width, screen_height);
}

RaytraceWindow::~RaytraceWindow() {
  //    CloseWindow();
  //    cam.~camera();
  //    delete[] pixels;
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

// Calculate each pixel color
// If we are using OpenMP, we can parallelize the loop
#ifdef USE_OPENMP
#pragma omp parallel for
#endif
    for (int j = 0; j < screen_height; j++)
      for (int i = 0; i < screen_width; i++) {
        for (int k = 0; k < rays_per_pixel; k++) {
          const Color pixel_color = cam.send_ray(world, i, j);
          pixels[(j * screen_width + i) * rays_per_pixel + k] = pixel_color;
        }
      }

    BeginDrawing();

    // Clear the screen
    ClearBackground(BLACK);

    // Draw the pixels
    draw_pixels();

    EndDrawing();
  }

  // Why it works here and not in the destructor, only God knows...
  CloseWindow();
  cam.~camera();
  delete[] pixels;
}

void RaytraceWindow::draw_pixels() {
  for (int j = 0; j < screen_height; j++) {
    for (int i = 0; i < screen_width; i++) {
      Color pixel_color = Color{0, 0, 0, 255};
      for (int k = 0; k < rays_per_pixel; k++) {
        const Color cp = pixels[(j * screen_width + i) * rays_per_pixel + k];
        pixel_color.r += cp.r / rays_per_pixel;
        pixel_color.g += cp.g / rays_per_pixel;
        pixel_color.b += cp.b / rays_per_pixel;
      }
      DrawPixel(i, j, pixel_color);
    }
  }
}

void RaytraceWindow::reset_pixels() {
  const int total_pixels = screen_width * screen_height * rays_per_pixel;

  if (pixels) delete[] pixels;
  pixels = new Color[total_pixels];

  total_elements.clear();
  for (int i = 0; i < total_pixels; i++) total_elements.push_back(i);
  shuffle_indices(total_elements, 0);
}

double RaytraceWindow::get_ray_random_duration() {
  const double start_time = GetTime();
  cam.send_ray(world, GetRandomValue(0, screen_width),
               GetRandomValue(0, screen_height));
  return GetTime() - start_time;
}

void RaytraceWindow::shuffle_indices(std::vector<int>& indices,
                                     int start_index) {
  std::random_device rd;
  std::mt19937 gen(rd());

  for (int i = start_index; i < indices.size(); ++i) {
    std::uniform_int_distribution<> dis(i, indices.size() - 1);
    std::swap(indices[i], indices[dis(gen)]);
  }
}

std::vector<int> RaytraceWindow::select_random_colors(std::vector<int>& indices,
                                                      int& start_index,
                                                      int num_to_select,
                                                      int total_elements) {
  std::vector<int> result;
  result.reserve(num_to_select);

  int end_index = start_index + num_to_select;

  if (end_index > total_elements) {
    end_index = total_elements;
    num_to_select = end_index - start_index;
  }

  for (int i = start_index; i < end_index; ++i) {
    result.push_back(indices[i]);
  }

  start_index = end_index;

  return result;
}