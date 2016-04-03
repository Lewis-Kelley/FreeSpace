/** @file
 */
#ifndef STACK_H
#define STACK_H

#include <stddef.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

/**
 * Holds a single piece of data and its string key in the Stack
 */
typedef struct _Node {
  void *key; ///< The key pointing to the data in this Node.
  void *data; ///< The generic data held in this Node.
  size_t data_size; ///< The size of the data in this Node.
  struct _Node *next; ///< A pointer to the next element in the list.
} Node;

/**
 * Hold the top of the stack and the size of the key used.
 */
typedef struct {
  Node *head; ///< The top of this stack.
  size_t key_size; ///< The size of the key.
} Stack;

/**
 * Return status for stack_put.
 */
typedef enum {
  STACK_SUCCESS = 0, ///< The item was put onto the stack without collisions.
  STACK_INVALID_ARGS = 1, ///< An argument was invalid.
  STACK_REPLACED = 2 ///< The key was already present, and it's item was replaced.
} Stack_Status;

extern Stack_Status stack_put(Stack *stack, void *key, void *item, size_t item_size);
extern void * stack_remove(Stack *stack, void *key);
extern Node * stack_find(Stack stack, void *key);
extern void stack_free(Stack *stack);
#endif
