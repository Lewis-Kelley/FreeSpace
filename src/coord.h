/** @file
 */
#ifndef COORD_H
#define COORD_H

#include <stdint.h>

/**
 * Holds a pair of doubles that represent a set of coordinates.
 */
typedef struct {
  double x; ///< The horizontal component of this coordinate.
  double y; ///< The vertical component of this coordinate.
} Coord_f;

/**
 * Holds a pair of bytes that represent a set of coordinates.
 */
typedef struct {
  uint8_t x; ///< The horizontal component of this coordinate.
  uint8_t y; ///< The vertical component of this coordinate.
} Coord_i;

#endif
