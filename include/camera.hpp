/**
 * @file camera.hpp
 * @author Bogdan Ciurea
 * @brief
 * @version 0.1
 * @date 2024-07-03
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef CAMERA_H
#define CAMERA_H

#include "objects/ObjectsList.hpp"

Color vec3_to_color(const vec3& v);

class camera {
 public:
  camera();
  camera(int image_width, int screen_height);

  /**
   * @brief Destroy the camera object
   *
   */
  ~camera() {}

  Color send_ray(ObjectsList* world, const uint pixel_width,
                 const uint pixel_height);

  double aspect_ratio = 1.0;  // Ratio of image width over height
  int screen_width = 100;     // Rendered image width in pixel count
  bool is_moving = false;     // Camera movement flag

  /**
   * @brief Updates the position of the camera
   *
   * @param dt delta time
   *
   * @return true if the camera was updated, false otherwise
   */
  bool update_state(float dt);

 private:
  int screen_height;  // Rendered image height

  vec3 pixel00_loc;    // Location of pixel 0, 0
  vec3 pixel_delta_u;  // Offset to pixel to the right
  vec3 pixel_delta_v;  // Offset to pixel below

  float vfov = 90;                       // Vertical view angle (field of view)
  vec3 camera_position = vec3(0, 0, 0);  // Camera center
  vec3 look_at_point = vec3(0, 0, -1);   // Camera view direction
  vec3 vup = vec3(0, 1, 0);              // Camera up position
  vec3 u, v, w;                          // Camera frame basis vectors
  float yaw = -90.0f;                    // Camera yaw angle
  float pitch = 0.0f;                    // Camera pitch angle

  float movement_per_second = 1.0f;  // Camera movement speed

  void initialize();
  Color ray_color(const ray& r, ObjectsList* world);
  bool update_camera_orientation();
};

#endif
