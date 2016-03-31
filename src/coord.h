/** @file
 */
#ifndef COORD_H
#define COORD_H

#include <stdint.h>

/** @struct Coord
 * Convenience 
 */
typedef struct {
  uint8_t x; ///< The horizontal component of this coordinate.
  uint8_t y; ///< The vertical component of this coordinate.
} Coord;

#endif
