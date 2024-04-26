/**
 * @file vec4.hpp
 * @author Bogdan Ciurea (ciureabogdanalexandru@gmail.com)
 * @brief Definition of the vec4 class
 * @version 0.1
 * @date 2024-04-14
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "math/vec4.hpp"

vec4::vec4() : e{0, 0, 0, 0} {}

vec4::vec4(const vec3& v) : e{v.e[0], v.e[1], v.e[2], 0} {}

vec4::vec4(const vec3& v, double w) : e{v.e[0], v.e[1], v.e[2], w} {}

vec4::vec4(const vec4& v) : e{v.e[0], v.e[1], v.e[2], v.e[3]} {}

vec4::vec4(const double e0, const double e1, const double e2, const double e3)
    : e{e0, e1, e2, e3} {}

void vec4::clamp_color() {
  for (int i = 0; i < 3; i++) {
    e[i] = std::min(255.0f, std::max(0.0f, float(e[i])));
  }
}

double vec4::operator[](int i) const {
  if (i < 0 || i > 2) {
    throw std::out_of_range("Index out of bounds");
  }
  return e[i];
}

bool vec4::operator==(const vec4& v) const {
  for (int i = 0; i < 4; i++) {
    if (abs(e[i] - v[i]) < std::numeric_limits<float>::epsilon()) {
      return false;
    }
  }
  return true;
}

bool vec4::operator!=(const vec4& v) const { return !(*this == v); }

vec4 vec4::operator+(const vec4& v) {
  return vec4(e[0] + v.e[0], e[1] + v.e[1], e[2] + v.e[2], e[3] + v.e[3]);
}

vec4 vec4::operator-() const { return vec4(-e[0], -e[1], -e[2], -e[3]); }

vec4 vec4::operator*(double t) const {
  return vec4(e[0] * t, e[1] * t, e[2] * t, e[3] * t);
}

vec4 vec4::operator/(double t) const { return *this * (1 / t); }

vec4 vec4::cross(const vec4& v) const {
  return vec4(e[1] * v.e[2] - e[2] * v.e[1], e[2] * v.e[0] - e[0] * v.e[2],
              e[0] * v.e[1] - e[1] * v.e[0], 0);
}

vec4 vec4::unit_vector() const { return *this / length(); }

double vec4::dot(const vec4& v) const {
  return e[0] * v.e[0] + e[1] * v.e[1] + e[2] * v.e[2] + e[3] * v.e[3];
}

double vec4::length() const { return sqrt(length_squared()); }

double vec4::length_squared() const {
  return e[0] * e[0] + e[1] * e[1] + e[2] * e[2] + e[3] * e[3];
}

vec4& vec4::operator+=(const vec4& v) {
  e[0] += v.e[0];
  e[1] += v.e[1];
  e[2] += v.e[2];
  e[3] += v.e[3];
  return *this;
}

vec4& vec4::operator-=(const vec4& v) {
  e[0] -= v.e[0];
  e[1] -= v.e[1];
  e[2] -= v.e[2];
  e[3] -= v.e[3];
  return *this;
}

vec4& vec4::operator*=(const double t) {
  e[0] *= t;
  e[1] *= t;
  e[2] *= t;
  e[3] *= t;
  return *this;
}

vec4& vec4::operator/=(const double t) { return *this *= 1 / t; }

std::ostream& operator<<(std::ostream& out, const vec4& v) {
  return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2] << ' ' << v.e[3];
}

std::istream& operator>>(std::istream& in, vec4& v) {
  return in >> v.e[0] >> v.e[1] >> v.e[2] >> v.e[3];
}
