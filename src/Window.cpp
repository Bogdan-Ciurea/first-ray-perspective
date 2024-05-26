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

#include "utils.hpp"

RaytraceWindow::RaytraceWindow(int screen_width, int screen_height,
                               const char* title)
    : screen_width(screen_width), screen_height(screen_height) {
  InitWindow(screen_width, screen_height, title);
  SetTargetFPS(60);

  // Allocate memory for the pixels
  pixels = (Color*)malloc(screen_width * screen_height * sizeof(Color));
}

Color ray_color(const ray& r, ObjectsList& world) {
  hit_record rec;
  if (world.intersect(r, 0, infinity, rec)) {
    return Color{(uchar)(rec.normal.x() * 256), (uchar)(rec.normal.y() * 256),
                   (uchar)(rec.normal.z() * 256), };
  }

  vec3 unit_direction = r.direction().unit_vector();
  auto a = 0.5 * (unit_direction.y() + 1.0);
  return (1.0 - a) * Color{(uchar)(256), (uchar)(256), (uchar)(256)} +
         a * Color{(uchar)(256 * 0.5), (uchar)(256 * 0.7), (uchar)(256)};
}

void RaytraceWindow::draw() {
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

  while (!WindowShouldClose()) {
    begin_drawing();

    // Clear the screen
    ClearBackground(BLACK);

// Calculate each pixel color
// If we are using OpenMP, we can parallelize the loop
#ifdef USE_OPENMP
#pragma omp parallel for
#endif
    for (int j = 0; j < screen_height; j++) {
      for (int i = 0; i < screen_width; i++) {
        auto pixel_center =
            pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v);
        auto ray_direction = pixel_center - camera_center;
        ray r(camera_center, ray_direction);

        Color pixel_color = ray_color(r, world);
        pixels[j * screen_width + i] = pixel_color;
      }
    }

    // Draw the pixels
    for (int j = 0; j < screen_height; j++) {
      for (int i = 0; i < screen_width; i++) {
        Color color = pixels[j * screen_width + i];
        draw_pixel(i, j, color);
      }
    }

    end_drawing();
  }
}
