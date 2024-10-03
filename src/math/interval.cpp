/**
 * @file interval.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2024-10-03
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "math/interval.hpp"

const interval interval::empty = interval(+infinity, -infinity);
const interval interval::universe = interval(-infinity, +infinity);