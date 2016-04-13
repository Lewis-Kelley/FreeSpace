#include <stdio.h>
#include "CUnit/CUnit.h"
#include "CUnit/Basic.h"
#include "hashmap/hashmap.h"
#include "src/game_state.h"
#include "testing/stack_tests.c"

#define QUIT do { CU_cleanup_registry(); return CU_get_error(); } while(0);

Game_Data * new_game_data(int rows, int cols, int num_units) {
  Game_Data *data = malloc(sizeof *data);
  data->battle_data.state = GAME_BATTLE_MOVE;
  data->battle_data.keys = 0;
  data->battle_data.delta = 0.0;
  data->battle_data.last_time = 0.0;
  data->battle_data.board =
    (Battle_Entity **)malloc(rows * cols
                             * sizeof(Battle_Entity *));
  data->battle_data.turn_order =
    (Battle_Entity **)malloc(num_units * sizeof(Battle_Entity *));
  data->battle_data.camera_pos = (Coord_f){0.0, 0.0};
  data->battle_data.camera_vel = (Coord_f){0.0, 0.0};
  data->battle_data.cols = cols;
  data->battle_data.rows = rows;
  data->battle_data.turn = 0;
  data->battle_data.num_units = num_units;

  return data;
}

Battle_Entity * add_battle_entity(Game_Data *data, int x, int y) {
  Battle_Entity *ent;
  int index = 0;

  if((ent = bat_ent_lookup(data, x, y)) == NULL) {
    return NULL;
  }

  for(int i = 0; i < data->battle_data.num_units
        && data->battle_data.turn_order[i] != NULL; i++) {
    index = i;
  }

  if(data->battle_data.turn_order[index] != NULL) {
    return NULL;
  }

  ent = malloc(sizeof *ent);
  ent->pos = (Coord_f){x, y};
  data->battle_data.turn_order[index] = ent;

  return ent;
}

int init_suite() {
  return 0;
}

int clean_suite() {
  return 0;
}

void test_battle_entity_update() {
  Game_Data *data = new_game_data(20, 20, 2);

  data->battle_data.turn_order[0] = add_battle_entity(data, 5, 7);
  data->battle_data.turn_order[1] = add_battle_entity(data, 0, 0);

  data->battle_data.turn_order[0]->team = TEAM_SELECTED;
  data->battle_data.turn_order[1]->team = TEAM_PLAYER;

  data->battle_data.turn_order[0]->vel = (Coord_f){0.0, 0.0};
  data->battle_data.turn_order[1]->vel = (Coord_f){0.0, 0.0};
}

void test_update_world() {

}

int main(int argc, char **argv) {
  CU_Suite *stack_suite = NULL,
    *hashmap_suite = NULL,
    *update_suite = NULL;

  if(CUE_SUCCESS != CU_initialize_registry())
    return CU_get_error();

  stack_suite = CU_add_suite("stack_test_suite", init_suite, clean_suite);
  hashmap_suite = CU_add_suite("hashmap_test_suite", init_suite, clean_suite);
  update_suite = CU_add_suite("update_test_suite", init_suite, clean_suite);

  if(stack_suite == NULL || hashmap_suite == NULL || update_suite == NULL) {
    QUIT;
  }

  if(CU_add_test(stack_suite, "stack_free",
                 test_stack_free) == NULL
     || CU_add_test(stack_suite, "stack_find",
                    test_stack_find) == NULL
     || CU_add_test(stack_suite, "stack_put",
                    test_stack_put) == NULL
     || CU_add_test(stack_suite, "stack_remove",
                    test_stack_remove) == NULL
     || CU_add_test(hashmap_suite, "hashmap_free",
                    test_hashmap_free) == NULL
     || CU_add_test(hashmap_suite, "hashmap_put",
                    test_hashmap_put) == NULL
     || CU_add_test(hashmap_suite, "hashmap_find",
                    test_hashmap_find) == NULL
     || CU_add_test(hashmap_suite, "hashmap_remove",
                    test_hashmap_remove) == NULL
     )
    QUIT;

  CU_basic_set_mode(CU_BRM_VERBOSE);
  CU_basic_run_tests();
  CU_basic_show_failures(CU_get_failure_list());
  printf("\n");

  QUIT;
}
