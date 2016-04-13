#include "CUnit/CUnit.h"
#include "CUnit/Basic.h"
#include "../hashmap/hashmap.h"

#define NEW_HASHMAP(size)                                 \
  (Hashmap){(Stack *)malloc(size * sizeof(Stack)), size};

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
