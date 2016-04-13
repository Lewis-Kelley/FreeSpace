/** @file
 */
#include "game_state.h"

/**
 * Returns a pointer to the Battle_Entity at the given row and column.
 *
 * @param data The current state of the game.
 * @param x The x coordinate of the Battle_Entity to find.
 * @param y The y coordinate of the Battle_Entity to find.
 * @return A pointer to the Battle_Entity at the given row and column or NULL
 * if the cell is empty or the parameters are invalid.
 */
Battle_Entity * bat_ent_lookup(Game_Data *data, uint16_t x, uint16_t y) {
  if(data == NULL || data->battle_data.state % STATES != STATE_BATTLE
     || y >= data->battle_data.rows || x >= data->battle_data.cols) {
    return NULL;
  }

  return data->battle_data.board[y * data->battle_data.cols + x];
}

/**
 * Returns a pointer to the Explore_Entity at the given row and column.
 *
 * @param data The current state of the game.
 * @param x The x coordinate of the Explore_Entity to find.
 * @param y The y coordinate of the Explore_Entity to find.
 * @return A pointer to the Explore_Entity at the given row and column or NULL
 * if the cell is empty or the parameters are invalid.
 */
Explore_Entity * exp_ent_lookup(Game_Data *data, uint16_t x, uint16_t y) {
  if(data == NULL || data->explore_data.state % STATES != STATE_EXPLORE
     || y >= data->explore_data.rows || x >= data->explore_data.cols) {
    return NULL;
  }

  return data->explore_data.board[y * data->explore_data.cols + x];
}

/**
 * Puts the given Battle_Entity at the appropriate spot in
 * the battle_data.board.
 * 
 * @param data The current state of the game.
 * @param ent A pointer to the Battle_Entity to be added.
 * @return 0 if successfully added, 1 if the cell was occupied,
 * 2 if invalid parameters.
 */
int8_t bat_ent_put(Game_Data *data, Battle_Entity *ent) {
  if(data == NULL || ent == NULL
     || data->battle_data.state % STATES != STATE_BATTLE
     || ent->pos.x >= data->battle_data.cols || ent->pos.x < 0
     || ent->pos.y >= data->battle_data.rows || ent->pos.y < 0) {
    return 2;
  }

  if(bat_ent_lookup(data, (uint16_t)ent->pos.y, (uint16_t)ent->pos.x) != NULL) {
    return 1;
  }

  data->battle_data.board[(uint16_t)ent->pos.y *data->battle_data.cols
                          + (uint16_t)ent->pos.x] = ent;

  return 0;
}

/**
 * Puts the given Explore_Entity at the appropriate spot in
 * the explore_data.board.
 * 
 * @param data The current state of the game.
 * @param ent A pointer to the Explore_Entity to be added.
 * @return 0 if successfully added, 1 if the cell was occupied,
 * 2 if invalid parameters.
 */
int8_t exp_ent_put(Game_Data *data, Explore_Entity *ent) {
  if(data == NULL || ent == NULL
     || data->battle_data.state % STATES != STATE_BATTLE
     || ent->pos.x >= data->battle_data.cols || ent->pos.x < 0
     || ent->pos.y >= data->battle_data.rows || ent->pos.y < 0) {
    return 2;
  }

  if(exp_ent_lookup(data, (uint16_t)ent->pos.y, (uint16_t)ent->pos.x) != NULL) {
    return 1;
  }

  data->explore_data.board[(uint16_t)ent->pos.y *data->explore_data.cols
                          + (uint16_t)ent->pos.x] = ent;

  return 0;
}
