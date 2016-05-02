#include <stdio.h>
#include "hashmap/stack.h"
#include "hashmap/hashmap.h"
#include "src/game_state.h"
#include "src/update.h"
#include "main.h"

#define CTEST_MAIN

// uncomment lines below to enable/disable features. See README.md for details
#define CTEST_SEGFAULT
//#define CTEST_NO_COLORS
#define CTEST_COLOR_OK

#include "ctest.h"

CTEST(battle_entity, basic_battle_entity_key_update) {
  Game_Data game_data;
  int sel = 23;

  game_data.battle_data.state = GAME_BATTLE_MOVE;
  game_data.battle_data.keys = 0;
  game_data.battle_data.camera_pos.x = 0.0;
  game_data.battle_data.camera_pos.y = 0.0;
  game_data.battle_data.camera_vel.x = 0.0;
  game_data.battle_data.camera_vel.y = 0.0;
  game_data.battle_data.cols = 10;
  game_data.battle_data.rows = 15;
  game_data.battle_data.board = malloc(game_data.battle_data.cols
                                       * game_data.battle_data.rows
                                       * sizeof *game_data.battle_data.board);
  for(int i = 0; i < game_data.battle_data.cols
        * game_data.battle_data.rows; i++) {
    game_data.battle_data.board[i]
      = malloc(sizeof **game_data.battle_data.board);
    game_data.battle_data.board[i]->team = TEAM_EMPTY;
    game_data.battle_data.board[i]->pos.x
      = i % game_data.battle_data.cols;
    game_data.battle_data.board[i]->pos.y
      = i / game_data.battle_data.cols;
    game_data.battle_data.board[i]->vel = (Coord_f){0.0, 0.0};
    game_data.battle_data.board[i]->move_queue.head = NULL;
    game_data.battle_data.board[i]->move_queue.key_size = 0;
  }

  Battle_Entity *ent = game_data.battle_data.board[sel];
  ent->team = TEAM_SELECTED;
  game_data.battle_data.keys = 0;

  for(int i = 0; i < 4; i++) {
    battle_entity_key_update(ent, &(game_data.battle_data));
  }

  for(int i = 0; i < game_data.battle_data.cols
        * game_data.battle_data.rows; i++) {
    if(i != sel) {
      ASSERT_EQUAL(TEAM_EMPTY, game_data.battle_data.board[i]->team);
    } else {
      ASSERT_EQUAL(TEAM_SELECTED, game_data.battle_data.board[i]->team);
    }

    ASSERT_EQUAL(0.0, game_data.battle_data.board[i]->vel.x);
    ASSERT_EQUAL(0.0, game_data.battle_data.board[i]->vel.y);
  }

  game_data.battle_data.keys = KEY_MOVE_LEFT;
  sel -= 1; //22

  battle_entity_key_update(ent, &(game_data.battle_data));

  for(int i = 0; i < game_data.battle_data.cols
        * game_data.battle_data.rows; i++) {
    if(i != sel) {
      ASSERT_EQUAL(TEAM_EMPTY, game_data.battle_data.board[i]->team);
    } else {
      ASSERT_EQUAL(TEAM_SELECTED, game_data.battle_data.board[i]->team);
    }
  }

  game_data.battle_data.keys = 0;

  battle_entity_key_update(ent, &(game_data.battle_data));

  for(int i = 0; i < game_data.battle_data.cols
        * game_data.battle_data.rows; i++) {
    if(i != sel) {
      ASSERT_EQUAL(TEAM_EMPTY, game_data.battle_data.board[i]->team);
    } else {
      ASSERT_EQUAL(TEAM_SELECTED, game_data.battle_data.board[i]->team);
    }
  }

  game_data.battle_data.keys = KEY_MOVE_UP;
  sel -= game_data.battle_data.cols; //7

  battle_entity_key_update(ent, &(game_data.battle_data));

  for(int i = 0; i < game_data.battle_data.cols *
        game_data.battle_data.rows; i++) {
    if(i != sel) {
      ASSERT_EQUAL(TEAM_EMPTY, game_data.battle_data.board[i]->team);
    } else {
      ASSERT_EQUAL(TEAM_SELECTED, game_data.battle_data.board[i]->team);
    }
  }
}

CTEST(battle_entity, collision_battle_entity_key_update) {
  Game_Data game_data;
  int sel = 0;

  game_data.battle_data.state = GAME_BATTLE_MOVE;
  game_data.battle_data.keys = 0;
  game_data.battle_data.camera_pos.x = 0.0;
  game_data.battle_data.camera_pos.y = 0.0;
  game_data.battle_data.camera_vel.x = 0.0;
  game_data.battle_data.camera_vel.y = 0.0;
  game_data.battle_data.cols = 10;
  game_data.battle_data.rows = 15;
  game_data.battle_data.board = malloc(game_data.battle_data.cols
                                       * game_data.battle_data.rows
                                       * sizeof *game_data.battle_data.board);
  for(int i = 0; i < game_data.battle_data.cols
        * game_data.battle_data.rows; i++) {
    game_data.battle_data.board[i]
      = malloc(sizeof **game_data.battle_data.board);
    game_data.battle_data.board[i]->team = TEAM_EMPTY;
    game_data.battle_data.board[i]->pos.x
      = i % game_data.battle_data.cols;
    game_data.battle_data.board[i]->pos.y
      = i / game_data.battle_data.cols;
    game_data.battle_data.board[i]->vel = (Coord_f){0.0, 0.0};
    game_data.battle_data.board[i]->move_queue.head = NULL;
    game_data.battle_data.board[i]->move_queue.key_size = 0;
  }

  Battle_Entity *ent = game_data.battle_data.board[sel];
  ent->team = TEAM_SELECTED;

  //Going out of bounds at the top of the screen.
  game_data.battle_data.keys = KEY_MOVE_UP;

  battle_entity_key_update(ent, &(game_data.battle_data));

  for(int i = 0; i < game_data.battle_data.cols
        * game_data.battle_data.rows; i++) {
    if(i != sel) {
      ASSERT_EQUAL(TEAM_EMPTY, game_data.battle_data.board[i]->team);
    } else {
      ASSERT_EQUAL(TEAM_SELECTED, game_data.battle_data.board[i]->team);
    }
  }

  //Moving left into an entity
  game_data.battle_data.board[sel + 1]->team = TEAM_PLAYER;
  game_data.battle_data.keys = KEY_MOVE_RIGHT;

  battle_entity_key_update(ent, &(game_data.battle_data));

  for(int i = 0; i < game_data.battle_data.cols
        * game_data.battle_data.rows; i++) {
    if(i != sel + 1) {
      if(i != sel) {
        ASSERT_EQUAL(TEAM_EMPTY, game_data.battle_data.board[i]->team);
      } else {
        ASSERT_EQUAL(TEAM_SELECTED, game_data.battle_data.board[i]->team);
      }
    } else {
      ASSERT_EQUAL(TEAM_PLAYER, game_data.battle_data.board[i]->team);
    }
  }
}

CTEST(battle_entity, battle_entity_update) {

}

int main(int argc, const char *argv[])
{
  int result = ctest_main(argc, argv);

  return result;
}
