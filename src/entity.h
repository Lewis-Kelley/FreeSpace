/** @file
 */

#ifndef ENTITY_H
#define ENTITY_H

#include <stdint.h>
#include "image.h"
#include "team.h"

/** @struct Entity
 * Stores all the necessary information about a unit.
 */
typedef struct {
  Image img; ///< The image representing this entity.
  Team team; ///< The team this entity currently is.
} Entity;

#endif
