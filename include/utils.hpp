#ifndef RTWEEKEND_H
#define RTWEEKEND_H

// Common Headers

#include <cmath>
#include <iostream>
#include <limits>
#include <memory>
#include <vector>

// C++ Std Usings

using std::make_shared;
using std::shared_ptr;
using std::sqrt;
using std::vector;

// Defining aliases
typedef unsigned int uint;
typedef unsigned char uchar;

// Constants

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

// Utility Functions

inline double degrees_to_radians(double degrees) {
  return degrees * pi / 180.0;
}

inline double radians_to_degrees(double radians) {
  return radians * 180.0 / pi;
}

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
  unsigned char r = (uchar)clamp(c1.r + c2.r, 0.0f, 255.0f);
  unsigned char g = (uchar)clamp(c1.g + c2.g, 0.0f, 255.0f);
  unsigned char b = (uchar)clamp(c1.b + c2.b, 0.0f, 255.0f);
  unsigned char a = (uchar)clamp(c1.a + c2.a, 0.0f, 255.0f);

  return Color{r, g, b, a};
}

// Operator overloading for Color multiplication with a float
inline Color operator*(float f, const Color& c) {
  unsigned char r = (uchar)clamp(f * c.r, 0.0f, 255.0f);
  unsigned char g = (uchar)clamp(f * c.g, 0.0f, 255.0f);
  unsigned char b = (uchar)clamp(f * c.b, 0.0f, 255.0f);
  unsigned char a = (uchar)clamp(f * c.a, 0.0f, 255.0f);

  return Color{r, g, b, a};
}

#endif