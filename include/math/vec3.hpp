/**
 * @file vec3.hpp
 * @author Bogdan Ciurea (ciureabogdanalexandru@gmail.com)
 * @brief Declaration of the vec3 class
 * @version 0.1
 * @date 2024-04-14
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef VEC3_HPP
#define VEC3_HPP

#include "utils.hpp"

class vec3 {
 public:
  vec3() {}
  vec3(float e0, float e1, float e2) {
    e[0] = e0;
    e[1] = e1;
    e[2] = e2;
  }
  inline float x() const { return e[0]; }
  inline float y() const { return e[1]; }
  inline float z() const { return e[2]; }
  inline float r() const { return e[0]; }
  inline float g() const { return e[1]; }
  inline float b() const { return e[2]; }

  inline const vec3 &operator+() const { return *this; }
  inline vec3 operator-() const { return vec3(-e[0], -e[1], -e[2]); }
  inline float operator[](int i) const { return e[i]; }
  inline float &operator[](int i) { return e[i]; };

  inline bool operator==(const vec3 &v) const {
    for (int i = 0; i < 3; i++) {
      if (std::fabs(e[i] - v[i]) > std::numeric_limits<float>::epsilon()) {
        return false;
      }
    }
    return true;
  }
  inline bool operator!=(const vec3 &v) const { return !(*this == v); }
  inline vec3 &operator+=(const vec3 &v) {
    e[0] += v.e[0];
    e[1] += v.e[1];
    e[2] += v.e[2];
    return *this;
  }
  inline vec3 &operator-=(const vec3 &v) {
    e[0] -= v.e[0];
    e[1] -= v.e[1];
    e[2] -= v.e[2];
    return *this;
  }
  inline vec3 &operator*=(const vec3 &v) {
    e[0] *= v.e[0];
    e[1] *= v.e[1];
    e[2] *= v.e[2];
    return *this;
  }
  inline vec3 &operator/=(const vec3 &v) {
    e[0] /= v.e[0];
    e[1] /= v.e[1];
    e[2] /= v.e[2];
    return *this;
  }
  inline vec3 &operator*=(const float t) {
    e[0] *= t;
    e[1] *= t;
    e[2] *= t;
    return *this;
  }
  inline vec3 &operator/=(const float t) {
    e[0] /= t;
    e[1] /= t;
    e[2] /= t;
    return *this;
  }

  inline float length() const { return sqrt(this->length_squared()); }
  inline float length_squared() const {
    return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
  }

  friend std::ostream &operator<<(std::ostream &out, const vec3 &v);
  friend std::istream &operator>>(std::istream &in, vec3 &v);

  std::array<float, 3> e;
};

inline vec3 operator+(const vec3 &v1, const vec3 &v) {
  return vec3(v1.e[0] + v.e[0], v1.e[1] + v.e[1], v1.e[2] + v.e[2]);
}

inline vec3 operator-(const vec3 &v1, const vec3 &v) {
  return vec3(v1.e[0] - v.e[0], v1.e[1] - v.e[1], v1.e[2] - v.e[2]);
}

inline vec3 operator*(const vec3 &v1, const vec3 &v) {
  return vec3(v1.e[0] * v.e[0], v1.e[1] * v.e[1], v1.e[2] * v.e[2]);
}

inline vec3 operator/(const vec3 &v1, const vec3 &v) {
  return vec3(v1.e[0] / v.e[0], v1.e[1] / v.e[1], v1.e[2] / v.e[2]);
}

inline vec3 operator*(float t, const vec3 &v) {
  return vec3(t * v.e[0], t * v.e[1], t * v.e[2]);
}

inline vec3 operator/(vec3 v, float t) {
  return vec3(v.e[0] / t, v.e[1] / t, v.e[2] / t);
}

inline vec3 operator*(const vec3 &v, float t) {
  return vec3(t * v.e[0], t * v.e[1], t * v.e[2]);
}

inline float dot(const vec3 &v1, const vec3 &v) {
  return v1.e[0] * v.e[0] + v1.e[1] * v.e[1] + v1.e[2] * v.e[2];
}

inline vec3 cross(const vec3 &v1, const vec3 &v) {
  return vec3((v1.e[1] * v.e[2] - v1.e[2] * v.e[1]),
              (-(v1.e[0] * v.e[2] - v1.e[2] * v.e[0])),
              (v1.e[0] * v.e[1] - v1.e[1] * v.e[0]));
}

inline vec3 unit_vector(const vec3 &v) {
  const float length = v.length();
  if (length == 0) {
    return vec3(0, 0, 0);
  }

  return vec3(v.e[0] / length, v.e[1] / length, v.e[2] / length);
}

/**
 * @brief Create a color object. Keep in mind that you might want to scale the
 * color values by 255 when using this function.
 *
 * @param r  The red component
 * @param g  The green component
 * @param b  The blue component
 * @param a  The alpha component
 * @return Color  The color object
 */
Color create_color(int r, int g, int b, int a = 255);

#endif  // VEC3_HPP
