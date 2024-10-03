#include "objects/ObjectsList.hpp"

ObjectsList::ObjectsList() {}

ObjectsList::~ObjectsList() { objects.clear(); }

void ObjectsList::add(std::shared_ptr<Object> object) {
  objects.push_back(object);
}

void ObjectsList::clear() { objects.clear(); }

std::vector<std::shared_ptr<Object>> ObjectsList::get_objects() {
  return objects;
}

bool ObjectsList::intersect(const ray& r, const interval& interval,
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

void ObjectsList::move(const vec3& offset) {
  for (const auto& object : objects) {
    object->move(offset);
  }
}

void ObjectsList::rotate(const vec3& axis, float angle) {
  for (const auto& object : objects) {
    object->rotate(axis, angle);
  }
}
