#ifndef EVENT_HANDLER_H
#define EVENT_HANDLER_H

#include "main.h"
#include "game_state.h"

void handle_event(SDL_Event *event, Game_State *state);
void on_quit(Game_State *state);

#endif
