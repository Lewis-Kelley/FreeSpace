/** @file
 */

#ifndef UPDATE_H
#define UPDATE_H

#include "battle_entity.h"
#include "game_state.h"
#include "main.h"

void update_world(Game_Data *game_data);
void battle_entity_update(Battle_Entity *ent, Game_Data *game_data);

#endif
