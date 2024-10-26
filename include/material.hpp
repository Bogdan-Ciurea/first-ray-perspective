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
#include "texture.hpp"

class material {
 public:
  virtual ~material() = default;

  virtual vec3 emitted(float u, float v, const vec3& p) const {
    return vec3(0, 0, 0);
  }

  /**
   * @brief Function that scatters the ray on the object
   *
   * @param r_in The ray that hits the object
   * @param rec  The hit record
   * @param attenuation  The attenuation of the ray
   * @param scattered  The scattered ray
   * @return true  If the ray scatters
   * @return false  If the ray does not scatter
   */
  virtual bool scatter(ray& r_in, const hit_record& rec, vec3& attenuation,
                       ray& scattered) const {
    return false;
  }
};

/**
 * @brief Class that represents a lambertian material
 *
 */
class lambertian : public material {
 public:
  lambertian(const vec3& albedo) : tex(make_shared<solid_color>(albedo)) {}
  lambertian(shared_ptr<texture> tex) : tex(tex) {}

  bool scatter(ray& r_in, const hit_record& rec, vec3& attenuation,
               ray& scattered) const override {
    vec3 scatter_direction = rec.normal + random_unit_vector();

    if (scatter_direction.near_zero()) scatter_direction = rec.normal;

    scattered = ray(rec.p, scatter_direction);
    attenuation = tex->value(rec.u, rec.v, rec.p);
    return true;
  }

 private:
  shared_ptr<texture> tex;
};

/**
 * @brief Class that represents a metal material
 *
 */
class metal : public material {
 public:
  /**
   * @brief Construct a new metal object
   *
   * @param albedo  The albedo (aka Color) of the material
   * @param fuzz  The fuzziness of the material or the fuzziness of the
   * reflected rays
   */
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

/**
 * @brief Class that represents a dielectric (aka glass) material
 *
 */
class dielectric : public material {
 public:
  /**
   * @brief Construct a new dielectric object
   *
   * @param refraction_index  The refractive index of the material
   */
  dielectric(float refraction_index) : refraction_index(refraction_index) {}

  bool scatter(ray& r_in, const hit_record& rec, vec3& attenuation,
               ray& scattered) const override {
    attenuation = vec3(1.0f, 1.0f, 1.0f);
    float ri = rec.front_face ? (1.0f / refraction_index) : refraction_index;

    scattered = r_in.refract(rec.normal, rec.p, ri);
    return true;
  }

 private:
  // Refractive index in vacuum or air, or the ratio of the material's
  // refractive index over the refractive index of the enclosing media
  float refraction_index;
};

class diffuse_light : public material {
 public:
  diffuse_light(shared_ptr<texture> tex) : tex(tex) {}
  diffuse_light(const vec3& emit) : tex(make_shared<solid_color>(emit)) {}

  vec3 emitted(float u, float v, const vec3& p) const {
    return tex->value(u, v, p);
  }

 private:
  shared_ptr<texture> tex;
};

#endif