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
  metal(const vec3& albedo, const float& fuzz = 0)
      : albedo(albedo), fuzz(fuzz < 1 ? fuzz : 1) {}

  bool scatter(ray& r_in, const hit_record& rec, vec3& attenuation,
               ray& scattered) const override {
    scattered = r_in.reflect(rec.normal, rec.p, fuzz);
    attenuation = albedo;
    return dot(scattered.direction(), rec.normal) > 0;
  }

 private:
  vec3 albedo;
  float fuzz;
};

class dielectric : public material {
 public:
  dielectric(double refraction_index) : refraction_index(refraction_index) {}

  bool scatter(ray& r_in, const hit_record& rec, vec3& attenuation,
               ray& scattered) const override {
    attenuation = vec3(1.0, 1.0, 1.0);
    double ri = rec.front_face ? (1.0 / refraction_index) : refraction_index;

    scattered = r_in.refract(rec.normal, rec.p, ri);
    return true;
  }

 private:
  // Refractive index in vacuum or air, or the ratio of the material's
  // refractive index over the refractive index of the enclosing media
  double refraction_index;
};

#endif