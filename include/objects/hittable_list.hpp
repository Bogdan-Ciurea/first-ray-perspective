/**
 * @file hittable_list.hpp
 * @author Bogdan Ciurea (ciureabogdanalexandru@gmail.com)
 * @brief Declaration of the hittable_list class
 * @version 0.1
 * @date 2024-04-26
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef OBJECTSLIST_HPP
#define OBJECTSLIST_HPP

#include "hittable.hpp"

class hittable_list : public hittable {
 public:
  /**
   * @brief Construct a new hittable_list object
   *
   */
  hittable_list();
  hittable_list(shared_ptr<hittable> object) { add(object); }

  /**
   * @brief Destroy the hittable_list object
   *
   */
  ~hittable_list();

  /**
   * @brief Add an object to the list
   *
   * @param object The object to add
   */
  void add(shared_ptr<hittable> object);

  void clear();

  /**
   * @brief Get the list of objects
   *
   * @return std::vector<std::shared_ptr<hittable>> The list of objects
   */
  vector<shared_ptr<hittable>> get_objects();

  /**
   * @brief Get the intersection of the objects in the list
   *
   * @param r The ray to intersect with
   * @param interval The interval in which the intersection should be
   * @param rec The hit record
   * @return bool True if the ray intersects any object in the list, false
   * otherwise
   */
  bool hit(const ray& r, const interval& interval,
           hit_record& rec) const override;

  void move(const vec3& offset) override;
  void rotate(const vec3& axis, float angle) override;

  aabb bounding_box() const override { return bbox; }

 private:
  vector<shared_ptr<hittable>> objects;
  aabb bbox;
};

#endif  // OBJECTSLIST_HPP
