#include "camera.hpp"

Color vec3_to_color(const vec3& v) {
  return create_color(255.99 * v.x(), 255.99 * v.y(), 255.99 * v.z(), 255);
}

camera::camera() {
  screen_height = 100;
  screen_width = 100;
  aspect_ratio = 1.0;
  initialize();
}
camera::camera(int image_width, int screen_height)
    : screen_height(screen_height), screen_width(image_width) {
  aspect_ratio = double(screen_width) / screen_height;
  initialize();
}

Color camera::send_ray(ObjectsList *world, const uint pixel_width,
                       const uint pixel_height) {
  auto pixel_center = pixel00_loc + (pixel_width * pixel_delta_u) +
                      (pixel_height * pixel_delta_v);
  auto ray_direction = pixel_center - center;
  ray r(center, ray_direction);
  return ray_color(r, world);
}

Color camera::ray_color(const ray& r, ObjectsList *world) {
  hit_record rec;
  if (world->intersect(r, 0, infinity, rec)) {
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
