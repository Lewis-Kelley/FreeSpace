#include "../hashmap/stack.h"
#include "CUnit/CUnit.h"
#include "CUnit/Basic.h"

void test_stack_free() {
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
  CU_PASS();

  stack_free(&stack);
  CU_PASS();

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

  stack_free(&stack);
  CU_PASS();

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
  CU_PASS();

  stack_free(&stack);
  CU_PASS();
}

void test_stack_find() {
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
  CU_ASSERT_NOT_EQUAL_FATAL(stack_find(stack, key), NULL);
  CU_ASSERT_EQUAL(*(int *)stack_find(stack, key)->data, 1);
  *(char *)key = 'd';
  CU_ASSERT_NOT_EQUAL_FATAL(stack_find(stack, key), NULL);
  CU_ASSERT_EQUAL(*(int *)stack_find(stack, key)->data, 3);
  *(char *)key = 'c';
  CU_ASSERT_NOT_EQUAL_FATAL(stack_find(stack, key), NULL);
  CU_ASSERT_EQUAL(*(int *)stack_find(stack, key)->data, 2);
  *(char *)key = 'j';
  CU_ASSERT_NOT_EQUAL_FATAL(stack_find(stack, key), NULL);
  CU_ASSERT_EQUAL(*(int *)stack_find(stack, key)->data, 9);
  *(char *)key = 'q';
  CU_ASSERT_EQUAL(stack_find(stack, key), NULL);
  CU_ASSERT_EQUAL(stack_find(stack, NULL), NULL);

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
  CU_ASSERT_NOT_EQUAL_FATAL(stack_find(stack, key), NULL);
  CU_ASSERT_EQUAL(*(int *)stack_find(stack, key)->data, 1);
  *(double *)key = 3.03;
  CU_ASSERT_NOT_EQUAL_FATAL(stack_find(stack, key), NULL);
  CU_ASSERT_EQUAL(*(int *)stack_find(stack, key)->data, 2);
  *(double *)key = 1.02;
  CU_ASSERT_EQUAL(stack_find(stack, key), NULL);

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
  CU_ASSERT_NOT_EQUAL_FATAL(stack_find(stack, key), NULL);
  CU_ASSERT_EQUAL(*(int *)stack_find(stack, key)->data, 3);
  strcpy(key, "two");
  CU_ASSERT_NOT_EQUAL_FATAL(stack_find(stack, key), NULL);
  CU_ASSERT_EQUAL(*(int *)stack_find(stack, key)->data, 1);
  strcpy(key, "four");
  CU_ASSERT_NOT_EQUAL_FATAL(stack_find(stack, key), NULL);
  CU_ASSERT_EQUAL(*(int *)stack_find(stack, key)->data, 3);
  strcpy(key, "ten");
  CU_ASSERT_NOT_EQUAL_FATAL(stack_find(stack, key), NULL);
  CU_ASSERT_EQUAL(*(int *)stack_find(stack, key)->data, 9);
  strcpy(key, "eleven");
  CU_ASSERT_EQUAL(stack_find(stack, key), NULL);

  free(key);
  key = NULL;

  CU_ASSERT_EQUAL(stack_find(stack, key), NULL);

  stack_free(&stack);
}

void test_stack_put() {
  Stack stack = (Stack){NULL, 0};

  void *data = malloc(sizeof(int));

  *(int *)data = 1;
  CU_ASSERT_EQUAL(stack_put(&stack, "first", data, sizeof(int)), STACK_SUCCESS);
  CU_ASSERT_EQUAL(*(int *)stack_find(stack, "first")->data, 1);
  CU_ASSERT_EQUAL(stack_find(stack, "first")->next, NULL);

  *(int *)data = 0;
  CU_ASSERT_EQUAL(*(int *)stack_find(stack, "first")->data, 1);

  CU_ASSERT_EQUAL(stack_put(&stack, "first", data, sizeof(int)), STACK_REPLACED);
  CU_ASSERT_EQUAL(*(int *)stack_find(stack, "first")->data, 0);

  *(int *)data = 1;
  CU_ASSERT_EQUAL(stack_put(&stack, "second", data, sizeof(int)), STACK_SUCCESS);
  CU_ASSERT_EQUAL(*(int *)stack_find(stack, "first")->data, 0);
  CU_ASSERT_EQUAL(*(int *)stack_find(stack, "second")->data, 1);

  free(data);
  data = malloc(sizeof(char));

  *(char *)data = 'c';
  CU_ASSERT_EQUAL(*(int *)stack_find(stack, "second")->data, 1);
  CU_ASSERT_EQUAL(stack_put(&stack, "third", data, sizeof(char)), STACK_SUCCESS);
  CU_ASSERT_EQUAL(*(char *)stack_find(stack, "third")->data, 'c');
  CU_ASSERT_EQUAL(stack_find(stack, "first")->next, NULL);

  free(data);
  data = malloc(sizeof(int));

  *(int *)data = 2;
  CU_ASSERT_EQUAL(stack_put(&stack, "first", data, sizeof(int)), STACK_REPLACED);
  CU_ASSERT_EQUAL(*(int *)stack_find(stack, "first")->data, 2);
  CU_ASSERT_EQUAL(*(char *)stack_find(stack, "third")->data, 'c');
  CU_ASSERT_EQUAL(stack_find(stack, "fourth"), NULL);

  CU_ASSERT_EQUAL(stack_put(NULL, "word", data, sizeof(int)), STACK_INVALID_ARGS);
  CU_ASSERT_EQUAL(stack_put(&stack, NULL, data, sizeof(int)), STACK_SUCCESS);
  CU_ASSERT_EQUAL(stack_put(&stack, "word", NULL, sizeof(int)), STACK_INVALID_ARGS);
  CU_ASSERT_EQUAL(stack_put(&stack, "word", data, 0), STACK_INVALID_ARGS);

  stack_free(&stack);
}

void test_stack_remove() {
  Stack stack = (Stack){NULL, 0};

  void *data = malloc(sizeof(int));

  CU_ASSERT_EQUAL(stack_remove(&stack, "new"), NULL);

  *(int *)data = 0;
  stack_put(&stack, "first", data, sizeof(int));
  *(int *)data = 1;
  stack_put(&stack, "second", data, sizeof(int));

  data = malloc(sizeof(char));

  *(char *)data = 'c';
  stack_put(&stack, "third", data, sizeof(char));
  *(char *)data = 'd';
  stack_put(&stack, "fourth", data, sizeof(char));

  CU_ASSERT_NOT_EQUAL_FATAL(stack_find(stack, "first"), NULL);
  CU_ASSERT_EQUAL_FATAL(stack_find(stack, "first")->next, NULL);
  CU_ASSERT_EQUAL(stack_remove(&stack, "fifth"), NULL);
  CU_ASSERT_NOT_EQUAL_FATAL(stack_find(stack, "first"), NULL);
  CU_ASSERT_EQUAL(*(int *)stack_find(stack, "first")->data, 0);
  CU_ASSERT_NOT_EQUAL_FATAL(stack_find(stack, "fourth"), NULL);
  CU_ASSERT_EQUAL(*(char *)stack_find(stack, "fourth")->data, 'd');
  CU_ASSERT_NOT_EQUAL_FATAL(stack_find(stack, "second"), NULL);
  CU_ASSERT_EQUAL(*(int *)stack_find(stack, "second")->data, 1);

  CU_ASSERT_EQUAL(*(int *)stack_remove(&stack, "second"), 1);
  CU_ASSERT_NOT_EQUAL_FATAL(stack_find(stack, "first"), NULL);
  CU_ASSERT_EQUAL(*(int *)stack_find(stack, "first")->data, 0);
  CU_ASSERT_NOT_EQUAL_FATAL(stack_find(stack, "third"), NULL);
  CU_ASSERT_EQUAL(*(char *)stack_find(stack, "third")->data, 'c');
  CU_ASSERT_NOT_EQUAL_FATAL(stack_find(stack, "fourth"), NULL);
  CU_ASSERT_EQUAL(*(char *)stack_find(stack, "fourth")->data, 'd');
  CU_ASSERT_EQUAL_FATAL(*(int *)stack_find(stack, "third")->next->data, 0);

  CU_ASSERT_EQUAL(*(char *)stack_remove(&stack, "third"), 'c');
  CU_ASSERT_EQUAL(stack_find(stack, "third"), NULL);
  CU_ASSERT_EQUAL(*(int *)stack_find(stack, "first")->data, 0);
  CU_ASSERT_EQUAL(*(char *)stack_find(stack, "fourth")->data, 'd');
  CU_ASSERT_EQUAL_FATAL(*(int *)stack_find(stack, "fourth")->next->data, 0);
  CU_ASSERT_EQUAL_FATAL(stack_find(stack, "first")->next, NULL);

  CU_ASSERT_EQUAL(*(int *)stack_remove(&stack, "first"), 0);
  CU_ASSERT_EQUAL(*(char *)stack_find(stack, "fourth")->data, 'd');
  CU_ASSERT_EQUAL(stack_find(stack, "first"), NULL);
  CU_ASSERT_EQUAL_FATAL(stack_find(stack, "fourth")->next, NULL);

  CU_ASSERT_EQUAL(*(char *)stack_remove(&stack, "fourth"), 'd');
  CU_ASSERT_EQUAL(stack.head, NULL);

  stack_free(&stack);
}
