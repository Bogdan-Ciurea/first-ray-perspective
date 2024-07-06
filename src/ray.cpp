/**
 * @file ray.cpp
 * @author Bogdan Ciurea
 * @brief
 * @version 0.1
 * @date 2024-04-20
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "ray.hpp"

void hit_record::set_face_normal(const ray& r, const vec3& outward_normal) {
  front_face = dot(r.direction(), outward_normal) < 0;
  normal = front_face ? outward_normal : -outward_normal;
}

ray ray::reflect(const vec3& normal, const vec3& intersection_point) const {
  return ray(intersection_point, dir - 2 * dot(dir, normal) * normal);
}

ray ray::refract(const vec3& normal, const vec3& intersection_point,
                 double etai_over_etat) const {
  vec3 unit_direction = unit_vector(dir);
  double cos_theta = fmin(dot(-unit_direction, normal), 1.0);
  vec3 r_out_perp = etai_over_etat * (unit_direction + cos_theta * normal);
  vec3 r_out_parallel = -sqrt(fabs(1.0 - r_out_perp.length_squared())) * normal;
  return ray(intersection_point, r_out_perp + r_out_parallel);
}