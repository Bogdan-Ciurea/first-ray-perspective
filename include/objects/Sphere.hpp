/**
 * @file sphere.hpp
 * @author Bogdan Ciurea (ciureabogdanalexandru@gmail.com)
 * @brief Declaration of the sphere class
 * @version 0.1
 * @date 2024-04-20
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef SPHERE_HPP
#define SPHERE_HPP

#include "hittable.hpp"

class sphere : public hittable {
 public:
  /**
   * @brief Construct a new sphere object
   *
   * @param center The center of the sphere
   * @param radius The radius of the sphere
   * @param material The material of the sphere
   */
  sphere(const vec3& center, float radius,
         const std::shared_ptr<material> material);

  /**
   * @brief Destroy the sphere object
   *
   */
  ~sphere();

  /**
   * @brief Get the material of the sphere
   *
   * @return Material The material of the sphere
   */
  // Material* get_material();

  /**
   * @brief Get the center of the sphere
   *
   * @return vec3 The center of the sphere
   */
  vec3 get_center();

  /**
   * @brief Get the radius of the sphere
   *
   * @return float The radius of the sphere
   */
  float get_radius();

  /**
   * @brief Get the intersection of the sphere
   *
   * @param r The ray to intersect with
   * @param interval The interval in which the intersection should be
   * @param rec The hit record
   * @return bool True if the ray intersects the sphere, false otherwise
   */
  bool hit(const ray& r, const interval& interval,
           hit_record& rec) const override;

  /**
   * @brief Move the sphere by a given offset
   *
   * @param offset The offset to move the sphere by
   */
  void move(const vec3& offset) override { center += offset; }

  /**
   * @brief Rotate the sphere by a given angle around a given axis
   *
   * @param axis The axis to rotate the sphere around
   * @param angle The angle to rotate the sphere by
   */
  void rotate(const vec3& axis, float angle) override {}

  /**
   * @brief Get the bounding box of the sphere
   *
   * @return aabb The bounding box of the sphere
   */
  aabb bounding_box() const override { return bbox; }

 private:
  vec3 center;
  float radius;
  std::shared_ptr<material> mat;
  aabb bbox;
};

#endif  // SPHERE_HPP
