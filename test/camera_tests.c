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

CTEST(camera, camera_move) {
  Game_Data game;
  game.battle_data.state = GAME_BATTLE_MOVE;
  game.battle_data.keys = 0;
  game.battle_data.camera_pos.x = 0.0;
  game.battle_data.camera_pos.y = 0.0;
  game.battle_data.camera_vel.x = 0.0;
  game.battle_data.camera_vel.y = 0.0;
  game.battle_data.cols = 0;
  game.battle_data.rows = 0;

  for(float i = 0; i < 1; i += 0.25) {
    update_world(&game, 0.25);
  }

  ASSERT_DBL_NEAR(game.battle_data.camera_pos.x, 0.0);
  ASSERT_DBL_NEAR(game.battle_data.camera_pos.y, 0.0);
  ASSERT_DBL_NEAR(game.battle_data.camera_vel.x, 0.0);
  ASSERT_DBL_NEAR(game.battle_data.camera_vel.y, 0.0);

  game.battle_data.keys = KEY_CAM_RIGHT;
  for(int i = 0; i < 4; i++) {
    update_world(&game, 0.25);
  }

  ASSERT_DBL_NEAR(game.battle_data.camera_pos.x, CAM_SPEED);
  ASSERT_DBL_NEAR(game.battle_data.camera_pos.y, 0.0);
  ASSERT_DBL_NEAR(game.battle_data.camera_vel.x, CAM_SPEED);
  ASSERT_DBL_NEAR(game.battle_data.camera_vel.y, 0.0);

  game.battle_data.keys = 0;
  for(int i = 0; i < 4; i++) {
    update_world(&game, 0.25);
  }

  ASSERT_DBL_NEAR(game.battle_data.camera_pos.x, CAM_SPEED);
  ASSERT_DBL_NEAR(game.battle_data.camera_pos.y, 0.0);
  ASSERT_DBL_NEAR(game.battle_data.camera_vel.x, 0.0);
  ASSERT_DBL_NEAR(game.battle_data.camera_vel.y, 0.0);

  game.battle_data.keys = KEY_CAM_LEFT | KEY_CAM_UP;
  for(int i = 0; i < 4; i++) {
    update_world(&game, 0.25);
  }

  ASSERT_DBL_NEAR(game.battle_data.camera_pos.x, 0.0);
  ASSERT_DBL_NEAR(game.battle_data.camera_pos.y, -CAM_SPEED);
  ASSERT_DBL_NEAR(game.battle_data.camera_vel.x, -CAM_SPEED);
  ASSERT_DBL_NEAR(game.battle_data.camera_vel.y, -CAM_SPEED);

  game.battle_data.keys = KEY_CAM_LEFT;
  for(int i = 0; i < 4; i++) {
    update_world(&game, 0.25);
  }

  ASSERT_DBL_NEAR(game.battle_data.camera_pos.x, -CAM_SPEED);
  ASSERT_DBL_NEAR(game.battle_data.camera_pos.y, -CAM_SPEED);
  ASSERT_DBL_NEAR(game.battle_data.camera_vel.x, -CAM_SPEED);
  ASSERT_DBL_NEAR(game.battle_data.camera_vel.y, 0.0);
}

CTEST(camera, image_move) {
  Game_Data game_data;
  Battle_Data battle_data;

  battle_data.state = GAME_BATTLE_MOVE;
  battle_data.camera_pos.x = 0.0;
  battle_data.camera_pos.y = 0.0;
  battle_data.camera_vel.x = 0.0;
  battle_data.camera_vel.y = 0.0;
  battle_data.cols = 10;
  battle_data.rows = 15;
  battle_data.board = malloc(battle_data.cols
                             * battle_data.rows
                             * sizeof *battle_data.board);
  for(int i = 0; i < battle_data.cols
        * battle_data.rows; i++) {
    battle_data.board[i]
      = malloc(sizeof **battle_data.board);
    battle_data.board[i]->team = TEAM_EMPTY;
    battle_data.board[i]->pos.x
      = i % battle_data.cols;
    battle_data.board[i]->pos.y
      = i / battle_data.cols;
    battle_data.board[i]->vel = (Coord_f){0.0, 0.0};
    battle_data.board[i]->move_queue.head = NULL;
    battle_data.board[i]->move_queue.key_size = 0;
    battle_data.board[i]->img.dest_x = (i % battle_data.cols)
      * WIN_WIDTH / battle_data.cols;
    battle_data.board[i]->img.dest_y = (i / battle_data.rows)
      * WIN_HEIGHT / battle_data.rows;
  }

  game_data.battle_data = battle_data;

  Battle_Entity *ent = game_data.battle_data.board[0];
  ent->team = TEAM_SELECTED;

  game_data.battle_data.keys = 0;
  update_world(&game_data, 0.25);

  ASSERT_EQUAL(0, ent->img.dest_x);
  ASSERT_EQUAL(0, ent->img.dest_y);

  game_data.battle_data.keys = KEY_CAM_LEFT;
  update_world(&game_data, 0.25);

  ASSERT_DBL_NEAR(0.25 * CAM_SPEED * WIN_WIDTH / battle_data.cols,
                  ent->img.dest_x);
  ASSERT_EQUAL(0, ent->img.dest_y);

  game_data.battle_data.keys = KEY_CAM_LEFT | KEY_CAM_UP;
  update_world(&game_data, 0.25);

  ASSERT_DBL_NEAR(0.50 * CAM_SPEED * WIN_WIDTH / battle_data.cols,
                  ent->img.dest_x);
  ASSERT_DBL_NEAR(0.25 * CAM_SPEED * WIN_HEIGHT / battle_data.rows,
                  ent->img.dest_y);
}

CTEST(camera, camera_ent_move) {
  Game_Data game_data;
  Battle_Data battle_data;
  int sel = 0;

  battle_data.state = GAME_BATTLE_MOVE;
  battle_data.camera_pos.x = 0.0;
  battle_data.camera_pos.y = 0.0;
  battle_data.camera_vel.x = 0.0;
  battle_data.camera_vel.y = 0.0;
  battle_data.cols = 10;
  battle_data.rows = 15;
  battle_data.board = malloc(battle_data.cols
                             * battle_data.rows
                             * sizeof *battle_data.board);
  for(int i = 0; i < battle_data.cols
        * battle_data.rows; i++) {
    battle_data.board[i]
      = malloc(sizeof **battle_data.board);
    battle_data.board[i]->team = TEAM_EMPTY;
    battle_data.board[i]->pos.x
      = i % battle_data.cols;
    battle_data.board[i]->pos.y
      = i / battle_data.cols;
    battle_data.board[i]->vel = (Coord_f){0.0, 0.0};
    battle_data.board[i]->move_queue.head = NULL;
    battle_data.board[i]->move_queue.key_size = 0;
    battle_data.board[i]->img.dest_x = (i % battle_data.cols)
      * WIN_WIDTH / battle_data.cols;
    battle_data.board[i]->img.dest_y = (i / battle_data.rows)
      * WIN_HEIGHT / battle_data.rows;
  }

  game_data.battle_data = battle_data;
  Battle_Entity *ent = game_data.battle_data.board[sel];
  ent->team = TEAM_SELECTED;

  game_data.battle_data.keys = 0;
  update_world(&game_data, 0.25);

  ASSERT_DBL_NEAR(0, ent->img.dest_x);
  ASSERT_DBL_NEAR(0, ent->img.dest_y);
  ASSERT_DBL_NEAR(0, ent->pos.x);
  ASSERT_DBL_NEAR(0, ent->pos.y);

  game_data.battle_data.keys = KEY_CAM_UP;
  update_world(&game_data, 1.0);

  ASSERT_DBL_NEAR(0, ent->img.dest_x);
  ASSERT_DBL_NEAR(CAM_SPEED * WIN_HEIGHT / battle_data.rows, ent->img.dest_y);
  ASSERT_DBL_NEAR(0, ent->pos.x);
  ASSERT_DBL_NEAR(0, ent->pos.y);

  game_data.battle_data.keys = KEY_MOVE_DOWN;
  update_world(&game_data, 0.25);

  ASSERT_DBL_NEAR(0.0, ent->img.dest_x);
  ASSERT_DBL_NEAR((CAM_SPEED + MOVE_SPEED * 0.25) * WIN_HEIGHT
                  / battle_data.rows, ent->img.dest_y);

  game_data.battle_data.keys = 0;
  update_world(&game_data, 1000.0);

  ASSERT_DBL_NEAR(0.0, ent->img.dest_x);
  ASSERT_DBL_NEAR((CAM_SPEED + 1) * WIN_HEIGHT / battle_data.rows,
                  ent->img.dest_y);

  game_data.battle_data.keys = KEY_MOVE_UP;
  update_world(&game_data, 0.25);

  game_data.battle_data.keys = 0;
  update_world(&game_data, 1000.0);

  ASSERT_DBL_NEAR(0.0, ent->img.dest_x);
  ASSERT_DBL_NEAR(CAM_SPEED * WIN_HEIGHT / battle_data.rows,
                  ent->img.dest_y);

  game_data.battle_data.keys = KEY_CAM_RIGHT | KEY_CAM_DOWN;
  update_world(&game_data, 1.0);

  ASSERT_DBL_NEAR(-CAM_SPEED * WIN_WIDTH * 1.0 / battle_data.cols,
                  ent->img.dest_x);
  ASSERT_DBL_NEAR(0.0, ent->img.dest_y);
}

int main(int argc, const char *argv[])
{
  int result = ctest_main(argc, argv);

  return result;
}
