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

bool hittable_list::intersect(const ray& r, const interval& interval,
                              hit_record& rec) {
  hit_record temp_rec;
  bool hit_anything = false;
  auto closest_so_far = interval.max;

  for (const auto& object : objects) {
    if (object->intersect(r, interval, temp_rec)) {
      hit_anything = true;
      closest_so_far = temp_rec.t;
      rec = temp_rec;
    }
  }

  return hit_anything;
}

void hittable_list::move(const vec3& offset) {
  for (const auto& object : objects) {
    object->move(offset);
  }
}

void hittable_list::rotate(const vec3& axis, float angle) {
  for (const auto& object : objects) {
    object->rotate(axis, angle);
  }
}
