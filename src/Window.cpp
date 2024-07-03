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

RaytraceWindow::RaytraceWindow(int screen_width, int screen_height,
                               const char* title)
    : screen_width(screen_width), screen_height(screen_height) {
  InitWindow(screen_width, screen_height, title);
  SetTargetFPS(60);
  pixels = new Color[screen_width * screen_height];
  cam = camera(screen_width, screen_height);
}

RaytraceWindow::~RaytraceWindow() {
  // cam.~camera();
  // CloseWindow();
  // delete[] pixels;
}

void RaytraceWindow::draw() {
  while (!WindowShouldClose()) {
    BeginDrawing();

    // Clear the screen
    ClearBackground(BLACK);

// Calculate each pixel color
// If we are using OpenMP, we can parallelize the loop
#ifdef USE_OPENMP
#pragma omp parallel for
#endif
    for (int j = 0; j < screen_height; j++) {
      for (int i = 0; i < screen_width; i++)
        pixels[j * screen_width + i] = cam.send_ray(world, i, j);
    }

    // Draw the pixels
    for (int j = 0; j < screen_height; j++)
      for (int i = 0; i < screen_width; i++)
        DrawPixel(i, j, pixels[j * screen_width + i]);

    EndDrawing();
  }
}
