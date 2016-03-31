/** @file
 */
#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <stdint.h>
#include "entity.h"

#define GRID_ROWS 20 ///< The number of rows in the grid.
#define GRID_COLS 20 ///< The number of columns in the grid.

/** @struct Game_State
 * Stores information about the current state of the game.
 */
typedef struct {
  Entity board[GRID_COLS][GRID_ROWS]; ///< The current state of the board.
  uint8_t running; ///< 1 if the game is still running, 0 if stopping
} Game_State;

#endif
