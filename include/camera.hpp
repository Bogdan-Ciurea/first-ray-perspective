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

  Color send_ray(ObjectsList& world, const uint pixel_width,
                 const uint pixel_height);

  double aspect_ratio = 1.0;  // Ratio of image width over height
  int screen_width = 100;     // Rendered image width in pixel count

 private:
  int screen_height;   // Rendered image height
  vec3 center;         // Camera center
  vec3 pixel00_loc;    // Location of pixel 0, 0
  vec3 pixel_delta_u;  // Offset to pixel to the right
  vec3 pixel_delta_v;  // Offset to pixel below

  void initialize();
  Color ray_color(const ray& r, ObjectsList& world);
};

#endif