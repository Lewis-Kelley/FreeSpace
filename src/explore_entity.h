/** @file
 */

#ifndef EXPLORE_ENTITY_H
#define EXPLORE_ENTITY_H

#include "image.h"

/**
 * Stores information needed for a unit in explore state.
 * Will include dailog, position, movement, etc. info.
 */
typedef struct {
  Image img; ///< The image representing this entity.
} Explore_Entity;

#endif
