/**
 * @file cornell_box.hpp
 * @author Bogdan Ciurea (ciureabogdanalexandru@gmail.com)
 * @brief Implementing the cornell box scene
 * @version 0.1
 * @date 2024-10-26
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef CONSTRUCTIONS_BOX_HPP
#define CONSTRUCTIONS_BOX_HPP

#include "Window.hpp"
#include "objects/quad.hpp"
#include "objects/sphere.hpp"

/**
 * @brief Returns the 3D box (six sides) that contains the two opposite vertices
 a & b.
 *
 * @param a The first vertex
 * @param b The second vertex
 * @param mat The material of the box
 * @return shared_ptr<hittable_list> The list of objects in the scene
 */
inline shared_ptr<hittable_list> box(const vec3& a, const vec3& b,
                                     shared_ptr<material> mat) {
  auto sides = make_shared<hittable_list>();

  // Construct the two opposite vertices with the minimum and maximum
  // coordinates.
  auto min = vec3(std::fmin(a.x(), b.x()), std::fmin(a.y(), b.y()),
                  std::fmin(a.z(), b.z()));
  auto max = vec3(std::fmax(a.x(), b.x()), std::fmax(a.y(), b.y()),
                  std::fmax(a.z(), b.z()));

  auto dx = vec3(max.x() - min.x(), 0, 0);
  auto dy = vec3(0, max.y() - min.y(), 0);
  auto dz = vec3(0, 0, max.z() - min.z());

  sides->add(make_shared<quad>(vec3(min.x(), min.y(), max.z()), dx, dy,
                               mat));  // front
  sides->add(make_shared<quad>(vec3(max.x(), min.y(), max.z()), -dz, dy,
                               mat));  // right
  sides->add(make_shared<quad>(vec3(max.x(), min.y(), min.z()), -dx, dy,
                               mat));  // back
  sides->add(make_shared<quad>(vec3(min.x(), min.y(), min.z()), dz, dy,
                               mat));  // left
  sides->add(make_shared<quad>(vec3(min.x(), max.y(), max.z()), dx, -dz,
                               mat));  // top
  sides->add(make_shared<quad>(vec3(min.x(), min.y(), min.z()), dx, dz,
                               mat));  // bottom

  return sides;
}

#endif  // CONSTRUCTIONS_BOX_HPP
