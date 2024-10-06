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
  vec3 at(float t) const { return orig + t * dir; }

  /**
   * @brief Function that constructs a reflected ray from an intersection point
   *
   * @param normal The normal of the intersection point
   * @param intersection_point The coordinates of the intersection point
   * @return vec3 The reflected ray
   */
  ray reflect(const vec3& normal, const vec3& intersection_point,
              const float& fuzz) const;

  /**
   * @brief Function that constructs a refracted ray from an intersection point
   *
   * @param normal The normal of the intersection point
   * @param intersection_point The coordinates of the intersection point
   * @param etai_over_etat The ratio of the refractive indices
   * @return vec3 The refracted ray
   */
  ray refract(const vec3& normal, const vec3& intersection_point,
              float etai_over_etat) const;

 private:
  vec3 orig;  // Origin of the ray
  vec3 dir;   // Direction of the ray

  float schlick(float cosine, float ref_idx) const;
};

class material;

class hit_record {
 public:
  vec3 p;           // Point of intersection
  vec3 normal;      // Normal at the intersection point
  float t;          // Distance from the ray origin
  float u;          // U coordinate of the texture
  float v;          // V coordinate of the texture
  bool front_face;  // True if the ray intersects the front face of the object
  std::shared_ptr<material> mat_ptr;  // Material of the object that was hit

  /**
   * @brief Set the face normal object
   *
   * @param r  The ray
   * @param outward_normal  The outward normal
   */
  void set_face_normal(const ray& r, const vec3& outward_normal);
};

#endif