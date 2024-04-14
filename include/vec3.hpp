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

#endif  // VEC3_HPP
