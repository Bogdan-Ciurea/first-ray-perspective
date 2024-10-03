/**
 * @file sphere.cpp
 * @author Bogdan Ciurea (ciureabogdanalexandru@gmail.com)
 * @brief This file contains the implementation of the sphere class
 * @version 0.1
 * @date 2024-04-20
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "objects/sphere.hpp"

sphere::sphere(const vec3& _center, float _radius,
               std::shared_ptr<material> _mat)
    : center(_center), radius(_radius), mat(_mat) {
  const vec3 rvec = vec3(radius, radius, radius);
  bbox = aabb(center - rvec, center + rvec);
}

sphere::~sphere() {}

vec3 sphere::get_center() { return center; }

float sphere::get_radius() { return radius; }

bool sphere::intersect(const ray& r, const interval& interval,
                       hit_record& rec) {
  vec3 oc = r.origin() - center;
  float a = dot(r.direction(), r.direction());
  float b = dot(oc, r.direction());
  float c = dot(oc, oc) - radius * radius;
  float discriminant = b * b - a * c;

  if (discriminant > 0) {
    float temp = (-b - sqrt(discriminant)) / a;
    if (interval.surrounds(temp)) {
      rec.t = temp;
      rec.p = r.at(rec.t);
      vec3 outward_normal = (rec.p - center) / radius;
      rec.set_face_normal(r, outward_normal);
      rec.mat_ptr = mat;
      return true;
    }
    temp = (-b + sqrt(discriminant)) / a;
    if (interval.surrounds(temp)) {
      rec.t = temp;
      rec.p = r.at(rec.t);
      vec3 outward_normal = (rec.p - center) / radius;
      rec.set_face_normal(r, outward_normal);
      rec.mat_ptr = mat;
      return true;
    }
  }
  return false;
}
