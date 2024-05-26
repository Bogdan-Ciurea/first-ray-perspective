/**
 * @file ray.hpp
 * @author Bogdan Ciurea (ciureabogdanalexandru@gmail.com)
 * @brief Declaration of the ray class
 * @version 0.1
 * @date 2024-04-15
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef RAY_H
#define RAY_H

#include "math/mat4.hpp"

class ray {
 public:
  ray() {}

  ray(const vec3& origin, const vec3& direction)
      : orig(origin), dir(direction) {}

  const vec3& origin() const { return orig; }
  const vec3& direction() const { return dir; }

  /**
   * @brief Returns the point at a distance t from the origin of the ray
   *
   * @param t The distance from the origin
   * @return vec3  The point at distance t from the origin
   */
  vec3 at(double t) const { return orig + t * dir; }

  /**
   * @brief Function that constructs a reflected ray from an intersection point
   *
   * @param normal The normal of the intersection point
   * @param intersection_point The coordinates of the intersection point
   * @return vec3 The reflected ray
   */
  vec3 reflect(const vec3& normal, const vec3& intersection_point) const;

  /**
   * @brief Function that constructs a refracted ray from an intersection point
   *
   * @param normal The normal of the intersection point
   * @param intersection_point The coordinates of the intersection point
   * @param etai_over_etat The ratio of the refractive indices
   * @return vec3 The refracted ray
   */
  vec3 refract(const vec3& normal, const vec3& intersection_point,
               double etai_over_etat) const;

 private:
  vec3 orig;
  vec3 dir;
};

#endif