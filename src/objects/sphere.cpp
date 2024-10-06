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

bool sphere::hit(const ray& r, const interval& interval,
                 hit_record& rec) const {
  // The equation of a sphere is (x - center)^2 + (y - center)^2 + (z -
  // center)^2
  vec3 oc = r.origin() - center;
  float a = dot(r.direction(), r.direction());
  float b = dot(oc, r.direction());
  float c = dot(oc, oc) - radius * radius;
  float discriminant = b * b - a * c;

  // If the discriminant is greater than 0, the ray intersects the sphere
  if (discriminant > 0) {
    float temp = (-b - sqrt(discriminant)) / a;
    if (interval.surrounds(temp)) {
      rec.t = temp;
      rec.p = r.at(rec.t);
      vec3 outward_normal = (rec.p - center) / radius;
      rec.set_face_normal(r, outward_normal);
      rec.mat_ptr = mat;
      get_sphere_uv(outward_normal, rec.u, rec.v);
      return true;
    }
    // If the first intersection point is not in the interval, check the second
    temp = (-b + sqrt(discriminant)) / a;
    if (interval.surrounds(temp)) {
      rec.t = temp;
      rec.p = r.at(rec.t);
      vec3 outward_normal = (rec.p - center) / radius;
      rec.set_face_normal(r, outward_normal);
      get_sphere_uv(outward_normal, rec.u, rec.v);
      rec.mat_ptr = mat;
      return true;
    }
  }
  return false;
}

void sphere::get_sphere_uv(const vec3& p, float& u, float& v) {
  float phi = atan2(p.z(), p.x());
  float theta = asin(p.y());
  u = 1 - (phi + M_PI) / (2 * M_PI);
  v = (theta + M_PI / 2) / M_PI;

  /*
    //      <1 0 0> yields <0.50 0.50>      <-1  0  0> yields <0.00 0.50>
    //      <0 1 0> yields <0.50 1.00>      < 0 -1  0> yields <0.50 0.00>
    //      <0 0 1> yields <0.25 0.50>      < 0  0 -1> yields <0.75 0.50>

    // theta is the angle from the y-axis
    float theta = std::acos(-p.y());
    // phi is the angle from the x-axis around the z-axis
    float phi = std::atan2(-p.z(), p.x()) + M_PI;

    // Normalize the angles
    u = phi / (2 * M_PI);
    v = theta / M_PI;
  */
}
