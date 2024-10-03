/**
 * @file aabb.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2024-10-03
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "objects/aabb.hpp"

const aabb aabb::empty =
    aabb(interval::empty, interval::empty, interval::empty);
const aabb aabb::universe =
    aabb(interval::universe, interval::universe, interval::universe);
