#ifndef EVENT_HANDLER_H
#define EVENT_HANDLER_H

#include "main.h"
#include "game_state.h"

void handle_event(SDL_Event *event, Game_Data *game_data);
void key_down(SDL_keysym keysym, Game_Data *game_data);
void on_quit(Game_Data *game_data);

#endif
