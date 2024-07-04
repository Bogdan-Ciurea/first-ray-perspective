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
  RaytraceWindow(int screen_width, int screen_height, const char* title);

  ~RaytraceWindow();

  void draw();
  void set_world(ObjectsList* world) { this->world = world; }

 private:
  uint rays_per_pixel = 1;
  uint target_fps = 30;

  int screen_width;
  int screen_height;
  ObjectsList* world;
  camera cam;
  Color* pixels;
  std::vector<int> total_elements;

  void draw_pixels();
  void reset_pixels();
  double get_ray_random_duration();
  void shuffle_indices(std::vector<int>& indices, int start_index);
  std::vector<int> select_random_colors(std::vector<int>& indices,
                                        int& start_index, int num_to_select,
                                        int total_elements);
};

#endif  // WINDOW_HPP
