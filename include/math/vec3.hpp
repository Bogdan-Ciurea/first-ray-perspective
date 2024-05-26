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

#include <math.h>

#include <iostream>
#include <limits>

#include "raylib.h"

typedef unsigned int uint;
typedef unsigned char uchar;

// Operator overloading for Color addition
inline Color operator+(const Color& c1, const Color& c2) {
  uchar r = std::min(c1.r + c2.r, 255);
  uchar g = std::min(c1.g + c2.g, 255);
  uchar b = std::min(c1.b + c2.b, 255);
  uchar a = std::min(c1.a + c2.a, 255);

  return Color{r, g, b, a};
}

// Operator overloading for Color multiplication with a float
inline Color operator*(float f, const Color& c) {
  uchar r = (uchar)std::min((uint)(f * c.r), 255);
  uchar g = (uchar)std::min((uint)(f * c.g), 255);
  uchar b = (uchar)std::min((uint)(f * c.b), 255);
  uchar a = (uchar)std::min((uint)(f * c.a), 255);

  return Color{r, g, b, a};
}

class vec3 {
 public:
  vec3();
  vec3(const vec3& v);
  vec3(const double e0, const double e1, const double e2);

  double x() const { return e[0]; }
  double y() const { return e[1]; }
  double z() const { return e[2]; }

  double operator[](int i) const;
  bool operator==(const vec3& v) const;
  bool operator!=(const vec3& v) const;

  vec3 operator+(const vec3& v);
  vec3 operator-() const;
  vec3 operator*(double t) const;
  vec3 operator/(double t) const;
  vec3 cross(const vec3& v) const;
  vec3 unit_vector() const;

  double dot(const vec3& v) const;
  double length() const;
  double length_squared() const;

  vec3& operator+=(const vec3& v);
  vec3& operator-=(const vec3& v);
  vec3& operator*=(const double t);
  vec3& operator/=(const double t);

  friend std::ostream& operator<<(std::ostream& out, const vec3& v);
  friend std::istream& operator>>(std::istream& in, vec3& v);

 public:
  double e[3];
};

inline vec3 operator*(double t, const vec3& v) {
  return vec3(t * v.e[0], t * v.e[1], t * v.e[2]);
}

inline vec3 operator+(const vec3& u, const vec3& v) {
  return vec3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
}

inline vec3 operator-(const vec3& u, const vec3& v) {
  return vec3(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
}

inline vec3 operator*(const vec3& u, const vec3& v) {
  return vec3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
}

inline vec3 operator/(const vec3& u, const vec3& v) {
  return vec3(u.e[0] / v.e[0], u.e[1] / v.e[1], u.e[2] / v.e[2]);
}

inline Color operator+(const vec3& v, const Color& c) {
  uchar r = std::min((uint)(v.x() + c.r), 255);
  uchar g = std::min((uint)(v.y() + c.g), 255);
  uchar b = std::min((uint)(v.z() + c.b), 255);

  return Color{r, g, b, c.a};
}

#endif  // VEC3_HPP
