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
  char *key; ///< The key pointing to the data in this Node.
  void *data; ///< The generic data held in this Node.
  size_t data_size; ///< The size of the data in this Node.
  struct _Node *next; ///< A pointer to the next element in the list.
} Node;

int16_t stack_put(Node *stack, char *key, void *item, size_t item_size);
void * stack_remove(Node *stack, char *key);
Node * stack_find(Node stack, char *key);
void stack_free(Node *stack);
#endif
