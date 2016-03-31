/** @file
 * Holds all the functions that deal exclusively with Stack's.
 */
#include "stack.h"

/**
 * Inserts a new Node with the given key and item.
 * If the key was already in use, that Node's item is replaced with the new one.
 * 
 * @param list The Node to be modified.
 * @param key The key to be stored.
 * @param item The piece data to be stored.
 * @return 0 if successful and the key was not already in use, -1 if there was invalid input,
 * or -2 if the key was already use.
 */
int16_t stack_put(Node *stack, char *key, void *item) {
    if(stack == NULL || key == NULL || item == NULL)
        return -1;
    
    Node *curr;
    if((curr = stack_find(*stack, key)) == NULL) {
        curr = (Node *)malloc(sizeof(Node));
        *curr = (Node){stack->key, stack->data, stack->next};
        *stack = (Node){key, item, curr};
        return 0;
    }

    curr->data = item;
    return -2;
}

/**
 * Removes the Node from the stack with the given key and returns the item associated with that key.
 * If there was no Node associated with the key, returns NULL.
 *
 * @param stack The Stack to be edited.
 * @param key The key of the Node to be removed.
 * @return A pointer to the removed data or NULL if there was no Node associated with that key.
 * Also returns NULL if any of the parameters are NULL.
 */
void * stack_remove(Node *stack, char *key) {
    if(strcmp(key, stack->key) == 0) { // The head is the Node to remove.
        void *data = stack->data;
        free(stack->key);

        if(stack->next == NULL)
            free(stack);
        else {
            Node *next = stack->next;
            *stack = (Node){next->key, next->data, next->next};
            free(next);
        }

        return data;
    }

    if(stack->next == NULL)
        return NULL;

    
    while(stack->next != NULL && strcmp(key, stack->next->key) != 0)
        stack = stack->next;

    if(strcmp(key, stack->next->key) == 0) {
        void *data = stack->next->data;
        free(stack->next->key);

        if(stack->next->next == NULL)
            free(stack->next);
        else {
            Node *next = stack->next->next;
            *stack->next = (Node){next->key, next->data, next->next};
            free(next);
        }

        return data;
    }

    return NULL;
}

/**
 * Finds the data associated with the given key or NULL if the key is not present.
 * This is linear, but that should be OK since these will be small stacks for the hashmap.
 *
 * @param stack The Stack to be modified.
 * @param key The key to be searched for.
 * @return A pointer to the Node with the associated data or NULL if the key wasn't found.
 */
Node * stack_find(Node stack, char *key) {
    if(key == NULL)
        return NULL;
    
    Node *curr = &stack;

    while(curr->next != NULL && strcmp(key, curr->key) != 0)
        curr = curr->next;

    if(strcmp(key, curr->key) == 0)
        return curr;

    return NULL;
}

/**
 * Frees up all the memory used by this Stack and deletes all Node's.
 *
 * @param stack The Stack to be cleared.
 */
void stack_free(Node *stack) {
    Node *temp;

    while(stack->next != NULL) {
        free(stack->next->key);
        free(stack->next->data);

        temp = stack->next->next;
        free(stack->next);

        stack->next = temp;
    }

    free(stack->key);
    free(stack->data);
    free(stack);
}
