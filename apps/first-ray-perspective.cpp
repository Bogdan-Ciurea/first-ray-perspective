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
#include "objects/quad.hpp"
#include "objects/sphere.hpp"

/**
 * @brief Scene containing three spheres and a ground.
 * The spheres are a dielectric, a metal, and a lambertian material.
 * The ground is a checker texture.
 */
hittable_list three_spheres(shared_ptr<camera> cam) {
  hittable_list world;
  cam->background_color = vec3(0.7f, 0.8f, 1.0f);

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
  world.add(make_shared<sphere>(vec3(.0f, -.0f, -1.0f), .5f, material_center));
  world.add(make_shared<sphere>(vec3(-1.0f, .0f, -1.0f), .5f, material_left));
  world.add(make_shared<sphere>(vec3(1.0f, .0f, -1.0f), .5f, material_right));

  TraceLog(LOG_INFO, "Creating BVH");
  return hittable_list(make_shared<bvh_node>(world));
}

/**
 * @brief Scene containing a sphere with an earth texture
 */
hittable_list earth(shared_ptr<camera> cam) {
  hittable_list world;
  cam->background_color = vec3(0.7f, 0.8f, 1.0f);

  TraceLog(LOG_INFO, "Loading TEXTURES");
  auto earth_texture = make_shared<image_texture>("earthmap.png");

  TraceLog(LOG_INFO, "Creating MATERIALS");
  auto earth_surface = make_shared<lambertian>(earth_texture);

  TraceLog(LOG_INFO, "Creating OBJECTS");
  auto globe = make_shared<sphere>(vec3(.0f, .0f, -4.f), 2.f, earth_surface);

  world.add(globe);

  TraceLog(LOG_INFO, "Creating BVH");
  return hittable_list(make_shared<bvh_node>(world));
}

hittable_list perlin_spheres(shared_ptr<camera> cam) {
  hittable_list world;
  cam->background_color = vec3(0.7f, 0.8f, 1.0f);

  TraceLog(LOG_INFO, "Creating MATERIALS");
  auto perlin_texture = make_shared<noise_texture>(4.f);
  auto perlin_surface = make_shared<lambertian>(perlin_texture);

  TraceLog(LOG_INFO, "Creating OBJECTS");
  world.add(
      make_shared<sphere>(vec3(0.f, -1000.f, 0.f), 1000.f, perlin_surface));
  world.add(make_shared<sphere>(vec3(.0f, 2.f, -1.f), 2.f, perlin_surface));

  TraceLog(LOG_INFO, "Creating BVH");
  return hittable_list(make_shared<bvh_node>(world));
}

hittable_list coloured_box(shared_ptr<camera> cam) {
  hittable_list world;
  cam->background_color = vec3(0.7f, 0.8f, 1.0f);
  cam->movement_per_second = 10.0f;

  // Materials
  TraceLog(LOG_INFO, "Creating MATERIALS");
  auto left_red = make_shared<lambertian>(vec3(1.0f, .2f, .2f));
  auto back_green = make_shared<lambertian>(vec3(.2f, 1.0f, .2f));
  auto right_blue = make_shared<lambertian>(vec3(.2f, .2f, 1.0f));
  auto upper_orange = make_shared<lambertian>(vec3(1.0f, .5f, .0f));
  auto lower_teal = make_shared<lambertian>(vec3(.2f, .8f, .8f));

  // Quads
  TraceLog(LOG_INFO, "Creating OBJECTS");
  world.add(make_shared<quad>(vec3(-3, -2, -3), vec3(0, 0, -4), vec3(0, 4, 0),
                              left_red));
  world.add(make_shared<quad>(vec3(-2, -2, -8), vec3(4, 0, 0), vec3(0, 4, 0),
                              back_green));
  world.add(make_shared<quad>(vec3(3, -2, -7), vec3(0, 0, 4), vec3(0, 4, 0),
                              right_blue));
  world.add(make_shared<quad>(vec3(-2, 3, -7), vec3(4, 0, 0), vec3(0, 0, 4),
                              upper_orange));
  world.add(make_shared<quad>(vec3(-2, -3, -3), vec3(4, 0, 0), vec3(0, 0, -4),
                              lower_teal));

  TraceLog(LOG_INFO, "Creating BVH");
  return hittable_list(make_shared<bvh_node>(world));
}

/**
 * @brief function that creates a cornell box
 * NOTE: The function does not create a BVH node
 *
 * @return hittable_list The list of objects in the scene
 */
hittable_list cornell_box() {
  hittable_list world;

  // Materials
  TraceLog(LOG_INFO, "Creating MATERIALS");
  auto ivory = make_shared<lambertian>(vec3(0.4f, 0.4f, 0.3f));
  auto red_rubber = make_shared<lambertian>(vec3(0.3f, 0.1f, 0.1f));
  auto green_rubber = make_shared<lambertian>(vec3(0.3f, 0.4f, 0.1f));
  auto light = make_shared<diffuse_light>(vec3(15.f, 15.f, 15.f));

  // Quads
  TraceLog(LOG_INFO, "Creating OBJECTS");
  // Left wall (100 units wide)
  world.add(make_shared<quad>(vec3(-50, -50, -50), vec3(0, 0, -100),
                              vec3(0, 100, 0), red_rubber));
  // Back wall (100 units wide)
  world.add(make_shared<quad>(vec3(-50, -50, -150), vec3(100, 0, 0),
                              vec3(0, 100, 0), ivory));
  // Right wall (100 units wide)
  world.add(make_shared<quad>(vec3(50, -50, -150), vec3(0, 0, 100),
                              vec3(0, 100, 0), green_rubber));
  // Ceiling (100 units wide)
  world.add(make_shared<quad>(vec3(-50, 50, -150), vec3(100, 0, 0),
                              vec3(0, 0, 100), ivory));
  // Light (as a 50x50 centered square on the ceiling)
  world.add(make_shared<quad>(vec3(-25, 49.99, -125), vec3(50, 0, 0),
                              vec3(0, 0, 50),
                              light));  // Centered light source
  // Floor (100 units wide)
  world.add(make_shared<quad>(vec3(-50, -50, -50), vec3(100, 0, 0),
                              vec3(0, 0, -100), ivory));

  return world;
}

int main() {
  SetTraceLogLevel(LOG_DEBUG);
  auto aspect_ratio = 16.0 / 9.0;
  int screen_width = 1000;

  // Calculate the image height, and ensure that it's at least 1.
  int screen_height = int(screen_width / aspect_ratio);
  screen_height = (screen_height < 1) ? 1 : screen_height;

  shared_ptr<camera> cam = make_shared<camera>(screen_width, screen_height, 50);

  RaytraceWindow window =
      RaytraceWindow(screen_width, screen_height, "First Ray Perspective", cam);

  // World
  hittable_list world;

  switch (5) {
    case 1:
      world = three_spheres(cam);
      break;
    case 2:
      world = earth(cam);
      break;
    case 3:
      world = perlin_spheres(cam);
      break;
    case 4:
      world = coloured_box(cam);
      break;
    case 5:
      world = cornell_box();
      break;
    default:
      break;
  }

  window.set_world(&world);

  window.draw();

  return 0;
}
