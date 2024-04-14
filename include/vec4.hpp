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

#include <math.h>

#include <algorithm>
#include <iostream>

#include "vec3.hpp"

class vec4 {
 public:
  vec4();
  vec4(const vec3& v);
  vec4(const vec3& v, double w);
  vec4(const vec4& v);
  vec4(const double e0, const double e1, const double e2, const double e3);

  void clamp_color();

  double x() const { return e[0]; }
  double y() const { return e[1]; }
  double z() const { return e[2]; }

  double operator[](int i) const;
  bool operator==(const vec4& v) const;
  bool operator!=(const vec4& v) const;

  vec4 operator+(const vec4& v);
  vec4 operator-() const;
  vec4 operator*(double t) const;
  vec4 operator/(double t) const;
  vec4 cross(const vec4& v) const;
  vec4 unit_vector() const;

  double dot(const vec4& v) const;
  double length() const;
  double length_squared() const;

  vec3 point() const { return vec3(e[0] / e[3], e[1] / e[3], e[2] / e[3]); }
  vec3 vector() const { return vec3(e[0], e[1], e[2]); }

  vec4& operator+=(const vec4& v);
  vec4& operator-=(const vec4& v);
  vec4& operator*=(const double t);
  vec4& operator/=(const double t);

  friend std::ostream& operator<<(std::ostream& out, const vec4& v);
  friend std::istream& operator>>(std::istream& in, vec4& v);

 public:
  double e[4];
};

#endif  // VEC4_HPP
