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

void vec4::clamp_color() {
  for (int i = 0; i < 3; i++) {
    e[i] = std::min(255.0f, std::max(0.0f, float(e[i])));
  }
}

inline std::istream &operator>>(std::istream &is, vec4 &t) {
  is >> t.e[0] >> t.e[1] >> t.e[2] >> t.e[3];
  return is;
}

inline std::ostream &operator<<(std::ostream &os, const vec4 &t) {
  os << t.e[0] << " " << t.e[1] << " " << t.e[2] << " " << t.e[3];
  return os;
}
