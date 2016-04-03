/** @file
 * Holds all the functions that deal exclusively with Stack's.
 */
#include "stack.h"

/**
 * Helper function for stack_put that clones all the data given into the current
 * head of the stack.
 */
static void set_stack_top(Stack *stack, void *key, void *item, size_t item_size,
                          Node *next) {
  stack->head = (Node *)malloc(sizeof(Node));
  *stack->head = (Node){(char *)malloc((strlen(key) + 1) * sizeof(char)),
                        malloc(item_size), item_size, next};
  strcpy(stack->head->key, key);

  // Copy the value in item into the newly malloc'ed data.
  for(size_t i = 0; i < item_size; i++) {
    *((uint8_t *)stack->head->data + i) = *((uint8_t *)item + i);
  }
}

/**
 * Used to compare two keys of the given size.
 * Note that if the key_size is 0, it is treated as a string.
 */
static int8_t key_comp(void *key_one, void *key_two, size_t key_size) {
  if(key_size == 0)
    return strcmp(key_one, key_two);
  
  for(size_t i = 0; i < key_size; i++) {
    if(*((uint8_t *)key_one + i) != *((uint8_t *)key_two + i))
      return *((uint8_t *)key_one + i) - *((uint8_t *)key_two + i);
  }

  return 0;
}

/**
 * Inserts a new Node with the given key and item.
 * If the key was already in use, that Node's item is replaced with the new one.
 * 
 * @param [in, out] stack The Node to be modified.
 * @param [in] key The key to be stored.
 * @param [in] item The piece data to be stored.
 * @param [in] item_size The size of the data stored at item.
 * @return Stack_Status representing the status of the stack.
 */
Stack_Status stack_put(Stack *stack, void *key, void *item, size_t item_size) {
  if(stack == NULL || key == NULL || item == NULL || item_size == 0)
    return STACK_INVALID_ARGS;
    
  Node *curr;

  if(stack->head == NULL) { // Empty stack
    set_stack_top(stack, key, item, item_size, NULL);
    return STACK_SUCCESS;
  }

  if((curr = stack_find(*stack, key)) == NULL) {
    set_stack_top(stack, key, item, item_size, stack->head);

    return STACK_SUCCESS;
  }

  // Update the value
  if(curr->data_size != item_size) {
    free(curr->data);
    curr->data = malloc(item_size);
    curr->data_size = item_size;
  }
  
  for(size_t i = 0; i < item_size; i++) {
    *((uint8_t *)curr->data + i) = *((uint8_t *)item + i);
  }
  return STACK_REPLACED;
}

/**
 * Removes the Node from the stack with the given key and returns the item associated
 * with that key. If there was no Node associated with the key, returns NULL.
 *
 * @param [in, out] stack The Stack to be edited.
 * @param [in] key The key of the Node to be removed.
 * @return A pointer to the removed data or NULL if there was no Node associated
 * with that key. Also returns NULL if any of the parameters are NULL.
 */
void * stack_remove(Stack *stack, void *key) {
  if(stack == NULL || key == NULL)
    return NULL;

  // Check if the head is the Node to remove.
  if(key_comp(key, stack->head->key, stack->key_size) == 0) {
    Node *next = stack->head->next;
    void *data = stack->head->data;
    free(stack->head->key);

    free(stack->head);
    stack->head = next;

    return data;
  }

  if(stack->head->next == NULL)
    return NULL;

  Node *curr = stack->head;
  while(curr->next != NULL && key_comp(key, curr->key, stack->key_size) != 0)
    curr = curr->next;

  if(curr->next == NULL) {
    return NULL;
  }

  free(curr->next->key);
  void *data = curr->next->data;

  if(curr->next->next == NULL) {
    free(curr->next);
    curr->next = NULL;
  } else {
    Node *next = curr->next->next;
    *curr->next = (Node){next->key, next->data, next->data_size, next->next};
    free(next);
  }

  return data;
}

/**
 * Finds the data associated with the given key or NULL if the key is not present.
 * This is linear, but that should be OK since these will be small stacks for
 * the hashmap.
 *
 * @param [in, out] stack The Stack to be modified.
 * @param [in] key The key to be searched for.
 * @return A pointer to the Node with the associated data or NULL if the key
 * wasn't found.
 */
Node * stack_find(Stack stack, void *key) {
  if(key == NULL)
    return NULL;

  Node *curr = stack.head;

  while(curr != NULL && (curr->key == NULL ||
                         key_comp(key, curr->key, stack.key_size)!= 0))
    curr = curr->next;

  return curr;
}

/**
 * Frees up all the memory used by this Stack and deletes all Node's.
 *
 * @param [in, out] stack The Stack to be cleared.
 */
void stack_free(Stack *stack) {
  if(stack->head == NULL)
    return;

  Node *next;
  while(stack->head->next != NULL) {
    next = stack->head->next;
    free(stack->head->key);
    free(stack->head->data);
    free(stack->head);
    stack->head = next;
  }

  free(stack->head->key);
  free(stack->head->data);
  free(stack->head);
  stack->head = NULL;
}
