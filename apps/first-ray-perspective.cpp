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
#include "objects/sphere.hpp"

/**
 * @brief Scene containing three spheres and a ground.
 * The spheres are a dielectric, a metal, and a lambertian material.
 * The ground is a checker texture.
 */
hittable_list three_spheres() {
  hittable_list world;

  TraceLog(LOG_INFO, "Creating MATERIALS");
  auto material_ground = make_shared<checker_texture>(
      0.32f, vec3(.2f, .3f, .1f), vec3(.9f, .9f, .9f));
  auto material_center = make_shared<lambertian>(vec3(.1f, .2f, .5f));
  auto material_left = make_shared<dielectric>(1.0f / 1.5168f);
  auto material_right = make_shared<metal>(vec3(.8f, .6f, 0.2f), .5f);

  TraceLog(LOG_INFO, "Creating OBJECTS");
  world.add(make_shared<sphere>(vec3(.0f, -100.5f, -1.0f), 100.0f,
                                make_shared<lambertian>(material_ground)));
  world.add(make_shared<sphere>(vec3(.0f, .0f, -1.2f), .5f, material_center));
  world.add(make_shared<sphere>(vec3(-1.0f, .0f, -1.0f), .5f, material_left));
  world.add(make_shared<sphere>(vec3(1.0f, .0f, -1.0f), .5f, material_right));

  TraceLog(LOG_INFO, "Creating BVH");
  return hittable_list(make_shared<bvh_node>(world));
}

int main() {
  auto aspect_ratio = 16.0 / 9.0;
  int screen_width = 1000;

  // Calculate the image height, and ensure that it's at least 1.
  int screen_height = int(screen_width / aspect_ratio);
  screen_height = (screen_height < 1) ? 1 : screen_height;

  RaytraceWindow window =
      RaytraceWindow(screen_width, screen_height, "First Ray Perspective");

  // World
  hittable_list world;

  switch (1) {
    case 1:
      world = three_spheres();
      break;
    default:
      break;
  }

  window.set_world(&world);

  window.draw();

  return 0;
}
