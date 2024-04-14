/**
 * @file vec3.hpp
 * @author Bogdan Ciurea (ciureabogdanalexandru@gmail.com)
 * @brief Definition of the vec3 class
 * @version 0.1
 * @date 2024-04-14
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "vec3.hpp"

vec3::vec3() : e{0, 0, 0} {}

vec3::vec3(const vec3& v) : e{v.e[0], v.e[1], v.e[2]} {}

vec3::vec3(const double e0, const double e1, const double e2) : e{e0, e1, e2} {}

double vec3::operator[](int i) const {
  if (i < 0 || i > 2) {
    throw std::out_of_range("Index out of bounds");
  }
  return e[i];
}

bool vec3::operator==(const vec3& v) const {
  for (int i = 0; i < 3; i++) {
    if (abs(e[i] - v[i]) < std::numeric_limits<float>::epsilon()) {
      return false;
    }
  }
  return true;
}

bool vec3::operator!=(const vec3& v) const { return !(*this == v); }

vec3 vec3::operator+(const vec3& v) {
  return vec3(e[0] + v.e[0], e[1] + v[1], e[2] + v.e[2]);
}

vec3 vec3::operator-() const { return vec3(-e[0], -e[1], -e[2]); }

vec3 vec3::operator*(double t) const {
  return vec3(e[0] * t, e[1] * t, e[2] * t);
}

vec3 vec3::operator/(double t) const { return *this * (1 / t); }

vec3 vec3::cross(const vec3& v) const {
  return vec3(e[1] * v.e[2] - e[2] * v.e[1], e[2] * v.e[0] - e[0] * v.e[2],
              e[0] * v.e[1] - e[1] * v.e[0]);
}

vec3 vec3::unit_vector() const { return *this / length(); }

double vec3::dot(const vec3& v) const {
  return e[0] * v.e[0] + e[1] * v.e[1] + e[2] * v.e[2];
}

double vec3::length() const { return sqrt(length_squared()); }

double vec3::length_squared() const {
  return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
}

vec3& vec3::operator+=(const vec3& v) {
  e[0] += v.e[0];
  e[1] += v.e[1];
  e[2] += v.e[2];
  return *this;
}

vec3& vec3::operator-=(const vec3& v) {
  e[0] -= v.e[0];
  e[1] -= v.e[1];
  e[2] -= v.e[2];
  return *this;
}

vec3& vec3::operator*=(const double t) {
  e[0] *= t;
  e[1] *= t;
  e[2] *= t;
  return *this;
}

vec3& vec3::operator/=(const double t) { return *this *= 1 / t; }

std::ostream& operator<<(std::ostream& out, const vec3& v) {
  return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}

std::istream& operator>>(std::istream& in, vec3& v) {
  return in >> v.e[0] >> v.e[1] >> v.e[2];
}
