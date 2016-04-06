/** @file
 */

#ifndef BATTLE_ENTITY_H
#define BATTLE_ENTITY_H

#include <stdint.h>
#include "../hashmap/stack.h"
#include "image.h"
#include "team.h"
#include "coord.h"

/**
 * Stores all the necessary information about a unit.
 */
typedef struct {
  Image img; ///< The image representing this entity.
  Team team; ///< The team this entity currently is.
  Coord_f pos; ///< The grid position of this entity.
  Coord_f vel; ///< The velocity of this entity (for animation purposes).
  Stack move_queue; ///< Stack of targeted Coord_i's queued up to complete.
} Battle_Entity;

#endif
