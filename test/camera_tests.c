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

int main(int argc, const char *argv[])
{
  int result = ctest_main(argc, argv);

  return result;
}
