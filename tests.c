#include <stdio.h>
#include "CUnit/CUnit.h"
#include "CUnit/Basic.h"
#include "src/hashmap.h"

int init_suite() {
  return 0;
}

int clean_suite() {
  return 0;
}

void test_stack_find() {
  Node stack = (Node){(char *)malloc(256 * sizeof(char)), malloc(sizeof(int)),
                      sizeof(int), NULL};
  Node *curr = &stack;
  *(int *)stack.data = 0;

  for(int i = 1; i < 10; i++){
    curr->next = (Node *)malloc(sizeof(Node));
    *curr->next = (Node){(char *)malloc(256 * sizeof(char)), malloc(sizeof(int)),
                         sizeof(int), NULL};

    curr = curr->next;
    *(int *)curr->data = i;
  }

  curr = &stack;
  curr->key = "first";
  curr = curr->next;
  curr->key = "second";
  curr = curr->next;
  curr->key = "third";
  curr = curr->next;
  curr->key = "fourth";
  curr = curr->next;
  curr->key = "fifth";
  curr = curr->next;
  curr->key = "sixth";
  curr = curr->next;
  curr->key = "seventh";
  curr = curr->next;
  curr->key = "eighth";
  curr = curr->next;
  curr->key = "ninth";
  curr = curr->next;
  curr->key = "tenth";

  CU_ASSERT_EQUAL(*(int *)stack_find(stack, "first")->data, 0);
  CU_ASSERT_EQUAL(*(int *)stack_find(stack, "second")->data, 1);
  CU_ASSERT_EQUAL(*(int *)stack_find(stack, "fourth")->data, 3);
  CU_ASSERT_EQUAL(*(int *)stack_find(stack, "first")->data, 0);
  CU_ASSERT_EQUAL(*(int *)stack_find(stack, "third")->data, 2);
  CU_ASSERT_EQUAL(*(int *)stack_find(stack, "tenth")->data, 9);
  CU_ASSERT_EQUAL(stack_find(stack, "eleventh"), NULL);
  CU_ASSERT_EQUAL(stack_find(stack, NULL), NULL);
}

void test_stack_put() {
  Node stack = (Node){NULL, NULL, 0, NULL};

  void *data = malloc(sizeof(int));
  
  *(int *)data = 1;
  CU_ASSERT_EQUAL(stack_put(&stack, "first", data, sizeof(int)), 0);
  CU_ASSERT_EQUAL(*(int *)stack_find(stack, "first")->data, 1);

  *(int *)data = 0;
  CU_ASSERT_EQUAL(*(int *)stack_find(stack, "first")->data, 1);

  CU_ASSERT_EQUAL(stack_put(&stack, "first", data, sizeof(int)), -2);
  CU_ASSERT_EQUAL(*(int *)stack_find(stack, "first")->data, 0);

  *(int *)data = 1;
  CU_ASSERT_EQUAL(stack_put(&stack, "second", data, sizeof(int)), 0);
  CU_ASSERT_EQUAL(*(int *)stack_find(stack, "first"), 0);
  CU_ASSERT_EQUAL(*(int *)stack_find(stack, "second"), 1);

  free(data);
  data = malloc(sizeof(char));

  *(char *)data = 'c';
  CU_ASSERT_EQUAL(*(int *)stack_find(stack, "second"), 1);
  CU_ASSERT_EQUAL(stack_put(&stack, "third", data, sizeof(char)), 0);
  CU_ASSERT_EQUAL(*(char *)stack_find(stack, "third"), 'c');

  *(char *)data = 'd';
  CU_ASSERT_EQUAL(*(int *)stack_find(stack, "first"), 1);
  CU_ASSERT_EQUAL(*(char *)stack_find(stack, "third"), 'c');
  CU_ASSERT_EQUAL(stack_find(stack, "fourth"), NULL);
}

void test_stack_remove() {
  Node stack = (Node){NULL, NULL, 0, NULL};

  void *data = malloc(sizeof(int));

  *(int *)data = 0;
  stack_put(&stack, "first", data, sizeof(int));
  *(int *)data = 1;
  stack_put(&stack, "second", data, sizeof(int));

  data = malloc(sizeof(char));

  *(char *)data = 'c';
  stack_put(&stack, "third", data, sizeof(char));
  *(char *)data = 'd';
  stack_put(&stack, "fourth", data, sizeof(char));

  CU_ASSERT_EQUAL(stack_remove(&stack, "fifth"), NULL);
  CU_ASSERT_EQUAL(*(int *)stack_find(stack, "first")->data, 0);
  CU_ASSERT_EQUAL(*(char *)stack_find(stack, "fourth")->data, 'd');

  CU_ASSERT_EQUAL(*(int *)stack_remove(&stack, "second"), 1);
  CU_ASSERT_EQUAL(*(int *)stack_find(stack, "first")->data, 0);
  CU_ASSERT_EQUAL(*(char *)stack_find(stack, "third")->data, 'c');
  CU_ASSERT_EQUAL(*(char *)stack_find(stack, "fourth")->data, 'd');

  CU_ASSERT_EQUAL(*(char *)stack_remove(&stack, "third"), 'c');
  CU_ASSERT_EQUAL(stack_find(stack, "third"), NULL);
  CU_ASSERT_EQUAL(*(int *)stack_find(stack, "first")->data, 0);
  CU_ASSERT_EQUAL(*(char *)stack_find(stack, "fourth")->data, 'd');

  CU_ASSERT_EQUAL(*(int *)stack_remove(&stack, "first"), 0);
  CU_ASSERT_EQUAL(*(char *)stack_find(stack, "fourth")->data, 'd');
  CU_ASSERT_EQUAL(stack_find(stack, "first"), NULL);
}

void test_stack_free() {

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

  if(CU_add_test(stack_suite, "stack_find", test_stack_find) == NULL
     || CU_add_test(stack_suite, "stack_put", test_stack_put) == NULL
     || CU_add_test(stack_suite, "stack_remove", test_stack_remove) == NULL
     || CU_add_test(stack_suite, "stack_free", test_stack_free) == NULL)
    QUIT;

  CU_basic_set_mode(CU_BRM_VERBOSE);
  CU_basic_run_test(stack_suite, CU_get_test(stack_suite, "stack_find"));
  CU_basic_run_test(stack_suite, CU_get_test(stack_suite, "stack_put"));
  CU_basic_show_failures(CU_get_failure_list());
  printf("\n");

  QUIT;
}
