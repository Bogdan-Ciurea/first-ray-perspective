/**
 * @file hittable_list.cpp
 * @author Bogdan Ciurea (ciureabogdanalexandru@gmail.com)
 * @brief This file contains the implementation of the hittable_list class
 * @version 0.1
 * @date 2024-10-03
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "objects/hittable_list.hpp"

hittable_list::hittable_list() {}

hittable_list::~hittable_list() { objects.clear(); }

void hittable_list::add(std::shared_ptr<hittable> object) {
  objects.push_back(object);
  bbox = aabb(bbox, object->bounding_box());
}

void hittable_list::clear() { objects.clear(); }

std::vector<std::shared_ptr<hittable>> hittable_list::get_objects() {
  return objects;
}

bool hittable_list::hit(const ray& r, const interval& interval,
                        hit_record& rec) const {
  hit_record temp_rec;
  bool hit_anything = false;
  auto closest_so_far = interval.max;

  for (const auto& object : objects) {
    if (object->hit(r, interval, temp_rec)) {
      hit_anything = true;
      if (temp_rec.t < closest_so_far) {
        closest_so_far = temp_rec.t;
        rec = temp_rec;
      }
    }
  }

  return hit_anything;
}

void hittable_list::move(const vec3& offset) {
  // TODO: Implement this
}

void hittable_list::rotate(const vec3& axis, float angle) {
  // TODO: Implement this
}
