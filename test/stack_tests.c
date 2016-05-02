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

int main(int argc, const char *argv[])
{
  int result = ctest_main(argc, argv);

  return result;
}
