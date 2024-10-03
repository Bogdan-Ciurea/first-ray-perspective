/**
 * @file interval.hpp
 * @author Bogdan Ciurea (ciureabogdanalexandru@gmail.com)
 * @brief This file contains the declaration of the Interval class that will be
 * used to represent intervals in the scene as well as random number generation
 * @version 0.1
 * @date 2024-10-03
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef INTERVAL_HPP
#define INTERVAL_HPP

#include <utils.hpp>

class interval {
 public:
  float min, max;

  interval() : min(-infinity), max(+infinity) {}
  interval(float min, float max) : min(min), max(max) {}

  bool contains(float x) const { return x >= min && x <= max; }
  bool contains(const interval& i) const {
    return i.min >= min && i.max <= max;
  }

  bool surrounds(const float x) const { return x > min && x < max; }

  interval expand(float delta) const {
    const float padding = delta / 2.f;
    return interval(min - padding, max + padding);
  }

  float size() const { return max - min; }
};

#endif
