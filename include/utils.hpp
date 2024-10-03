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

#define NO_RAYS_PER_PIXEL 1
#define TARGET_FPS 30

// Common Headers
#include <chrono>
#include <cmath>
#include <iostream>
#include <limits>
#include <memory>
#include <numeric>
#include <random>
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
// auto now = std::chrono::high_resolution_clock::now();

// Defining aliases
typedef unsigned int uint;
typedef unsigned char uchar;

// Constants
const float infinity = std::numeric_limits<float>::infinity();

// Utility Functions

// Returns a random real in [0,1).
inline float random_float(float min = 0, float max = 1) {
  const float rand = (float)GetRandomValue(0, 1000) / 1000.0f;
  return min + (max - min) * rand;
}

// Returns a random integer in [min,max].
inline int random_int(int min, int max) { return GetRandomValue(min, max); }

inline float clamp(float x, float min, float max) {
  if (x < min) return min;
  if (x > max) return max;
  return x;
}

#endif  // UTILS_HPP
