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
  std::array<std::array<float, 4>, 4> coordinates;

  mat4() {
    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 4; j++) {
        coordinates[i][j] = 0;
      }
    }
  }
  mat4(const mat4& m) {
    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 4; j++) {
        coordinates[i][j] = m.coordinates[i][j];
      }
    }
  }

  bool operator==(const mat4& m) const {
    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 4; j++) {
        if (abs(coordinates[i][j] - m.coordinates[i][j]) >
            std::numeric_limits<float>::epsilon()) {
          return false;
        }
      }
    }
    return true;
  }
  bool operator!=(const mat4& m) const { return !(*this == m); }

  mat4 operator+(const mat4& m) const {
    mat4 result;
    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 4; j++) {
        result.coordinates[i][j] = coordinates[i][j] + m.coordinates[i][j];
      }
    }
    return result;
  }
  mat4 operator-(const mat4& m) const {
    mat4 result;
    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 4; j++) {
        result.coordinates[i][j] = coordinates[i][j] - m.coordinates[i][j];
      }
    }
    return result;
  }

  mat4 operator*(const mat4& m) const {
    mat4 result;
    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 4; j++) {
        for (int k = 0; k < 4; k++) {
          result.coordinates[i][j] += coordinates[i][k] * m.coordinates[k][j];
        }
      }
    }
    return result;
  }
  vec4 operator*(const vec4& v) const {
    vec4 result;
    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 4; j++) {
        result.e[i] += coordinates[i][j] * v[j];
      }
    }
    return result;
  }
  vec3 operator*(const vec3& v) const {
    vec4 result = *this * vec4(v, 1);
    return vec3(result[0], result[1], result[2]);
  }
  mat4 operator*(float t) const {
    mat4 result;
    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 4; j++) {
        result.coordinates[i][j] = coordinates[i][j] * t;
      }
    }
    return result;
  }

  mat4 operator/(float t) const { return *this * (1 / t); }

  mat4& operator+=(const mat4& m) {
    *this = *this + m;
    return *this;
  }
  mat4& operator-=(const mat4& m) {
    *this = *this - m;
    return *this;
  }

  mat4& operator*=(const mat4& m) {
    *this = *this * m;
    return *this;
  }
  mat4& operator*=(float t) {
    *this = *this * t;
    return *this;
  }
  mat4& operator/=(float t) {
    *this = *this * (1 / t);
    return *this;
  }

  friend std::ostream& operator<<(std::ostream& out, const mat4& m) {
    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 4; j++) {
        out << m.coordinates[i][j] << " ";
      }
      out << std::endl;
    }
    return out;
  }
  friend std::istream& operator>>(std::istream& in, mat4& m) {
    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 4; j++) {
        in >> m.coordinates[i][j];
      }
    }
    return in;
  }

  mat4 transpose() const {
    mat4 result;
    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 4; j++) {
        result.coordinates[i][j] = coordinates[j][i];
      }
    }
    return result;
  }

  static mat4 identity() {
    mat4 result;
    for (int i = 0; i < 4; i++) {
      result.coordinates[i][i] = 1;
    }
    return result;
  }
  static mat4 translate(const vec3& v) {
    mat4 result = identity();
    result.coordinates[0][3] = v[0];
    result.coordinates[1][3] = v[1];
    result.coordinates[2][3] = v[2];
    return result;
  }
  static mat4 scale(const vec3& v) {
    mat4 result;
    for (int i = 0; i < 3; i++) {
      result.coordinates[i][i] = v[i];
    }
    result.coordinates[3][3] = 1;
    return result;
  }
  static mat4 rotate(float angle, const vec3& axis) {
    mat4 result;
    float c = cos(angle);
    float s = sin(angle);
    float t = 1 - c;
    vec3 a = unit_vector(axis);
    result.coordinates[0][0] = t * a[0] * a[0] + c;
    result.coordinates[0][1] = t * a[0] * a[1] - s * a[2];
    result.coordinates[0][2] = t * a[0] * a[2] + s * a[1];
    result.coordinates[1][0] = t * a[0] * a[1] + s * a[2];
    result.coordinates[1][1] = t * a[1] * a[1] + c;
    result.coordinates[1][2] = t * a[1] * a[2] - s * a[0];
    result.coordinates[2][0] = t * a[0] * a[2] - s * a[1];
    result.coordinates[2][1] = t * a[1] * a[2] + s * a[0];
    result.coordinates[2][2] = t * a[2] * a[2] + c;
    result.coordinates[3][3] = 1;
    return result;
  }

  void rotate_x(float angle) { *this = *this * rotate(angle, vec3(1, 0, 0)); }
  void rotate_y(float angle) { *this = *this * rotate(angle, vec3(0, 1, 0)); }
  void rotate_z(float angle) { *this = *this * rotate(angle, vec3(0, 0, 1)); }
};

#endif  // MAT4_HPP