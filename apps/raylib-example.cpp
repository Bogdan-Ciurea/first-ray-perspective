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

#include <iostream>

#include "objects/ObjectsList.hpp"
#include "objects/Sphere.hpp"
#include "raylib.h"
#include "utils.hpp"

double hit_sphere(const vec3& center, double radius, const ray& r) {
  vec3 oc = center - r.origin();
  auto a = r.direction().length_squared();
  auto h = r.direction().dot(oc);
  auto c = oc.length_squared() - radius * radius;
  auto discriminant = h * h - a * c;

  if (discriminant < 0) {
    return -1.0;
  } else {
    return (h - sqrt(discriminant)) / a;
  }
}

Color ray_color(const ray& r, ObjectsList& world) {
  hit_record rec;
  if (world.intersect(r, 0, infinity, rec)) {
    return (Color){(uchar)(rec.normal.x() * 256), (uchar)(rec.normal.y() * 256),
                   (uchar)(rec.normal.z() * 256)};
  }

  vec3 unit_direction = r.direction().unit_vector();
  auto a = 0.5 * (unit_direction.y() + 1.0);
  return (1.0 - a) * (Color){(uchar)(256), (uchar)(256), (uchar)(256)} +
         a * (Color){(uchar)(256 * 0.5), (uchar)(256 * 0.7), (uchar)(256)};
}

int main() {
  // Initialization
  //--------------------------------------------------------------------------------------
  auto aspect_ratio = 16.0 / 9.0;
  int screen_width = 1000;

  // Calculate the image height, and ensure that it's at least 1.
  int screen_height = int(screen_width / aspect_ratio);
  screen_height = (screen_height < 1) ? 1 : screen_height;

  // World

  ObjectsList world = ObjectsList();

  world.add(make_shared<Sphere>(vec3(0, 0, -1), 0.5));
  world.add(make_shared<Sphere>(vec3(1, 0, -1), 0.5));
  world.add(make_shared<Sphere>(vec3(0, -100.5, -1), 100));

  // Camera
  auto focal_length = 1.0;
  auto viewport_height = 2.0;
  auto viewport_width =
      viewport_height * (double(screen_width) / screen_height);
  auto camera_center = vec3(0, 0, 0);

  // Calculate the vectors across the horizontal and down the vertical viewport
  // edges.
  auto viewport_u = vec3(viewport_width, 0, 0);
  auto viewport_v = vec3(0, -viewport_height, 0);

  // Calculate the horizontal and vertical delta vectors from pixel to pixel.
  auto pixel_delta_u = viewport_u / screen_width;
  auto pixel_delta_v = viewport_v / screen_height;

  // Calculate the location of the upper left pixel.
  auto viewport_upper_left = camera_center - vec3(0, 0, focal_length) -
                             viewport_u / 2 - viewport_v / 2;
  auto pixel00_loc =
      viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);

  InitWindow(screen_width, screen_height, "First Ray Perspective");

  SetTargetFPS(60);  // Set our game to run at 60 frames-per-second
  //--------------------------------------------------------------------------------------

  // Main game loop
  while (!WindowShouldClose()) {  // Detect window close button or ESC key
    // Update
    //----------------------------------------------------------------------------------
    // Update your variables here
    //----------------------------------------------------------------------------------

    // Draw
    //----------------------------------------------------------------------------------
    BeginDrawing();

    ClearBackground(BLACK);

    for (int j = 0; j < screen_height; j++) {
      for (int i = 0; i < screen_width; i++) {
        auto pixel_center =
            pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v);
        auto ray_direction = pixel_center - camera_center;
        ray r(camera_center, ray_direction);

        Color pixel_color = ray_color(r, world);

        DrawPixel(i, j, pixel_color);
      }
    }

    EndDrawing();
    //----------------------------------------------------------------------------------
  }

  // De-Initialization
  //--------------------------------------------------------------------------------------
  CloseWindow();  // Close window and OpenGL context
  //--------------------------------------------------------------------------------------

  return 0;
}