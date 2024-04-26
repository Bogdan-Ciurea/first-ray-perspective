/**
 * @file hit_record.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2024-04-20
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "hit_record.hpp"

void hit_record::set_face_normal(const ray& r, const vec3& outward_normal) {
  front_face = r.direction().dot(outward_normal) < 0;
  normal = front_face ? outward_normal : -outward_normal;
}
