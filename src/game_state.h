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

/**
 * Represents the current state the game is in.
 * Grouped into three groups by their divisibility by 3.
 * % 3 = 0: Various menu things that are outside the main two modes.
 * % 3 = 1: Battle mode states.
 * % 3 = 2: Exploration mode states.
 */
typedef enum {
  GAME_STOPPED = 0, ///< Game is stopping.
  GAME_BATTLE_MOVE = 1, ///< Moving a unit.
  GAME_BATTLE_TARGETING = 4, ///< Target selection in a battle.
  GAME_BATTLE_SURVEY = 7, ///< Free camera in a battle.
  GAME_BATTLE_ATTACK = 10, ///< An attack is ongoing.
  GAME_EXPLORE_MOVE = 2, ///< Explore state when walking around.
  GAME_EXPLORE_TALK = 5, ///< Talking with an NPC.
  GAME_EXPLORE_SEARCH = 8 ///< Searching an object.
} Game_State;

/**
 * Stores information about the current state of the game.
 */
typedef struct {
  Game_State state; ///< The current state of the game.
  union {
    struct {
      Battle_Entity **board; ///< The current state of the board.
      double x; ///< The current x position of the camera.
      double y; ///< The current y position of the camera.
      int columns; ///< The number of columns in the current board.
      int rows; ///< The number of rows in the current board.
    } battle_data; ///< Holds data on the battle states.
    struct {
      Explore_Entity **board; ///< The current state of the board.
      double x; ///< The current x position of the camera.
      double y; ///< The current y position of the camera.
      int columns; ///< The number of columns in the current board.
      int rows; ///< The number of rows in the current board.
    } explore_data; ///< Holds data on the exploration states.
  } data; ///< The relevant data for the current Game_State.
} Game_Data;

#endif
