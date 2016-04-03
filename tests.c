#include <stdio.h>
#include "CUnit/CUnit.h"
#include "CUnit/Basic.h"
#include "src/hashmap.h"

#define NEW_HASHMAP(size)                                 \
  (Hashmap){(Stack *)malloc(size * sizeof(Stack)), size};

int init_suite() {
  return 0;
}

int clean_suite() {
  return 0;
}

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
  CU_ASSERT_EQUAL(stack_put(&stack, NULL, data, sizeof(int)), STACK_INVALID_ARGS);
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

void test_hashmap_free() {
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
  CU_PASS();

  hashmap = NEW_HASHMAP(100);
  for(int i = 0; i < 100; i++) {
    hashmap.data[i].key_size = 0;
    hashmap.data[i].head = NULL;
  }

  hashmap_free(&hashmap);
  CU_PASS();
}

void test_hashmap_put() {
  Hashmap hashmap = NEW_HASHMAP(100);
  for(int i = 0; i < 100; i++) {
    hashmap.data[i].key_size = 0;
    hashmap.data[i].head = NULL;
  }

  void *data = malloc(sizeof(int));

  *(int *)data = 100;
  CU_ASSERT_EQUAL(hashmap_put(&hashmap, "one", data, sizeof(int)),
                  STACK_SUCCESS);
  CU_ASSERT_EQUAL(*(int *)stack_find(hashmap.data[hash_func("one",
                                                            hashmap.data[0].
                                                            key_size, 100)],
                                     "one")->data, 100);

  *(int *)data = 101;
  CU_ASSERT_EQUAL(hashmap_put(&hashmap, "one", data, sizeof(int)),
                  STACK_REPLACED);
  CU_ASSERT_EQUAL(*(int *)stack_find(hashmap.data[hash_func("one",
                                                            hashmap.data[0].
                                                            key_size, 100)],
                                     "one")->data, 101);

  *(int *)data = 102;
  CU_ASSERT_EQUAL(hashmap_put(&hashmap, "two", data, sizeof(int)),
                  STACK_SUCCESS);
  CU_ASSERT_EQUAL(*(int *)stack_find(hashmap.data[hash_func("two",
                                                            hashmap.data[0].
                                                            key_size, 100)],
                                     "two")->data, 102);

  free(data);
  data = malloc(sizeof(char));

  *(char *)data = 'a';
  CU_ASSERT_EQUAL(hashmap_put(&hashmap, "three", data, sizeof(int)),
                  STACK_SUCCESS);
  CU_ASSERT_EQUAL(*(char *)stack_find(hashmap.data[hash_func("three",
                                                             hashmap.data[0].
                                                             key_size, 100)],
                                      "three")->data, 'a');
  CU_ASSERT_EQUAL(stack_find(hashmap.data[hash_func("three",
                                                    hashmap.data[0].
                                                    key_size, 100)], "thwee"),
                  NULL);

  CU_ASSERT_EQUAL(hashmap_put(&hashmap, "one", data, sizeof(char)),
                  STACK_REPLACED);
  CU_ASSERT_EQUAL(*(char *)stack_find(hashmap.data[hash_func("one",
                                                             hashmap.data[0].
                                                             key_size, 100)],
                                      "one")->data, 'a');

  hashmap_free(&hashmap);
}

void test_hashmap_find() {
  Hashmap hashmap = NEW_HASHMAP(100);
  for(int i = 0; i < 100; i++) {
    hashmap.data[i].key_size = 0;
    hashmap.data[i].head = NULL;
  }

  void *data = malloc(sizeof(int));

  *(int *)data = 0;
  hashmap_put(&hashmap, "first", data, sizeof(int));
  CU_ASSERT_EQUAL(*(int *)hashmap_find(hashmap, "first")->data, 0);
  CU_ASSERT_EQUAL(hashmap_find(hashmap, "second"), NULL);

  *(int *)data = 1;
  hashmap_put(&hashmap, "second", data, sizeof(int));
  CU_ASSERT_EQUAL(*(int *)hashmap_find(hashmap, "second")->data, 1);
  CU_ASSERT_EQUAL(*(int *)hashmap_find(hashmap, "first")->data, 0);

  free(data);
  data = malloc(sizeof(char));

  *(char *)data = 'c';
  hashmap_put(&hashmap, "third", data, sizeof(char));
  CU_ASSERT_EQUAL(*(char *)hashmap_find(hashmap, "third")->data, 'c');

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
  CU_ASSERT_NOT_EQUAL_FATAL(hashmap_find(hashmap, key), NULL);
  CU_ASSERT_EQUAL(*(int *)hashmap_find(hashmap, key)->data, 0);

  *(int *)key = 1;
  *(int *)data = 1;
  CU_ASSERT_EQUAL(hashmap_find(hashmap, key), NULL);
  hashmap_put(&hashmap, key, data, sizeof(int));
  CU_ASSERT_NOT_EQUAL_FATAL(hashmap_find(hashmap, key), NULL);
  CU_ASSERT_EQUAL(*(int *)hashmap_find(hashmap, key)->data, 1);

  *(int *)key = 0;
  CU_ASSERT_EQUAL(*(int *)hashmap_find(hashmap, key)->data, 0);

  hashmap_free(&hashmap);
}

void test_hashmap_remove() {
  Hashmap hashmap = NEW_HASHMAP(100);
  for(int i = 0; i < 100; i++) {
    hashmap.data[i].key_size = 0;
    hashmap.data[i].head = NULL;
  }

  void *data = malloc(sizeof(int));

  CU_ASSERT_EQUAL_FATAL(hashmap_remove(&hashmap, "anything"), NULL);

  *(int *)data = 5;
  hashmap_put(&hashmap, "five", data, sizeof(int));

  *(int *)data = 7;
  hashmap_put(&hashmap, "seven", data, sizeof(int));
  CU_ASSERT_EQUAL_FATAL(*(int *)hashmap_remove(&hashmap, "five"), 5);
  CU_ASSERT_EQUAL(hashmap_find(hashmap, "five"), NULL);
  CU_ASSERT_EQUAL(hashmap_remove(&hashmap, "five"), NULL);

  hashmap_free(&hashmap);
}

#define QUIT do { CU_cleanup_registry(); return CU_get_error(); } while(0);

int main(int argc, char **argv) {
  CU_Suite *stack_suite = NULL,
    *hashmap_suite = NULL;

  if(CUE_SUCCESS != CU_initialize_registry())
    return CU_get_error();

  stack_suite = CU_add_suite("stack_test_suite", init_suite, clean_suite);
  hashmap_suite = CU_add_suite("hashmap_test_suite", init_suite, clean_suite);

  if(stack_suite == NULL || hashmap_suite == NULL)
    QUIT;

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
