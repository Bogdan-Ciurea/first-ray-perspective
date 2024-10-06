/**
 * @file texture.hpp
 * @author Bogdan Ciurea (ciureabogdanalexandru@gmail.com)
 * @brief Declaration of the texture class
 * @version 0.1
 * @date 2024-10-06
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include "math/vec3.hpp"
#include "raylib.h"

class texture {
 public:
  virtual ~texture() = default;

  virtual vec3 value(float u, float v, const vec3& p) const = 0;
};

class solid_color : public texture {
 public:
  solid_color(const vec3& albedo) : albedo(albedo) {}

  solid_color(float red, float green, float blue)
      : solid_color(vec3(red, green, blue)) {}

  vec3 value(float u, float v, const vec3& p) const override { return albedo; }

 private:
  vec3 albedo;
};

class checker_texture : public texture {
 public:
  checker_texture(float scale, shared_ptr<texture> even,
                  shared_ptr<texture> odd)
      : inv_scale(1.0f / scale), even(even), odd(odd) {}

  checker_texture(float scale, const vec3& c1, const vec3& c2)
      : checker_texture(scale, make_shared<solid_color>(c1),
                        make_shared<solid_color>(c2)) {}

  vec3 value(float u, float v, const vec3& p) const override {
    int xInteger = int(std::floor(inv_scale * p.x()));
    int yInteger = int(std::floor(inv_scale * p.y()));
    int zInteger = int(std::floor(inv_scale * p.z()));

    bool isEven = (xInteger + yInteger + zInteger) % 2 == 0;

    return isEven ? even->value(u, v, p) : odd->value(u, v, p);
  }

 private:
  float inv_scale;
  shared_ptr<texture> even;
  shared_ptr<texture> odd;
};

#endif  // TEXTURE_HPP