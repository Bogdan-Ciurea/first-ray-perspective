/**
 * @file quad.h
 * @author your name (you@domain.com)
 * @brief Bogdan Ciurea (ciureabogdanalexandru@gmail.com)
 * @version 0.1
 * @date 2024-10-14
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef QUAD_H
#define QUAD_H

#include "hittable.hpp"

class quad : public hittable {
 public:
  /**
   * @brief Construct a new quadrilateral object
   *
   * @param Q
   * @param u
   * @param v
   * @param material The material of the quadrilateral
   */
  quad(const vec3& Q, const vec3& u, const vec3& v, shared_ptr<material> mat);

  ~quad() {}

  /**
   * @brief Set the bounding box object
   *
   */
  void set_bounding_box();

  /**
   * @brief
   *
   * @param a
   * @param b
   * @param rec
   * @return true
   * @return false
   */
  bool is_interior(double a, double b, hit_record& rec) const;

  /**
   * @brief Get the intersection of the quadrilateral
   *
   * @param r The ray to intersect with
   * @param interval The interval in which the intersection should be
   * @param rec The hit record
   * @return bool True if the ray intersects the quadrilateral, false otherwise
   */
  bool hit(const ray& r, const interval& ray_t, hit_record& rec) const override;

  /**
   * @brief
   *
   * @return aabb
   */
  aabb bounding_box() const override;

  void move(const vec3& offset) override;
  void rotate(const vec3& axis, float angle) override;

 private:
  vec3 Q;
  vec3 u, v;
  vec3 w;
  shared_ptr<material> mat;
  aabb bbox;
  vec3 normal;
  double D;
};

#endif
