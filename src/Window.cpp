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
  cam = camera(screen_width, screen_height);
}

RaytraceWindow::~RaytraceWindow() {
  cam.~camera();
  CloseWindow();
}

void RaytraceWindow::draw() {
  // Camera
  cam.render(world);
}
