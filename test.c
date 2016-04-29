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

CTEST(stack, stack_free_1) {
  Stack stack = (Stack){(Node *)malloc(sizeof(Node)), sizeof(char)};
  *stack.head = (Node){malloc(sizeof(char)), malloc(sizeof(int)),
                       sizeof(int), NULL};
  Node *curr = stack.head;
  *(int *)stack.head->data = 0;

  for(int i = 1; i < 10; i++){
    curr->next = (Node *)malloc(sizeof(Node));
    *curr->next = (Node){malloc(sizeof(char)), malloc(sizeof(int)),
                         sizeof(int), NULL};

    curr = curr->next;
    *(int *)curr->data = i;
  }

  curr = stack.head;
  *(char *)curr->key = 'a';
  curr = curr->next;
  *(char *)curr->key = 'b';
  curr = curr->next;
  *(char *)curr->key = 'c';
  curr = curr->next;
  *(char *)curr->key = 'd';
  curr = curr->next;
  *(char *)curr->key = 'e';
  curr = curr->next;
  *(char *)curr->key = 'f';
  curr = curr->next;
  *(char *)curr->key = 'g';
  curr = curr->next;
  *(char *)curr->key = 'h';
  curr = curr->next;
  *(char *)curr->key = 'i';
  curr = curr->next;
  *(char *)curr->key = 'j';

  stack_free(&stack);

  stack_free(&stack);
}

CTEST(stack, stack_free_2) {
  Stack stack = (Stack){(Node *)malloc(sizeof(Node)), sizeof(char)};
  stack.key_size = sizeof(double);
  stack.head = (Node *)malloc(sizeof(Node));
  *stack.head = (Node){malloc(sizeof(double)), malloc(sizeof(int)),
                       sizeof(int), NULL};
  Node *curr = stack.head;
  *(int *)stack.head->data = 0;

  for(int i = 1; i < 10; i++){
    curr->next = (Node *)malloc(sizeof(Node));
    *curr->next = (Node){malloc(sizeof(double)), malloc(sizeof(int)),
                         sizeof(int), NULL};

    curr = curr->next;
    *(int *)curr->data = i;
  }

  curr = stack.head;
  *(double *)curr->key = 1.01;
  curr = curr->next;
  *(double *)curr->key = 2.02;
  curr = curr->next;
  *(double *)curr->key = 3.03;
  curr = curr->next;
  *(double *)curr->key = 4.04;
  curr = curr->next;
  *(double *)curr->key = 5.05;
  curr = curr->next;
  *(double *)curr->key = 6.06;
  curr = curr->next;
  *(double *)curr->key = 7.07;
  curr = curr->next;
  *(double *)curr->key = 8.08;
  curr = curr->next;
  *(double *)curr->key = 9.09;
  curr = curr->next;
  *(double *)curr->key = 10.10;

  stack_free(&stack);

  stack.key_size = 0;
  stack.head = (Node *)malloc(sizeof(Node));
  *stack.head = (Node){malloc(256 * sizeof(char)), malloc(sizeof(int)),
                       sizeof(int), NULL};
  curr = stack.head;
  *(int *)stack.head->data = 0;

  for(int i = 1; i < 3; i++){
    curr->next = (Node *)malloc(sizeof(Node));
    *curr->next = (Node){malloc(256 * sizeof(char)), malloc(sizeof(int)),
                         sizeof(int), NULL};

    curr = curr->next;
    *(int *)curr->data = i;
  }

  curr = stack.head;
  strcpy(curr->key, "one");
  curr = curr->next;
  strcpy(curr->key, "two");
  curr = curr->next;
  strcpy(curr->key, "three");

  stack_free(&stack);

  stack_free(&stack);
}

CTEST(stack, stack_find) {
  Stack stack = (Stack){(Node *)malloc(sizeof(Node)), sizeof(char)};
  Node *curr = stack.head;
  *curr = (Node){malloc(sizeof(char)), malloc(sizeof(int)),
                 sizeof(int), NULL};
  *(int *)curr->data = 0;

  for(int i = 1; i < 10; i++){
    curr->next = (Node *)malloc(sizeof(Node));

    curr = curr->next;
    *curr = (Node){malloc(sizeof(char)), malloc(sizeof(int)),
                   sizeof(int), NULL};

    *(int *)curr->data = i;
  }

  curr = stack.head;
  *(char *)curr->key = 'a';
  curr = curr->next;
  *(char *)curr->key = 'b';
  curr = curr->next;
  *(char *)curr->key = 'c';
  curr = curr->next;
  *(char *)curr->key = 'd';
  curr = curr->next;
  *(char *)curr->key = 'e';
  curr = curr->next;
  *(char *)curr->key = 'f';
  curr = curr->next;
  *(char *)curr->key = 'g';
  curr = curr->next;
  *(char *)curr->key = 'h';
  curr = curr->next;
  *(char *)curr->key = 'i';
  curr = curr->next;
  *(char *)curr->key = 'j';

  void *key = malloc(sizeof(char));
  *(char *)key = 'b';
  ASSERT_NOT_NULL(stack_find(stack, key));
  ASSERT_EQUAL(*(int *)stack_find(stack, key)->data, 1);
  *(char *)key = 'd';
  ASSERT_NOT_NULL(stack_find(stack, key));
  ASSERT_EQUAL(*(int *)stack_find(stack, key)->data, 3);
  *(char *)key = 'c';
  ASSERT_NOT_NULL(stack_find(stack, key));
  ASSERT_EQUAL(*(int *)stack_find(stack, key)->data, 2);
  *(char *)key = 'j';
  ASSERT_NOT_NULL(stack_find(stack, key));
  ASSERT_EQUAL(*(int *)stack_find(stack, key)->data, 9);
  *(char *)key = 'q';
  ASSERT_NULL(stack_find(stack, key));
  ASSERT_NULL(stack_find(stack, NULL));

  free(key);
  key = malloc(sizeof(double));

  stack_free(&stack);

  stack.key_size = sizeof(double);
  stack.head = (Node *)malloc(sizeof(Node));
  *stack.head = (Node){malloc(sizeof(double)), malloc(sizeof(int)),
                       sizeof(int), NULL};
  curr = stack.head;
  *(int *)stack.head->data = 0;

  for(int i = 1; i < 10; i++){
    curr->next = (Node *)malloc(sizeof(Node));
    *curr->next = (Node){malloc(sizeof(double)), malloc(sizeof(int)),
                         sizeof(int), NULL};

    curr = curr->next;
    *(int *)curr->data = i;
  }

  curr = stack.head;
  *(double *)curr->key = 1.01;
  curr = curr->next;
  *(double *)curr->key = 2.02;
  curr = curr->next;
  *(double *)curr->key = 3.03;
  curr = curr->next;
  *(double *)curr->key = 4.04;
  curr = curr->next;
  *(double *)curr->key = 5.05;
  curr = curr->next;
  *(double *)curr->key = 6.06;
  curr = curr->next;
  *(double *)curr->key = 7.07;
  curr = curr->next;
  *(double *)curr->key = 8.08;
  curr = curr->next;
  *(double *)curr->key = 9.09;
  curr = curr->next;
  *(double *)curr->key = 10.10;

  *(double *)key = 2.02;
  ASSERT_NOT_NULL(stack_find(stack, key));
  ASSERT_EQUAL(*(int *)stack_find(stack, key)->data, 1);
  *(double *)key = 3.03;
  ASSERT_NOT_NULL(stack_find(stack, key));
  ASSERT_EQUAL(*(int *)stack_find(stack, key)->data, 2);
  *(double *)key = 1.02;
  ASSERT_NULL(stack_find(stack, key));

  free(key);
  stack_free(&stack);

  stack.key_size = 0;
  stack.head = (Node *)malloc(sizeof(Node));
  *stack.head = (Node){malloc(256 * sizeof(char)), malloc(sizeof(int)),
                       sizeof(int), NULL};

  curr = stack.head;
  *(int *)stack.head->data = 0;

  for(int i = 1; i < 10; i++){
    curr->next = (Node *)malloc(sizeof(Node));
    *curr->next = (Node){malloc(256 * sizeof(char)), malloc(sizeof(int)),
                         sizeof(int), NULL};

    curr = curr->next;
    *(int *)curr->data = i;
  }

  curr = stack.head;
  strcpy(curr->key, "one");
  curr = curr->next;
  strcpy(curr->key, "two");
  curr = curr->next;
  strcpy(curr->key, "three");
  curr = curr->next;
  strcpy(curr->key, "four");
  curr = curr->next;
  strcpy(curr->key, "five");
  curr = curr->next;
  strcpy(curr->key, "six");
  curr = curr->next;
  strcpy(curr->key, "seven");
  curr = curr->next;
  strcpy(curr->key, "eight");
  curr = curr->next;
  strcpy(curr->key, "nine");
  curr = curr->next;
  strcpy(curr->key, "ten");

  key = malloc(256 * sizeof(char));

  strcpy(key, "four");
  ASSERT_NOT_NULL(stack_find(stack, key));
  ASSERT_EQUAL(*(int *)stack_find(stack, key)->data, 3);
  strcpy(key, "two");
  ASSERT_NOT_NULL(stack_find(stack, key));
  ASSERT_EQUAL(*(int *)stack_find(stack, key)->data, 1);
  strcpy(key, "four");
  ASSERT_NOT_NULL(stack_find(stack, key));
  ASSERT_EQUAL(*(int *)stack_find(stack, key)->data, 3);
  strcpy(key, "ten");
  ASSERT_NOT_NULL(stack_find(stack, key));
  ASSERT_EQUAL(*(int *)stack_find(stack, key)->data, 9);
  strcpy(key, "eleven");
  ASSERT_NULL(stack_find(stack, key));

  free(key);
  key = NULL;

  ASSERT_NULL(stack_find(stack, key));

  stack_free(&stack);
}

CTEST(stack, stack_put) {
  Stack stack = (Stack){NULL, 0};

  void *data = malloc(sizeof(int));

  *(int *)data = 1;
  ASSERT_EQUAL(stack_put(&stack, "first", data, sizeof(int)), STACK_SUCCESS);
  ASSERT_EQUAL(*(int *)stack_find(stack, "first")->data, 1);
  ASSERT_NULL(stack_find(stack, "first")->next);

  *(int *)data = 0;
  ASSERT_EQUAL(*(int *)stack_find(stack, "first")->data, 1);

  ASSERT_EQUAL(stack_put(&stack, "first", data, sizeof(int)), STACK_REPLACED);
  ASSERT_EQUAL(*(int *)stack_find(stack, "first")->data, 0);

  *(int *)data = 1;
  ASSERT_EQUAL(stack_put(&stack, "second", data, sizeof(int)), STACK_SUCCESS);
  ASSERT_EQUAL(*(int *)stack_find(stack, "first")->data, 0);
  ASSERT_EQUAL(*(int *)stack_find(stack, "second")->data, 1);

  free(data);
  data = malloc(sizeof(char));

  *(char *)data = 'c';
  ASSERT_EQUAL(*(int *)stack_find(stack, "second")->data, 1);
  ASSERT_EQUAL(stack_put(&stack, "third", data, sizeof(char)), STACK_SUCCESS);
  ASSERT_EQUAL(*(char *)stack_find(stack, "third")->data, 'c');
  ASSERT_NULL(stack_find(stack, "first")->next);

  free(data);
  data = malloc(sizeof(int));

  *(int *)data = 2;
  ASSERT_EQUAL(stack_put(&stack, "first", data, sizeof(int)), STACK_REPLACED);
  ASSERT_EQUAL(*(int *)stack_find(stack, "first")->data, 2);
  ASSERT_EQUAL(*(char *)stack_find(stack, "third")->data, 'c');
  ASSERT_NULL(stack_find(stack, "fourth"));

  ASSERT_EQUAL(stack_put(NULL, "word", data, sizeof(int)), STACK_INVALID_ARGS);
  ASSERT_EQUAL(stack_put(&stack, NULL, data, sizeof(int)), STACK_SUCCESS);
  ASSERT_EQUAL(stack_put(&stack, "word", NULL, sizeof(int)),
               STACK_INVALID_ARGS);
  ASSERT_EQUAL(stack_put(&stack, "word", data, 0), STACK_INVALID_ARGS);

  stack_free(&stack);
}

CTEST(stack, stack_remove) {
  Stack stack = (Stack){NULL, 0};

  void *data = malloc(sizeof(int));

  ASSERT_NULL(stack_remove(&stack, "new"));

  *(int *)data = 0;
  stack_put(&stack, "first", data, sizeof(int));
  *(int *)data = 1;
  stack_put(&stack, "second", data, sizeof(int));

  data = malloc(sizeof(char));

  *(char *)data = 'c';
  stack_put(&stack, "third", data, sizeof(char));
  *(char *)data = 'd';
  stack_put(&stack, "fourth", data, sizeof(char));

  ASSERT_NOT_NULL(stack_find(stack, "first"));
  ASSERT_NULL(stack_find(stack, "first")->next);
  ASSERT_NULL(stack_remove(&stack, "fifth"));
  ASSERT_NOT_NULL(stack_find(stack, "first"));
  ASSERT_EQUAL(*(int *)stack_find(stack, "first")->data, 0);
  ASSERT_NOT_NULL(stack_find(stack, "fourth"));
  ASSERT_EQUAL(*(char *)stack_find(stack, "fourth")->data, 'd');
  ASSERT_NOT_NULL(stack_find(stack, "second"));
  ASSERT_EQUAL(*(int *)stack_find(stack, "second")->data, 1);

  ASSERT_EQUAL(*(int *)stack_remove(&stack, "second"), 1);
  ASSERT_NOT_NULL(stack_find(stack, "first"));
  ASSERT_EQUAL(*(int *)stack_find(stack, "first")->data, 0);
  ASSERT_NOT_NULL(stack_find(stack, "third"));
  ASSERT_EQUAL(*(char *)stack_find(stack, "third")->data, 'c');
  ASSERT_NOT_NULL(stack_find(stack, "fourth"));
  ASSERT_EQUAL(*(char *)stack_find(stack, "fourth")->data, 'd');
  ASSERT_EQUAL(*(int *)stack_find(stack, "third")->next->data, 0);

  ASSERT_EQUAL(*(char *)stack_remove(&stack, "third"), 'c');
  ASSERT_NULL(stack_find(stack, "third"));
  ASSERT_EQUAL(*(int *)stack_find(stack, "first")->data, 0);
  ASSERT_EQUAL(*(char *)stack_find(stack, "fourth")->data, 'd');
  ASSERT_EQUAL(*(int *)stack_find(stack, "fourth")->next->data, 0);
  ASSERT_NULL(stack_find(stack, "first")->next);

  ASSERT_EQUAL(*(int *)stack_remove(&stack, "first"), 0);
  ASSERT_EQUAL(*(char *)stack_find(stack, "fourth")->data, 'd');
  ASSERT_NULL(stack_find(stack, "first"));
  ASSERT_NULL(stack_find(stack, "fourth")->next);

  ASSERT_EQUAL(*(char *)stack_remove(&stack, "fourth"), 'd');
  ASSERT_NULL(stack.head);

  stack_free(&stack);
}

#define NEW_HASHMAP(size)                                 \
  (Hashmap){(Stack *)malloc(size * sizeof(Stack)), size};

CTEST(hashmap, hashmap_free) {
  Hashmap hashmap = NEW_HASHMAP(100);
  for(int i = 0; i < 100; i++) {
    hashmap.data[i].key_size = 0;
    hashmap.data[i].head = NULL;
  }

  void *data = malloc(sizeof(int));

  *(int *)data = 5;
  stack_put(&hashmap.data[5], "test", data, sizeof(int));

  *(int *)data = 6;
  stack_put(&hashmap.data[5], "testing", data, sizeof(int));

  *(int *)data = 0;
  stack_put(&hashmap.data[0], "test", data, sizeof(int));
  stack_put(&hashmap.data[99], "test", data, sizeof(int));

  hashmap_free(&hashmap);

  hashmap = NEW_HASHMAP(100);
  for(int i = 0; i < 100; i++) {
    hashmap.data[i].key_size = 0;
    hashmap.data[i].head = NULL;
  }

  hashmap_free(&hashmap);
}

CTEST(hashmap, hashmap_put) {
  Hashmap hashmap = NEW_HASHMAP(100);
  for(int i = 0; i < 100; i++) {
    hashmap.data[i].key_size = 0;
    hashmap.data[i].head = NULL;
  }

  void *data = malloc(sizeof(int));

  *(int *)data = 100;
  ASSERT_EQUAL(hashmap_put(&hashmap, "one", data, sizeof(int)),
               STACK_SUCCESS);
  ASSERT_EQUAL(*(int *)stack_find(hashmap.data[hash_func("one",
                                                         hashmap.data[0].
                                                         key_size, 100)],
                                  "one")->data, 100);

  *(int *)data = 101;
  ASSERT_EQUAL(hashmap_put(&hashmap, "one", data, sizeof(int)),
               STACK_REPLACED);
  ASSERT_EQUAL(*(int *)stack_find(hashmap.data[hash_func("one",
                                                         hashmap.data[0].
                                                         key_size, 100)],
                                  "one")->data, 101);

  *(int *)data = 102;
  ASSERT_EQUAL(hashmap_put(&hashmap, "two", data, sizeof(int)),
               STACK_SUCCESS);
  ASSERT_EQUAL(*(int *)stack_find(hashmap.data[hash_func("two",
                                                         hashmap.data[0].
                                                         key_size, 100)],
                                  "two")->data, 102);

  free(data);
  data = malloc(sizeof(char));

  *(char *)data = 'a';
  ASSERT_EQUAL(hashmap_put(&hashmap, "three", data, sizeof(int)),
               STACK_SUCCESS);
  ASSERT_EQUAL(*(char *)stack_find(hashmap.data[hash_func("three",
                                                          hashmap.data[0].
                                                          key_size, 100)],
                                   "three")->data, 'a');
  ASSERT_NULL(stack_find(hashmap.data[hash_func("three",
                                                hashmap.data[0].
                                                key_size, 100)], "thwee"));

  ASSERT_EQUAL(hashmap_put(&hashmap, "one", data, sizeof(char)),
               STACK_REPLACED);
  ASSERT_EQUAL(*(char *)stack_find(hashmap.data[hash_func("one",
                                                          hashmap.data[0].
                                                          key_size, 100)],
                                   "one")->data, 'a');

  hashmap_free(&hashmap);
}

CTEST(hashmap, hashmap_find) {
  Hashmap hashmap = NEW_HASHMAP(100);
  for(int i = 0; i < 100; i++) {
    hashmap.data[i].key_size = 0;
    hashmap.data[i].head = NULL;
  }

  void *data = malloc(sizeof(int));

  *(int *)data = 0;
  hashmap_put(&hashmap, "first", data, sizeof(int));
  ASSERT_EQUAL(*(int *)hashmap_find(hashmap, "first")->data, 0);
  ASSERT_NULL(hashmap_find(hashmap, "second"));

  *(int *)data = 1;
  hashmap_put(&hashmap, "second", data, sizeof(int));
  ASSERT_EQUAL(*(int *)hashmap_find(hashmap, "second")->data, 1);
  ASSERT_EQUAL(*(int *)hashmap_find(hashmap, "first")->data, 0);

  free(data);
  data = malloc(sizeof(char));

  *(char *)data = 'c';
  hashmap_put(&hashmap, "third", data, sizeof(char));
  ASSERT_EQUAL(*(char *)hashmap_find(hashmap, "third")->data, 'c');

  hashmap_free(&hashmap);

  hashmap = NEW_HASHMAP(100);
  for(int i = 0; i < 100; i++) {
    hashmap.data[i].key_size = 0;
    hashmap.data[i].head = NULL;
  }

  void *key = malloc(sizeof(int));

  *(int *)key = 0;
  *(int *)data = 0;
  hashmap_put(&hashmap, key, data, sizeof(int));
  ASSERT_NOT_NULL(hashmap_find(hashmap, key));
  ASSERT_EQUAL(*(int *)hashmap_find(hashmap, key)->data, 0);

  *(int *)key = 1;
  *(int *)data = 1;
  ASSERT_NULL(hashmap_find(hashmap, key));
  hashmap_put(&hashmap, key, data, sizeof(int));
  ASSERT_NOT_NULL(hashmap_find(hashmap, key));
  ASSERT_EQUAL(*(int *)hashmap_find(hashmap, key)->data, 1);

  *(int *)key = 0;
  ASSERT_EQUAL(*(int *)hashmap_find(hashmap, key)->data, 0);

  hashmap_free(&hashmap);
}

CTEST(hashmap, hashmap_remove) {
  Hashmap hashmap = NEW_HASHMAP(100);
  for(int i = 0; i < 100; i++) {
    hashmap.data[i].key_size = 0;
    hashmap.data[i].head = NULL;
  }

  void *data = malloc(sizeof(int));

  ASSERT_NULL(hashmap_remove(&hashmap, "anything"));

  *(int *)data = 5;
  hashmap_put(&hashmap, "five", data, sizeof(int));

  *(int *)data = 7;
  hashmap_put(&hashmap, "seven", data, sizeof(int));
  ASSERT_EQUAL(*(int *)hashmap_remove(&hashmap, "five"), 5);
  ASSERT_NULL(hashmap_find(hashmap, "five"));
  ASSERT_NULL(hashmap_remove(&hashmap, "five"));

  hashmap_free(&hashmap);
}

#undef NEW_HASHMAP

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

CTEST(battle_entity, battle_entity_key_update) {
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

  for(int i = 0; i < 4; i++) {
    battle_entity_key_update(ent, &game_data);
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
  sel -= 1;

  battle_entity_key_update(ent, &game_data);

  for(int i = 0; i < game_data.battle_data.cols
        * game_data.battle_data.rows; i++) {
    if(i != sel) {
      ASSERT_EQUAL(TEAM_EMPTY, game_data.battle_data.board[i]->team);
    } else {
      ASSERT_EQUAL(TEAM_SELECTED, game_data.battle_data.board[i]->team);
    }
  }

  game_data.battle_data.keys = 0;

  battle_entity_key_update(ent, &game_data);

  for(int i = 0; i < game_data.battle_data.cols
        * game_data.battle_data.rows; i++) {
    if(i != sel) {
      ASSERT_EQUAL(TEAM_EMPTY, game_data.battle_data.board[i]->team);
    } else {
      ASSERT_EQUAL(TEAM_SELECTED, game_data.battle_data.board[i]->team);
    }
  }

  game_data.battle_data.keys = KEY_MOVE_UP;

  battle_entity_key_update(ent, &game_data);

  for(int i = 0; i < game_data.battle_data.cols *
        game_data.battle_data.rows; i++) {
    if(i != sel) {
      ASSERT_EQUAL(TEAM_EMPTY, game_data.battle_data.board[i]->team);
    } else {
      ASSERT_EQUAL(TEAM_SELECTED, game_data.battle_data.board[i]->team);
    }
  }
}

int main(int argc, const char *argv[])
{
  int result = ctest_main(argc, argv);

  return result;
}
