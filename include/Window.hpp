/**
 * @file Window.hpp
 * @author Bogdan Ciurea (ciureabogdanalexandru@gmail.com)
 * @brief Declaration of the RaytraceWindow class
 * @version 0.1
 * @date 2024-04-19
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <omp.h>

#include "camera.hpp"
#include "objects/ObjectsList.hpp"

class RaytraceWindow {
 public:
  RaytraceWindow(int screen_width, int screen_height, const char* title);

  ~RaytraceWindow();

  void draw();
  void set_world(ObjectsList *world) { this->world = world; }

 private:
  int screen_width;
  int screen_height;
  ObjectsList* world;
  camera cam;
  Color* pixels;
};

#endif  // WINDOW_HPP
