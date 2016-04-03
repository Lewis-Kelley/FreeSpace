/** @file
 */
#ifndef HASHMAP_H
#define HASHMAP_H

#include <stddef.h>
#include <stdlib.h>
#include "stack.h"

/**
 * A generic hashmap implementation that can take any key and link it to any item.
 */
typedef struct {
    Stack *data; ///< An array of Stacks that store the actual data.
    uint16_t map_size; ///< The number of buckets in this hashmap.
} Hashmap;

extern uint16_t hash_func(char *key, uint16_t map_size);
extern Stack_Status hashmap_put(Hashmap *map, char *key, void *item, size_t item_size);
extern void * hashmap_remove(Hashmap *map, char *key);
extern Node * hashmap_find(Hashmap map, char *key);
extern void hashmap_free(Hashmap *map);

#endif
