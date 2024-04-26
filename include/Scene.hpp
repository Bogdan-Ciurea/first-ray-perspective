/**
 * @file Scene.hpp
 * @author Bogdan Ciurea (ciureabogdanalexandru@gmail.com)
 * @brief Declaration of the Scene class
 * @version 0.1
 * @date 2024-04-19
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef SCENE_HPP
#define SCENE_HPP

#include "math/mat4.hpp"

/**
 * @brief Class responsible for managing the scene.
 * These are the responsibilities of the Scene class:
 * - Will COMMUNICATE with the camera
 * - Will store and process the View Model Matrix
 * - Will process and store intersections data
 * - Will store the objects in the scene
 * - Will store the lights in the scene
 *
 */
class Scene {
 public:
  /**
   * @brief Construct a new Scene object
   *
   * @param screen_width The width of the screen
   * @param screen_height The height of the screen
   */
  Scene(int screen_width, int screen_height);

  /**
   * @brief Destroy the Scene object
   *
   */
  ~Scene();

  /**
   * @brief Get the screen width
   *
   * @return int The screen width
   */
  int get_screen_width();

  /**
   * @brief Get the screen height
   *
   * @return int The screen height
   */
  int get_screen_height();

  /**
   * @brief Get the view model matrix
   *
   * @return mat4 The view model matrix
   */
  mat4 get_view_model_matrix();

  /**
   * @brief Set the view model matrix
   *
   * @param view_model_matrix The view model matrix
   */
  void set_view_model_matrix(mat4 view_model_matrix);

 private:
  int screen_width;
  int screen_height;
  mat4 view_model_matrix;
};

#endif  // SCENE_HPP
