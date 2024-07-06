/**
 * @file material.hpp
 * @author Bogdan Ciurea
 * @brief  Declaration of the material class
 * @version 0.1
 * @date 2024-07-06
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef MATERIAL_H
#define MATERIAL_H

#include "ray.hpp"

class material {
 public:
  virtual ~material() = default;

  virtual bool scatter(ray& r_in, const hit_record& rec, vec3& attenuation,
                       ray& scattered) const {
    return false;
  }
};

class lambertian : public material {
 public:
  lambertian(const vec3& a) : albedo(a) {}

  bool scatter(ray& r_in, const hit_record& rec, vec3& attenuation,
               ray& scattered) const override {
    vec3 scatter_direction = rec.normal + random_unit_vector();

    if (scatter_direction.near_zero()) scatter_direction = rec.normal;

    scattered = ray(rec.p, scatter_direction);
    attenuation = albedo;
    return true;
  }

 private:
  vec3 albedo;
};

class metal : public material {
 public:
  metal(const vec3& albedo) : albedo(albedo) {}

  bool scatter(ray& r_in, const hit_record& rec, vec3& attenuation,
               ray& scattered) const override {
    scattered = r_in.reflect(rec.normal, rec.p);
    attenuation = albedo;
    return true;
  }

 private:
  vec3 albedo;
};

#endif