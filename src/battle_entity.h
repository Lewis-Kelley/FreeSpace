/** @file
 */

#ifndef BATTLE_ENTITY_H
#define BATTLE_ENTITY_H

#include <stdint.h>
#include "image.h"
#include "team.h"

/**
 * Stores all the necessary information about a unit.
 */
typedef struct {
  Image img; ///< The image representing this entity.
  Team team; ///< The team this entity currently is.
} Battle_Entity;

#endif
