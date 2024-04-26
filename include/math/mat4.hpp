/**
 * @file mat4.hpp
 * @author Bogdan Ciurea (ciureabogdanalexandru@gmail.com)
 * @brief Declaration of the mat4 class
 * @version 0.1
 * @date 2024-04-15
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef MAT4_HPP
#define MAT4_HPP

#include <iostream>

#include "vec4.hpp"

class mat4 {
 public:
  float coordinates[4][4];

  mat4();
  mat4(const mat4& m);

  bool operator==(const mat4& m) const;
  bool operator!=(const mat4& m) const;

  mat4 operator+(const mat4& m) const;
  mat4 operator-(const mat4& m) const;

  mat4 operator*(const mat4& m) const;
  vec4 operator*(const vec4& v) const;
  vec3 operator*(const vec3& v) const;
  mat4 operator*(float t) const;

  mat4 operator/(float t) const;

  mat4& operator+=(const mat4& m);
  mat4& operator-=(const mat4& m);

  mat4& operator*=(const mat4& m);
  mat4& operator*=(float t);
  mat4& operator/=(float t);

  friend std::ostream& operator<<(std::ostream& out, const mat4& m);
  friend std::istream& operator>>(std::istream& in, mat4& m);

  mat4 transpose() const;

  static mat4 identity();
  static mat4 translate(const vec3& v);
  static mat4 scale(const vec3& v);
  static mat4 rotate(float angle, const vec3& axis);
};

#endif  // MAT4_HPP