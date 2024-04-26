/**
 * @file Sphere.hpp
 * @author Bogdan Ciurea (ciureabogdanalexandru@gmail.com)
 * @brief Declaration of the Sphere class
 * @version 0.1
 * @date 2024-04-20
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef SPHERE_HPP
#define SPHERE_HPP

#include "Object.hpp"

class Sphere : public Object {
 public:
  /**
   * @brief Construct a new Sphere object
   *
   * @param center The center of the sphere
   * @param radius The radius of the sphere
   * @param material The material of the sphere
   */
  Sphere(const vec3& center, double radius);

  /**
   * @brief Destroy the Sphere object
   *
   */
  ~Sphere();

  /**
   * @brief Get the material of the sphere
   *
   * @return Material The material of the sphere
   */
  Material* get_material();

  /**
   * @brief Get the center of the sphere
   *
   * @return vec3 The center of the sphere
   */
  vec3 get_center();

  /**
   * @brief Get the radius of the sphere
   *
   * @return double The radius of the sphere
   */
  double get_radius();

  /**
   * @brief Get the intersection of the sphere
   *
   * @param r The ray to intersect with
   * @param t_min The minimum t value
   * @param t_max The maximum t value
   * @param rec The hit record
   * @return bool True if the ray intersects the sphere, false otherwise
   */
  bool intersect(const ray& r, double t_min, double t_max, hit_record& rec);

  /**
   * @brief Move the sphere by a given offset
   *
   * @param offset The offset to move the sphere by
   */
  void move(const vec3& offset) { center += offset; }
  void rotate(const vec3& axis, double angle) {}

 private:
  vec3 center;
  double radius;
  Material* material;
};

#endif  // SPHERE_HPP