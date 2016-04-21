/** @file
 */
#ifndef EVENT_HANDLER_H
#define EVENT_HANDLER_H

#include "../main.h"
#include "game_state.h"
#include "coord.h"

void handle_event(SDL_Event *event, Game_Data *game_data);
void key_down(SDL_Keycode keycode, Game_Data *game_data);
void key_up(SDL_Keycode keycode, Game_Data *game_data);
void on_quit(Game_Data *game_data);

#endif
