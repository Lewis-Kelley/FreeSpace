/** @file
 */

#ifndef EXPLORE_ENTITY_H
#define EXPLORE_ENTITY_H

#include "image.h"
#include "team.h"
#include "coord.h"

/**
 * Stores information needed for a unit in explore state.
 * Will include dailog, position, movement, etc. info.
 */
typedef struct {
  Image img; ///< The image representing this entity.
  Team team; ///< The team that this unit is on. (Used for collisions.)
  Coord_f pos; ///< The grid position of this entity.
  Coord_f vel; ///< The velocity of this entity (for animation purposes).
} Explore_Entity;

#endif
