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
  ObjectsList world;

  TraceLog(LOG_INFO, "Creating MATERIALS");
  auto material_ground = make_shared<lambertian>(vec3(0.8, 0.8, 0.0));
  auto material_center = make_shared<lambertian>(vec3(0.1, 0.2, 0.5));
  auto material_left = make_shared<dielectric>(1.0 / 1.33);
  auto material_right = make_shared<metal>(vec3(0.8, 0.6, 0.2), .5);

  TraceLog(LOG_INFO, "Creating OBJECTS");
  world.add(
      make_shared<Sphere>(vec3(0.0, -100.5, -1.0), 100.0, material_ground));
  world.add(make_shared<Sphere>(vec3(0.0, 0.0, -1.2), 0.5, material_center));
  world.add(make_shared<Sphere>(vec3(-1.0, 0.0, -1.0), 0.5, material_left));
  world.add(make_shared<Sphere>(vec3(1.0, 0.0, -1.0), 0.5, material_right));

  RaytraceWindow window =
      RaytraceWindow(screen_width, screen_height, "First Ray Perspective");

  window.set_world(&world);

  window.draw();

  return 0;
}
