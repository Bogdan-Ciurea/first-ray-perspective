/**
 * @file Window.hpp
 * @author Bogdan Ciurea (ciureabogdanalexandru@gmail.com)
 * @brief Declaration of the RaytraceWindow class
 * @version 0.1
 * @date 2024-04-19
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <omp.h>

#include "camera.hpp"
#include "objects/ObjectsList.hpp"

class RaytraceWindow {
 public:
  RaytraceWindow(const int screen_width, const int screen_height,
                 const char* title);

  ~RaytraceWindow();

  void draw();
  void set_world(ObjectsList* world) { this->world = world; }

 private:
  int current_renders = 0;
  int max_renders = 10;
  uint target_fps = 30;
  int start_index = 0;  // The starting index for the next selection (when
                           // selecting random colors)

  const int screen_width;      // The dimensions of the window
  const int screen_height;     // The dimensions of the window
  ObjectsList* world;          // The world that we are going to draw
  camera cam;                  // The camera object
  std::vector<Color> pixels;   // The array of pixels that we are going to draw
  Texture2D texture;  // The texture that we are going to draw (DrawPixel method
                      // is not efficient for large images)

  std::vector<int> shuffled_index_array;  // An array of shuffled indices

  void draw_pixels();
  void reset_pixels();
  float get_ray_random_duration();
  void shuffle_indices(std::vector<int>& indices, int start_index);
};

#endif  // WINDOW_HPP
