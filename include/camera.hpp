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
  /**
   * @brief Construct a new camera object.
   * Will initialize the camera with default values
   * screen_height = 100, screen_width = 100, max_depth = 10
   *
   */
  camera();

  /**
   * @brief Construct a new camera object
   *
   * @param image_width The width of the rendered image
   * @param screen_height The height of the rendered image
   * @param max_depth The maximum depth of the ray
   */
  camera(const size_t image_width, const size_t screen_height,
         const size_t max_depth);

  /**
   * @brief Destroy the camera object
   *
   */
  ~camera() {}

  /**
   * @brief Function that generates a ray from the camera to a pixel on the
   * screen. The function returns the color of the pixel that the ray
   * intersects with.
   *
   * @param world The list of objects in the scene
   * @param pixel_width The "index" of the pixel on the x-axis. The value should
   * be between 0 and screen_width but can be a floating point number as we are
   * using anti-aliasing.
   * @param pixel_height The "index" of the pixel on the y-axis. The value
   * should be between 0 and screen_height but can be a floating point number as
   * we are using anti-aliasing.
   *
   * @return vec3 The color of the pixel that the ray intersects with
   */
  vec3 send_ray(ObjectsList* world, const double pixel_width,
                const double pixel_height);

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
  size_t max_depth;   // Maximum depth of the ray

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

  double defocus_angle = 0;  // Variation angle of rays through each pixel
  double focus_dist =
      10;  // Distance from camera lookfrom point to plane of perfect focus
  vec3 defocus_disk_u;  // Defocus disk u vector
  vec3 defocus_disk_v;  // Defocus disk v vector

  float movement_per_second = 1.0f;  // Camera movement speed

  /**
   * @brief Function to initialize the camera's parameters based on the
   * viewport size and camera position. This  function is called once at the
   * beginning of the program. Furthermore, it is also called when the camera
   * is moved as the camera's position changes.
   *
   */
  void initialize();

  /**
   * @brief Function that takes a ray as input and returns the color of the
   * pixel that the ray intersects with. The function is recursive and will
   * continue to call itself until the maximum depth is reached.
   *
   * @param r The ray to trace
   * @param world The list of objects in the scene
   * @param depth The current depth of the ray
   *
   * @return vec3 The color of the pixel that the ray intersects with
   */
  vec3 ray_color(ray& r, ObjectsList* world, const size_t depth = 1);

  /**
   * @brief Function that updates the camera's orientation based on the
   * keyboard input. The function is called every frame and updates the camera's
   * position based on the input.
   *
   */
  bool update_camera_orientation();

  /**
   * @brief Function that returns a random point on the defocus disk. The
   * function is used to simulate the defocus effect of the camera.
   *
   * @return vec3 The random point on the defocus disk
   */
  vec3 defocus_disk_sample() const;
};

#endif
