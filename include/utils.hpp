/**
 * @file utils.hpp
 * @author Bogdan Ciurea (ciureabogdanalexandru@gmail.com)
 * @brief Utility functions and constants used throughout the project
 * @version 0.1
 * @date 2024-06-24
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef UTILS_HPP
#define UTILS_HPP

#define NO_RAYS_PER_PIXEL 4
#define TARGET_FPS 30

// Common Headers
#include <chrono>
#include <cmath>
#include <iostream>
#include <limits>
#include <memory>
#include <unordered_set>
#include <vector>

#include "raylib.h"

// C++ Std Usings

using std::make_shared;
using std::shared_ptr;
using std::sqrt;
using std::vector;
using Secondsf = std::chrono::duration<float, std::ratio<1>>;
using Clock = std::chrono::steady_clock;

// Defining aliases
typedef unsigned int uint;
typedef unsigned char uchar;

// Constants
const double infinity = std::numeric_limits<double>::infinity();

// Utility Functions

inline double random_double() {
  // Returns a random real in [0,1).
  return rand() / (RAND_MAX + 1.0);
}

inline double clamp(double x, double min, double max) {
  if (x < min) return min;
  if (x > max) return max;
  return x;
}

// Operator overloading for Color addition
inline Color operator+(const Color& c1, const Color& c2) {
  uchar r = (uchar)clamp(c1.r + c2.r, 0.0f, 255.0f);
  uchar g = (uchar)clamp(c1.g + c2.g, 0.0f, 255.0f);
  uchar b = (uchar)clamp(c1.b + c2.b, 0.0f, 255.0f);
  uchar a = (uchar)clamp(std::max(c1.a, c2.a), 0.0f, 255.0f);

  return Color{r, g, b, a};
}

// Operator overloading for Color multiplication with a float
inline Color operator*(float f, const Color& c) {
  uchar r = (uchar)clamp(f * c.r, 0.0f, 255.0f);
  uchar g = (uchar)clamp(f * c.g, 0.0f, 255.0f);
  uchar b = (uchar)clamp(f * c.b, 0.0f, 255.0f);
  uchar a = (uchar)clamp(c.a, 0.0f, 255.0f);

  return Color{r, g, b, a};
}

// Operator overloading for Color divider with a float
inline Color operator/(const Color& c, float f) { return (1 / f) * c; }

#endif  // UTILS_HPP
