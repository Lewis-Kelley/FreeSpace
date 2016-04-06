/** @file
 */
#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <stdint.h>
#include "battle_entity.h"
#include "explore_entity.h"
#include "coord.h"

#define GRID_ROWS 20 ///< The number of rows in the grid.
#define GRID_COLS 20 ///< The number of columns in the grid.

#define WIN_WIDTH 1000 ///< The width of the window in pixels
#define WIN_HEIGHT 1000 ///<The height of the window in pixels

#define STATES 3 ///< The number of major states in the program.

/**
 * The different types of major states.
 */
typedef enum {
  STATE_MENU = 0, ///< In a menu outside of the actual game.
  STATE_BATTLE = 1, ///< In a battle state.
  STATE_EXPLORE = 2 ///< In an exploration state.
} Major_State;

/**
 * Represents the current state the game is in.
 */
typedef enum {
  GAME_STOPPED = 0, ///< Game is stopping.
  GAME_BATTLE_MOVE = 0 * STATES + STATE_BATTLE, ///< Moving a unit.
  GAME_BATTLE_TARGETING = 1 * STATES + STATE_BATTLE, ///< Selecting target.
  GAME_BATTLE_SURVEY = 2 * STATES + STATE_BATTLE, ///< Free camera in a battle.
  GAME_BATTLE_ATTACK = 3 * STATES + STATE_BATTLE, ///< An attack is ongoing.
  GAME_EXPLORE_MOVE = 0 * STATES + STATE_EXPLORE, ///< Just walking.
  GAME_EXPLORE_TALK = 1 * STATES + STATE_EXPLORE, ///< Talking with an NPC.
  GAME_EXPLORE_SEARCH = 2 * STATES + STATE_EXPLORE, ///< Searching an object.
  GAME_MAIN_MENU = 0 * STATES + STATE_MENU ///< Statup menu.
} Game_State;

/**
 * Stores information about the current state of the game.
 */
typedef union {
  struct {
    Game_State state; ///< The current state of the game.
    double delta; ///< The time since the last tick.
    double last_time; ///< The time of the previous tick.
    Battle_Entity **board; ///< An array of Entity pointers.
    Battle_Entity **turn_order; ///< Holds when each unit moves.
    Coord_f camera; ///< The camera position.
    int cols; ///< The number of columns in the current board.
    int rows; ///< The number of rows in the current board.
    int turn; ///< The current move (not round).
    int num_units; ///< The number of units
  } battle_data; ///< Holds data on the battle states.
  struct {
    Game_State state; ///< The current state of the game.
    double delta; ///< The time since the last tick.
    double last_time; ///< The time of the previous tick.
    Explore_Entity **board; ///< An array of Entity pointers.
    Coord_f camera; ///< The camera position.
    int cols; ///< The number of columns in the current board.
    int rows; ///< The number of rows in the current board.
  } explore_data; ///< Holds data on the exploration states.
} Game_Data;

#endif
