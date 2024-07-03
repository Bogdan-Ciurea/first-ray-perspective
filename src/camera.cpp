#include "camera.hpp"

Color vec3_to_color(const vec3& v) {
  return create_color(255.99 * v.x(), 255.99 * v.y(), 255.99 * v.z(), 255);
}

camera::camera() {
  screen_height = 100;
  screen_width = 100;
  aspect_ratio = 1.0;
  pixels = new Color[screen_width * screen_height];
  initialize();
}
camera::camera(int image_width, int screen_height)
    : screen_height(screen_height), screen_width(image_width) {
  aspect_ratio = double(screen_width) / screen_height;
  pixels = new Color[screen_width * screen_height];
  initialize();
}

camera::~camera() { delete[] pixels; }

void camera::render(ObjectsList& world) {
  while (!WindowShouldClose()) {
    BeginDrawing();

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
        auto ray_direction = pixel_center - center;
        ray r(center, ray_direction);
        pixels[j * screen_width + i] = ray_color(r, world);
      }
    }

    // Draw the pixels
    for (int j = 0; j < screen_height; j++) {
      for (int i = 0; i < screen_width; i++) {
        Color color = pixels[j * screen_width + i];
        DrawPixel(i, j, color);
      }
    }

    EndDrawing();
  }
}

Color camera::ray_color(const ray& r, ObjectsList& world) {
  hit_record rec;
  if (world.intersect(r, 0, infinity, rec)) {
    return vec3_to_color(0.5f * vec3(rec.normal.x() + 1, rec.normal.y() + 1,
                                     rec.normal.z() + 1));
  }

  vec3 unit_direction = unit_vector(r.direction());
  float t = 0.5 * (unit_direction.y() + 1.0);
  return vec3_to_color((float)(1.0 - t) * vec3(1.0, 1.0, 1.0) +
                       t * vec3(0.5, 0.7, 1.0));
}

void camera::initialize() {
  center = vec3(0, 0, 0);

  // Determine viewport dimensions.
  auto focal_length = 1.0;
  auto viewport_height = 2.0;
  auto viewport_width = viewport_height * aspect_ratio;

  // Calculate the vectors across the horizontal and down the vertical viewport
  // edges.
  auto viewport_u = vec3(viewport_width, 0, 0);
  auto viewport_v = vec3(0, -viewport_height, 0);

  // Calculate the horizontal and vertical delta vectors from pixel to pixel.
  pixel_delta_u = viewport_u / screen_width;
  pixel_delta_v = viewport_v / screen_height;

  // Calculate the location of the upper left pixel.
  auto viewport_upper_left =
      center - vec3(0, 0, focal_length) - viewport_u / 2 - viewport_v / 2;
  pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);
}