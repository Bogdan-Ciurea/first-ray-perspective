/**
 * @file hit_record.hpp
 * @author Bogdan Ciurea (ciureabogdanalexandru@gmail.com)
 * @brief Declaration of the hit_record struct
 * @version 0.1
 * @date 2024-04-20
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef HIT_RECORD_HPP
#define HIT_RECORD_HPP

#include "ray.hpp"

class hit_record {
 public:
  vec3 p;
  vec3 normal;
  double t;
  bool front_face;

  void set_face_normal(const ray& r, const vec3& outward_normal);
};

#endif  // HIT_RECORD_HPP
