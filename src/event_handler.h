/** @file
 */
#ifndef EVENT_HANDLER_H
#define EVENT_HANDLER_H

#include "main.h"
#include "game_state.h"
#include "coord.h"

/** @enum Move_Status
 * Results from attempting to move a unit to a cell.
 */
typedef enum {
  MOVE_OUT_OF_BOUNDS, ///< The destination was out of bounds.
  MOVE_EMPTY_ORIGIN, ///< There was no unit to move at the origin.
  MOVE_SUCCESS, ///< The destination cell was unobstructed; entity moved.
  MOVE_OBSTRUCTED, ///< The destination is obstructed by an enemy or obstacle.
  MOVE_OCCUPIED, ///< The destination cell is occupied by an ally.
  MOVE_ONGOING ///< The Entity at this location is already in motion.
} Move_Status;

void handle_event(SDL_Event *event, Game_Data *game_data);
Move_Status move_entity(Coord_i origin, Coord_i dest, Game_Data *game_data);
void key_down(SDL_Keycode keycode, Game_Data *game_data);
void key_up(SDL_Keycode keycode, Game_Data *game_data);
void on_quit(Game_Data *game_data);

#endif
