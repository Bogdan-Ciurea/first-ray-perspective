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

Sphere::Sphere(const vec3& center, double radius)
    : center(center), radius(radius) {}

Sphere::~Sphere() {}

Material* Sphere::get_material() { return material; }

vec3 Sphere::get_center() { return center; }

double Sphere::get_radius() { return radius; }

bool Sphere::intersect(const ray& r, double t_min, double t_max,
                       hit_record& rec) {
  vec3 oc = center - r.origin();
  auto a = r.direction().length_squared();
  auto h = r.direction().dot(oc);
  auto c = oc.length_squared() - radius * radius;

  auto discriminant = h * h - a * c;
  if (discriminant < 0) return false;

  auto sqrtd = sqrt(discriminant);

  // Find the nearest root that lies in the acceptable range.
  auto root = (h - sqrtd) / a;
  if (root <= t_min || t_max <= root) {
    root = (h + sqrtd) / a;
    if (root <= t_min || t_max <= root) return false;
  }

  rec.t = root;
  rec.p = r.at(rec.t);
  vec3 outward_normal = (rec.p - center) / radius;
  rec.set_face_normal(r, outward_normal);

  return true;
}