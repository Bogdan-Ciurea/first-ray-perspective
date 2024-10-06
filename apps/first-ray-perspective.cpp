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

  TraceLog(LOG_INFO, "Loading TEXTURES");
  auto material_ground = make_shared<checker_texture>(
      0.32f, vec3(.2f, .3f, .1f), vec3(.9f, .9f, .9f));

  TraceLog(LOG_INFO, "Creating MATERIALS");
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

/**
 * @brief Scene containing a sphere with an earth texture
 */
hittable_list earth() {
  hittable_list world;

  TraceLog(LOG_INFO, "Loading TEXTURES");
  auto earth_texture = make_shared<image_texture>("earthmap.png");

  TraceLog(LOG_INFO, "Creating MATERIALS");
  auto earth_surface = make_shared<lambertian>(earth_texture);

  TraceLog(LOG_INFO, "Creating OBJECTS");
  auto globe = make_shared<sphere>(vec3(.0f, .0f, -4.f), 2.f, earth_surface);

  world.add(globe);

  return world;
}

hittable_list perlin_spheres() {
  hittable_list world;

  auto perlin_texture = make_shared<noise_texture>(4.f);
  auto perlin_surface = make_shared<lambertian>(perlin_texture);

  world.add(
      make_shared<sphere>(vec3(0.f, -1000.f, 0.f), 1000.f, perlin_surface));
  world.add(make_shared<sphere>(vec3(.0f, 2.f, -1.f), 2.f, perlin_surface));

  return world;
}

int main() {
  SetTraceLogLevel(LOG_DEBUG);
  auto aspect_ratio = 16.0 / 9.0;
  int screen_width = 1000;

  // Calculate the image height, and ensure that it's at least 1.
  int screen_height = int(screen_width / aspect_ratio);
  screen_height = (screen_height < 1) ? 1 : screen_height;

  RaytraceWindow window =
      RaytraceWindow(screen_width, screen_height, "First Ray Perspective");

  // World
  hittable_list world;

  switch (3) {
    case 1:
      world = three_spheres();
      break;
    case 2:
      world = earth();
      break;
    case 3:
      world = perlin_spheres();
      break;
    default:
      break;
  }

  window.set_world(&world);

  window.draw();

  return 0;
}
