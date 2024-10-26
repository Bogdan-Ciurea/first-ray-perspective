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

#ifndef CONSTRUCTIONS_CORNELL_BOX_HPP
#define CONSTRUCTIONS_CORNELL_BOX_HPP

#include "Window.hpp"
#include "objects/quad.hpp"
#include "objects/sphere.hpp"

/**
 * @brief function that creates a cornell box
 * NOTE: The function does not create a BVH node
 *
 * @return hittable_list The list of objects in the scene
 */
inline hittable_list cornell_box(shared_ptr<camera> cam, int size) {
  hittable_list world;

  cam->movement_per_second = sqrt(size);

  // Materials
  TraceLog(LOG_INFO, "Creating MATERIALS");
  auto ivory = make_shared<lambertian>(vec3(0.4f, 0.4f, 0.3f));
  auto red_rubber = make_shared<lambertian>(vec3(0.3f, 0.1f, 0.1f));
  auto green_rubber = make_shared<lambertian>(vec3(0.3f, 0.4f, 0.1f));
  auto light = make_shared<diffuse_light>(vec3(15.f, 15.f, 15.f));

  // Quads
  TraceLog(LOG_INFO, "Creating OBJECTS");
  // Left wall (size units wide)
  world.add(make_shared<quad>(vec3(-size * .5f, -size * .5f, -size * .5f),
                              vec3(0, 0, -size), vec3(0, size, 0), red_rubber));
  // Back wall (size units wide)
  world.add(make_shared<quad>(vec3(-size * .5f, -size * .5f, -size * 1.5f),
                              vec3(size, 0, 0), vec3(0, size, 0), ivory));
  // Right wall (size units wide)
  world.add(make_shared<quad>(vec3(size * .5f, -size * .5f, -size * 1.5f),
                              vec3(0, 0, size), vec3(0, size, 0),
                              green_rubber));
  // Ceiling (size units wide)
  world.add(make_shared<quad>(vec3(-size * .5f, size * .5f, -size * 1.5f),
                              vec3(size, 0, 0), vec3(0, 0, size), ivory));
  // Light (as a 50x50 centered square on the ceiling)
  world.add(
      make_shared<quad>(vec3(-size / 4.f, size / 2 - 0.01f, -size * 1.25f),
                        vec3(size * .5f, 0, 0), vec3(0, 0, size * .5f),
                        light));  // Centered light source
  // Floor (size units wide)
  world.add(make_shared<quad>(vec3(-size * .5f, -size * .5f, -size * .5f),
                              vec3(size, 0, 0), vec3(0, 0, -size), ivory));

  return world;
}

#endif  // CONSTRUCTIONS_CORNELL_BOX_HPP
