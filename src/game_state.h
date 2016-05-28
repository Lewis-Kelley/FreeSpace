/** @file
 */
#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <stdint.h>
#include "battle_entity.h"
#include "explore_entity.h"
#include "coord.h"
#include "board.h"

#define GRID_ROWS 20 ///< The number of rows in the grid.
#define GRID_COLS 20 ///< The number of columns in the grid.

#define WIN_WIDTH 500 ///< The width of the window in pixels
#define WIN_HEIGHT 500 ///<The height of the window in pixels

#define STATES 3 ///< The number of major states in the program.

/**
 * The different types of major states.
 */
typedef enum {
  STATE_MENU = 1, ///< In a menu outside of the actual game.
  STATE_BATTLE = 2, ///< In a battle state.
  STATE_EXPLORE = 3 ///< In an exploration state.
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
 * List of masking powers of 2 representing the current state
 * of the keyboard.
 */
typedef enum {
  KEY_MOVE_RIGHT = 1,
  KEY_MOVE_UP = 2,
  KEY_MOVE_LEFT = 4,
  KEY_MOVE_DOWN = 8,
  KEY_MOVE = KEY_MOVE_RIGHT | KEY_MOVE_LEFT | KEY_MOVE_UP | KEY_MOVE_DOWN,

  KEY_CAM_RIGHT = 16,
  KEY_CAM_UP = 32,
  KEY_CAM_LEFT = 64,
  KEY_CAM_DOWN = 128,
  KEY_CAM = KEY_CAM_RIGHT | KEY_CAM_UP | KEY_CAM_LEFT | KEY_CAM_DOWN
} KEYS;

/**
 * Holds all the data needed by the game in a battle state.
 */
typedef struct {
  Game_State state; ///< The current state of the game.
  uint16_t keys; ///< A map of the current keys pressed.
  Board board; ///< The current board.
  Battle_Entity **turn_order; ///< Holds when each unit moves.
  Coord_f camera_pos; ///< The camera's pixel position.
  Coord_f camera_vel; ///< The camera velocity.
  uint16_t turn; ///< The current move (not round).
  uint16_t num_units; ///< The number of units
} Battle_Data;

/**
 * Holds all the data needed by the game in an explore state.
 */
typedef struct {
  Game_State state; ///< The current state of the game.
  Board board; ///< The current board.
  Coord_f camera_pos; ///< The camera's pixel position.
  Coord_f camera_vel; ///< The camera velocity.
} Explore_Data;

/**
 * Stores information about the current state of the game.
 */
typedef union {
  Battle_Data battle_data; ///< Holds data needed for battle states.
  Explore_Data explore_data; ///< Holds data on the exploration states.
} Game_Data;

extern Battle_Entity * bat_ent_lookup(Game_Data *data, uint16_t x, uint16_t y);
extern Explore_Entity * exp_ent_lookup(Game_Data *data, uint16_t x, uint16_t y);

extern int8_t bat_ent_put(Game_Data *data, Battle_Entity *ent);
extern int8_t exp_ent_put(Game_Data *data, Explore_Entity *ent);

extern int8_t bat_ent_put_coord(Game_Data *data, Battle_Entity *ent,
                                uint16_t x, uint16_t y);
extern int8_t exp_ent_put_coord(Game_Data *data, Explore_Entity *ent,
                                uint16_t x, uint16_t y);

extern Battle_Entity * bat_ent_remove(Game_Data *data, uint16_t x, uint16_t y);
extern Explore_Entity * exp_ent_remove(Game_Data *data, uint16_t x, uint16_t y);
#endif
