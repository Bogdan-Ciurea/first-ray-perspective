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

#include "math/vec3.hpp"

/**
 * @brief Create a color object. Keep in mind that you might want to scale the
 * color values by 255 when using this function.
 *
 * @param r  The red component
 * @param g  The green component
 * @param b  The blue component
 * @param a  The alpha component
 * @return Color  The color object
 */
Color create_color(int r, int g, int b, int a) {
  r = clamp(abs(r), 0, 255);
  g = clamp(abs(g), 0, 255);
  b = clamp(abs(b), 0, 255);
  a = clamp(abs(a), 0, 255);

  return Color{(uchar)r, (uchar)g, (uchar)b, (uchar)a};
}