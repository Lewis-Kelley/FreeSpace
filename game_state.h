/** @file
 * Holds the Game_State struct definition.
 */
#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <stdint.h>
#include "cell_state.h"

#define GRID_ROWS 20 ///< The number of rows in the grid.
#define GRID_COLS 20 ///< The number of columns in the grid.

/** @struct Game_State
 * Stores information about the current state of the game.
 */
typedef struct {
    uint8_t running; ///< 1 if the game is still running, 0 if stopping
    uint8_t turn; ///< 0 if player's turn, 1 if enemy's.
    Cell_State board[GRID_ROWS][GRID_COLS]; ///< The current state of the board.
} Game_State;

#endif
