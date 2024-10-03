/**
 * @file Sphere.cpp
 * @author Bogdan Ciurea (ciureabogdanalexandru@gmail.com)
 * @brief This file contains the implementation of the Sphere class
 * @version 0.1
 * @date 2024-04-20
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "objects/Sphere.hpp"

Sphere::Sphere(const vec3& _center, float _radius,
               std::shared_ptr<material> _mat)
    : center(_center), radius(_radius), mat(_mat) {}

Sphere::~Sphere() {}

vec3 Sphere::get_center() { return center; }

float Sphere::get_radius() { return radius; }

bool Sphere::intersect(const ray& r, const interval& interval,
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
