/**
 * @file ObjectsList.hpp
 * @author Bogdan Ciurea (ciureabogdanalexandru@gmail.com)
 * @brief Declaration of the ObjectsList class
 * @version 0.1
 * @date 2024-04-26
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef OBJECTSLIST_HPP
#define OBJECTSLIST_HPP

#include "Object.hpp"

class ObjectsList : public Object {
 public:
  /**
   * @brief Construct a new ObjectsList object
   *
   */
  ObjectsList();

  /**
   * @brief Destroy the ObjectsList object
   *
   */
  ~ObjectsList();

  /**
   * @brief Add an object to the list
   *
   * @param object The object to add
   */
  void add(shared_ptr<Object> object);

  void clear();

  /**
   * @brief Get the list of objects
   *
   * @return std::vector<std::shared_ptr<Object>> The list of objects
   */
  vector<shared_ptr<Object>> get_objects();

  /**
   * @brief Get the intersection of the objects in the list
   *
   * @param r The ray to intersect with
   * @param t_min The minimum t value
   * @param t_max The maximum t value
   * @param rec The hit record
   * @return bool True if the ray intersects any object in the list, false
   * otherwise
   */
  bool intersect(const ray& r, const float t_min, const float t_max,
                 hit_record& rec);

  void move(const vec3& offset);
  void rotate(const vec3& axis, float angle);

 private:
  vector<shared_ptr<Object>> objects;
};

#endif  // OBJECTSLIST_HPP
