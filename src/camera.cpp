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

Color camera::send_ray(ObjectsList* world, const double pixel_width,
                       const double pixel_height) {
  auto pixel_center = pixel00_loc + (pixel_width * pixel_delta_u) +
                      (pixel_height * pixel_delta_v);
  auto ray_direction = pixel_center - camera_position;
  ray r(camera_position, ray_direction);
  return ray_color(r, world);
}

Color camera::ray_color(const ray& r, ObjectsList* world) {
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
  auto focal_length = (camera_position - look_at_point).length();
  auto theta = vfov * DEG2RAD;
  auto h = tan(theta / 2);
  auto viewport_height = 2 * h * focal_length;
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
      camera_position - (focal_length * w) - viewport_u / 2 - viewport_v / 2;
  pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);
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