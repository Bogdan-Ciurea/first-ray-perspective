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
#include "perlin.hpp"
#include "raylib.h"
#include "rtw_stb_image.hpp"

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

class image_texture : public texture {
 public:
  image_texture(const char* filename) : image(filename) {}

  vec3 value(float u, float v, const vec3& p) const override {
    // If there is no image data, return magenta.
    if (image.width() == 0) return vec3(1, 0, 1);

    // Clamp input texture coordinates to [0,1] x [1,0]
    u = clamp(u, 0.0f, 1.0f);
    v = 1.0f - clamp(v, 0.0f, 1.0f);  // Flip V to image coordinates

    int i = static_cast<int>(u * image.width());
    int j = static_cast<int>(v * image.height());

    // Clamp integer mapping, since actual coordinates should be less than 1.0
    if (i >= image.width()) i = image.width() - 1;
    if (j >= image.height()) j = image.height() - 1;

    const unsigned char* pixel = image.pixel_data(i, j);

    // Normalize [0,255] -> [0,1]
    return vec3(pixel[0], pixel[1], pixel[2]) / 255.0f;
  }

 private:
  rtw_image image;
};

class noise_texture : public texture {
 public:
  noise_texture() {}
  noise_texture(float _scale) : noise(), scale(_scale) {}

  vec3 value(float u, float v, const vec3& p) const override {
    return vec3(.5f, .5f, .5f) *
           (1 + std::sin(scale * p.z() + 10 * noise.turb(p, 7)));
  }

 private:
  perlin noise;
  float scale;
};

#endif  // TEXTURE_HPP