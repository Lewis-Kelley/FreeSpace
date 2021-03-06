/** @file
 */

#ifndef UPDATE_H
#define UPDATE_H

#include <stdint.h>
#include "battle_entity.h"
#include "event_handler.h"
#include "game_state.h"
#include "image_update.h"
#include "../main.h"

void update_world(Game_Data *game_data, double delta);
void battle_entity_key_update(Battle_Entity *ent, Battle_Data *battle_data);
void battle_entity_update(Battle_Entity *ent, Battle_Data *battle_data,
                          double delta);

#endif
