/**
 * @file first-ray-perspective.cpp
 * @author Bogdan Ciurea (ciureabogdanalexandru@gmail.com)
 * @brief Implementing the first ray tracing algorithm with perspective
 * projection
 * @version 0.1
 * @date 2024-04-14
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "Window.hpp"
#include "objects/Sphere.hpp"

int main() {
  auto aspect_ratio = 16.0 / 9.0;
  int screen_width = 1000;

  // Calculate the image height, and ensure that it's at least 1.
  int screen_height = int(screen_width / aspect_ratio);
  screen_height = (screen_height < 1) ? 1 : screen_height;

  // World
  std::cout << "Creating world" << std::endl;
  ObjectsList world;

  world.add(make_shared<Sphere>(vec3(0, 0, -1), 0.5));
  world.add(make_shared<Sphere>(vec3(1, 0, -1), 0.5));
  world.add(make_shared<Sphere>(vec3(0, -100.5, -1), 100));

  RaytraceWindow window =
      RaytraceWindow(screen_width, screen_height, "First Ray Perspective");

  window.set_world(&world);

  window.draw();

  window.~RaytraceWindow();
  //  world.~ObjectsList(); // TODO: might want to change shared pointers to
  //  normal pointers

  return 0;
}
