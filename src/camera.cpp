#include "camera.hpp"

camera::camera() {
  screen_height = 100;
  screen_width = 100;
  max_depth = 10;
  initialize();
}

camera::camera(const size_t image_width, const size_t screen_height,
               const size_t max_depth)
    : screen_height(screen_height),
      screen_width(image_width),
      max_depth(max_depth) {
  initialize();
}

Color camera::send_ray(ObjectsList* world, const double pixel_width,
                       const double pixel_height) {
  auto pixel_center = pixel00_loc + (pixel_width * pixel_delta_u) +
                      (pixel_height * pixel_delta_v);
  auto ray_origin =
      (defocus_angle <= 0) ? camera_position : defocus_disk_sample();
  auto ray_direction = pixel_center - camera_position;
  ray r(ray_origin, ray_direction);
  return ray_color(r, world, max_depth).to_color(255);
}

vec3 camera::ray_color(ray& r, ObjectsList* world, const size_t depth) {
  if (depth <= 0) {
    return vec3(0, 0, 0);
  }

  hit_record rec;
  if (world->intersect(r, std::numeric_limits<float>::epsilon(), infinity,
                       rec)) {
    ray scattered;
    vec3 attenuation;
    // If the ray scatters, recursively call the function
    if (rec.mat_ptr->scatter(r, rec, attenuation, scattered))
      return attenuation * ray_color(scattered, world, depth - 1);

    // If the ray does not scatter, return black
    vec3(0, 0, 0);
  }

  vec3 unit_direction = unit_vector(r.direction());
  float t = 0.5 * (unit_direction.y() + 1.0);
  return (float)(1.0 - t) * vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);
}

void camera::initialize() {
  auto theta = vfov * DEG2RAD;
  auto h = tan(theta / 2);
  auto viewport_height = 2 * h * focus_dist;
  auto viewport_width =
      viewport_height * (double(screen_width) / screen_height);

  w = unit_vector(camera_position - look_at_point);
  u = unit_vector(cross(vup, w));
  v = cross(w, u);

  vec3 viewport_u = viewport_width * u;
  vec3 viewport_v = viewport_height * -v;

  pixel_delta_u = viewport_u / screen_width;
  pixel_delta_v = viewport_v / screen_height;

  auto viewport_upper_left =
      camera_position - (focus_dist * w) - viewport_u / 2 - viewport_v / 2;
  pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);

  // Calculate the camera defocus disk basis vectors.
  auto defocus_radius = focus_dist * tan(DEG2RAD * defocus_angle / 2);
  defocus_disk_u = u * defocus_radius;
  defocus_disk_v = v * defocus_radius;
}

bool camera::update_state(float dt) {
  if (!is_moving) {
    return false;
  }

  bool moved = update_camera_orientation();

  const float speed =
      movement_per_second * dt * (IsKeyDown(KEY_LEFT_SHIFT) ? 5.0 : 1.0);

  vec3 front = unit_vector(look_at_point - camera_position);
  vec3 right = unit_vector(cross(front, vup));

  if (IsKeyDown(KEY_W)) {
    camera_position += front * speed;
    moved = true;
  }
  if (IsKeyDown(KEY_S)) {
    camera_position -= front * speed;
    moved = true;
  }
  if (IsKeyDown(KEY_A)) {
    camera_position -= right * speed;
    moved = true;
  }
  if (IsKeyDown(KEY_D)) {
    camera_position += right * speed;
    moved = true;
  }

  if (moved) {
    look_at_point =
        camera_position + front * (look_at_point - camera_position).length();
    initialize();
  }

  return moved;
}

bool camera::update_camera_orientation() {
  const Vector2 mouse_pos = GetMouseDelta();

  if (mouse_pos.x == 0 && mouse_pos.y == 0) {
    return false;
  }

  const float sensitivity = 0.1f;
  const float x_offset = mouse_pos.x * sensitivity;
  const float y_offset = mouse_pos.y * sensitivity;

  yaw += x_offset;
  pitch += y_offset;

  if (pitch > 89.0f) pitch = 89.0f;
  if (pitch < -89.0f) pitch = -89.0f;

  vec3 direction;
  direction[0] = cosf(yaw * DEG2RAD) * cosf(pitch * DEG2RAD);
  direction[1] = -sinf(pitch * DEG2RAD);
  direction[2] = sinf(yaw * DEG2RAD) * cosf(pitch * DEG2RAD);

  look_at_point = camera_position + unit_vector(direction);

  return true;
}

vec3 camera::defocus_disk_sample() const {
  auto p = random_in_unit_disk();
  return camera_position + (p[0] * defocus_disk_u) + (p[1] * defocus_disk_v);
}