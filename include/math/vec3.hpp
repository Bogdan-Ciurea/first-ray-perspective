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

#include "raylib.h"
#include "utils.hpp"

typedef unsigned int uint;
typedef unsigned char uchar;

// My own color class
class MColor {
 public:
  MColor() : r(0), g(0), b(0), a(255) {}
  MColor(uchar r, uchar g, uchar b, uchar a) : r(r), g(g), b(b), a(a) {}
  MColor(double r, double g, double b)
      : r(abs(r * 255.999)), g(abs(g * 255.999)), b(abs(b * 255.999)), a(255) {}
  MColor(double r, double g, double b, double a)
      : r(abs(r * 255.999)),
        g(abs(g * 255.999)),
        b(abs(b * 255.999)),
        a(abs(a * 255.999)) {}

  Color to_color() { return Color{r, g, b, a}; }

  uchar r;
  uchar g;
  uchar b;
  uchar a;
};

inline MColor operator+(const MColor& c1, const MColor& c2) {
  uchar r = c1.r + c2.r > 255 ? 255 : c1.r + c2.r;
  uchar g = c1.g + c2.g > 255 ? 255 : c1.g + c2.g;
  uchar b = c1.b + c2.b > 255 ? 255 : c1.b + c2.b;
  uchar a = c1.a + c2.a > 255 ? 255 : c1.a + c2.a;

  return MColor(r, g, b, a);
}

inline MColor operator*(const float f, const MColor& c) {
  uchar r = f * c.r > 255 ? 255 : f * c.r;
  uchar g = f * c.g > 255 ? 255 : f * c.g;
  uchar b = f * c.b > 255 ? 255 : f * c.b;
  uchar a = f * c.a > 255 ? 255 : f * c.a;

  return MColor(r, g, b, a);
}

// Operator overloading for Color addition
inline Color operator+(const Color& c1, const Color& c2) {
  unsigned char r = (uchar)clamp(c1.r + c2.r, 0.0f, 255.0f);
  unsigned char g = (uchar)clamp(c1.g + c2.g, 0.0f, 255.0f);
  unsigned char b = (uchar)clamp(c1.b + c2.b, 0.0f, 255.0f);
  unsigned char a = (uchar)clamp(c1.a + c2.a, 0.0f, 255.0f);

  return Color{r, g, b, a};
}

// Operator overloading for Color multiplication with a float
inline Color operator*(float f, const Color& c) {
  unsigned char r = (uchar)clamp(f * c.r, 0.0f, 255.0f);
  unsigned char g = (uchar)clamp(f * c.g, 0.0f, 255.0f);
  unsigned char b = (uchar)clamp(f * c.b, 0.0f, 255.0f);
  unsigned char a = (uchar)clamp(f * c.a, 0.0f, 255.0f);

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

inline MColor operator+(const vec3, const MColor& c) {
  uchar r = c.r + c.r > 255 ? 255 : c.r + c.r;
  uchar g = c.g + c.g > 255 ? 255 : c.g + c.g;
  uchar b = c.b + c.b > 255 ? 255 : c.b + c.b;

  return MColor(r, g, b, c.a);
}

inline Color operator+(const vec3, const Color& c) {
  unsigned char r = (uchar)clamp(c.r, 0.0f, 255.0f);
  unsigned char g = (uchar)clamp(c.g, 0.0f, 255.0f);
  unsigned char b = (uchar)clamp(c.b, 0.0f, 255.0f);
  unsigned char a = (uchar)clamp(c.a, 0.0f, 255.0f);

  return Color{r, g, b, a};
}

#endif  // VEC3_HPP
