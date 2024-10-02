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
  auto material_ground = make_shared<lambertian>(vec3(.8f, .8f, .0f));
  auto material_center = make_shared<lambertian>(vec3(.1f, .2f, .5f));
  auto material_left = make_shared<dielectric>(1.0f / 1.33f);
  auto material_right = make_shared<metal>(vec3(.8f, .6f, 0.2f), .5f);

  TraceLog(LOG_INFO, "Creating OBJECTS");
  world.add(
      make_shared<Sphere>(vec3(.0f, -100.5f, -1.0f), 100.0f, material_ground));
  world.add(make_shared<Sphere>(vec3(.0f, .0f, -1.2f), .5f, material_center));
  world.add(make_shared<Sphere>(vec3(-1.0f, .0f, -1.0f), .5f, material_left));
  world.add(make_shared<Sphere>(vec3(1.0f, .0f, -1.0f), .5f, material_right));

  RaytraceWindow window =
      RaytraceWindow(screen_width, screen_height, "First Ray Perspective");

  window.set_world(&world);

  window.draw();

  return 0;
}
