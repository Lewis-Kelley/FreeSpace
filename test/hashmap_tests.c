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

int main(int argc, const char *argv[])
{
  int result = ctest_main(argc, argv);

  return result;
}
