/** @file
 */

#ifndef BATTLE_ENTITY_H
#define BATTLE_ENTITY_H

#include <stdint.h>
#include "image.h"
#include "team.h"
#include "coord.h"

/**
 * Stores all the necessary information about a unit.
 */
typedef struct {
  Image img; ///< The image representing this entity.
  Team team; ///< The team this entity currently is.
  Coord_i pos; ///< The grid position of this entity.
} Battle_Entity;

#endif
