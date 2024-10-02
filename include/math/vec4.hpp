/**
 * @file vec4.hpp
 * @author Bogdan Ciurea (ciureabogdanalexandru@gmail.com)
 * @brief Declaration of the vec4 class
 * @version 0.1
 * @date 2024-04-14
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef VEC4_HPP
#define VEC4_HPP

#include "vec3.hpp"

class vec4 {
 public:
  vec4() { e[0] = e[1] = e[2] = e[3] = 0; }
  vec4(const vec3& v) : e{v.x(), v.y(), v.z(), 1.0} {}
  vec4(const vec3& v, float w) : e{v.x(), v.y(), v.z(), w} {}
  vec4(const vec4& v) : e{v.e[0], v.e[1], v.e[2], v.e[3]} {}
  vec4(float e0, float e1, float e2, float e3) {
    e[0] = e0;
    e[1] = e1;
    e[2] = e2;
    e[3] = e3;
  }

  inline float x() const { return e[0]; }
  inline float y() const { return e[1]; }
  inline float z() const { return e[2]; }
  inline float w() const { return e[3]; }
  inline float r() const { return e[0]; }
  inline float g() const { return e[1]; }
  inline float b() const { return e[2]; }
  inline float a() const { return e[3]; }

  inline const vec4& operator+() const { return *this; }
  inline vec4 operator-() const { return vec4(-e[0], -e[1], -e[2], -e[3]); }
  inline float operator[](int i) const { return e[i]; }
  inline float operator[](int i) { return e[i]; };

  inline bool operator==(const vec4& v) const {
    for (int i = 0; i < 4; i++) {
      if (abs(e[i] - v[i]) > std::numeric_limits<float>::epsilon()) {
        return false;
      }
    }
    return true;
  }
  inline bool operator!=(const vec4& v) const { return !(*this == v); }
  inline vec4& operator+=(const vec4& v) {
    e[0] += v.e[0];
    e[1] += v.e[1];
    e[2] += v.e[2];
    e[3] += v.e[3];
    return *this;
  }
  inline vec4& operator-=(const vec4& v) {
    e[0] -= v.e[0];
    e[1] -= v.e[1];
    e[2] -= v.e[2];
    e[3] -= v.e[3];
    return *this;
  }
  inline vec4& operator*=(const vec4& v) {
    e[0] *= v.e[0];
    e[1] *= v.e[1];
    e[2] *= v.e[2];
    e[3] *= v.e[3];
    return *this;
  }
  inline vec4& operator/=(const vec4& v) {
    e[0] /= v.e[0];
    e[1] /= v.e[1];
    e[2] /= v.e[2];
    e[3] /= v.e[3];
    return *this;
  }
  inline vec4& operator*=(const float t) {
    e[0] *= t;
    e[1] *= t;
    e[2] *= t;
    e[3] *= t;
    return *this;
  }
  inline vec4& operator/=(const float t) {
    e[0] /= t;
    e[1] /= t;
    e[2] /= t;
    e[3] /= t;
    return *this;
  }

  float length() const { return sqrt(this->length_squared()); }
  float length_squared() const {
    return e[0] * e[0] + e[1] * e[1] + e[2] * e[2] + e[3] * e[3];
  }

  vec3 point() const { return vec3(e[0] / e[3], e[1] / e[3], e[2] / e[3]); }
  vec3 vector() const { return vec3(e[0], e[1], e[2]); }

  friend std::ostream& operator<<(std::ostream& out, const vec4& v) {
    return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2] << ' ' << v.e[3];
  }
  friend std::istream& operator>>(std::istream& in, vec4& v) {
    return in >> v.e[0] >> v.e[1] >> v.e[2] >> v.e[3];
  }

  Color to_color(const float mult = 1) const {
    uchar r = (uchar)clamp(abs(e[0]) * mult, 0, 255);
    uchar g = (uchar)clamp(abs(e[1]) * mult, 0, 255);
    uchar b = (uchar)clamp(abs(e[2]) * mult, 0, 255);
    uchar a = (uchar)clamp(abs(e[3]) * mult, 0, 255);

    return Color{r, g, b, a};
  }

  std::array<float, 4> e;
};

inline vec4 operator*(float t, const vec4& v) {
  return vec4(t * v.e[0], t * v.e[1], t * v.e[2], t * v.e[3]);
}

inline vec4 operator/(const vec4& v, float t) {
  return vec4(v.e[0] / t, v.e[1] / t, v.e[2] / t, v.e[3] / t);
}

inline vec4 operator+(const vec4& u, const vec4& v) {
  return vec4(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2],
              u.e[3] + v.e[3]);
}

inline vec4 operator-(const vec4& u, const vec4& v) {
  return vec4(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2],
              u.e[3] - v.e[3]);
}

inline vec4 operator*(const vec4& u, const vec4& v) {
  return vec4(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2],
              u.e[3] * v.e[3]);
}

inline vec4 operator/(const vec4& u, const vec4& v) {
  return vec4(u.e[0] / v.e[0], u.e[1] / v.e[1], u.e[2] / v.e[2],
              u.e[3] / v.e[3]);
}

inline float dot(const vec4& u, const vec4& v) {
  return u.e[0] * v.e[0] + u.e[1] * v.e[1] + u.e[2] * v.e[2] + u.e[3] * v.e[3];
}

inline vec3 cross(const vec4& u, const vec4& v) {
  return vec3(u.e[1] * v.e[2] - u.e[2] * v.e[1],
              -(u.e[0] * v.e[2] - u.e[2] * v.e[0]),
              u.e[0] * v.e[1] - u.e[1] * v.e[0]);
}

inline vec4 unit_vector(const vec4& v) {
  const float length = v.length();

  if (length == 0) {
    return vec4(0, 0, 0, 0);
  }

  return vec4(v.e[0] / length, v.e[1] / length, v.e[2] / length,
              v.e[3] / length);
}

#endif  // VEC4_HPP
