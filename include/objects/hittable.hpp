/**
 * @file hittable.hpp
 * @author Bogdan Ciurea (ciureabogdanalexandru@gmail.com)
 * @brief This file contains the declaration of the hittable class that will be
 * the base class for all objects in the scene
 * @version 0.1
 * @date 2024-04-20
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef OBJECT_HPP
#define OBJECT_HPP

#include "aabb.hpp"
#include "material.hpp"
#include "math/interval.hpp"

class hittable {
 public:
  virtual ~hittable() = default;

  /**
   * @brief Get the object's intersection
   *
   * @param r The ray to intersect with
   * @param interval The interval in which the intersection should be
   * @param rec The hit record
   * @return bool True if the ray intersects the object, false otherwise
   */
  virtual bool hit(const ray& r, const interval& interval,
                   hit_record& rec) const = 0;

  /**
   * @brief Getter for the object's bounding box
   *
   * @return aabb The bounding box of the object
   */
  virtual aabb bounding_box() const = 0;

  virtual void move(const vec3& offset) = 0;
  virtual void rotate(const vec3& axis, float angle) = 0;
};

#endif  // OBJECT_HPP
