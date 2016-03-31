/** @file
 * Holds all the functions pertaining to Hashmap's.
 */

#include "hashmap.h"

/**
 * Returns a hash code representing the given key.
 *
 * @param [in] key The key to be hashed.
 * @param [in] map_size The number of buckets in the hashmap. The hash will be less than this number.
 * @return Hash code representing the given key.
 */
uint16_t hash_func(char *key, uint16_t map_size) {
  uint16_t hash = 0; //TODO Make an actual function.
  return hash;
}

/**
 * Stores the given item-key pair in the Hashmap.
 * If there was already an item stored under the given key,
 * that old item is replaced for the new one.
 * 
 * @param [in, out] map The Hashmap to store the items in.
 * @param [in] key The key to be added.
 * @param [in] item The item to be added.
 * @return 0 if successfully inserted, -1 if there was an invalid parameter,
 * or -2 if there was already an item mapped to that key.
 */
int8_t hashmap_put(Hashmap *map, char *key, void *item, size_t item_size) {
  return stack_put(&(map->data[hash_func(key, map->map_size)]), key, item, item_size);
}

/**
 * Removes the key and its paired item from the Hashmap.
 *
 * @param [in, out] map The Hashmap to be edited.
 * @param [in] key The key to be removed.
 * @return A pointer to the data paired with the key or NULL if there wasn't any reference to the key in the map.
 */
void * hashmap_remove(Hashmap *map, char *key) {
  return stack_remove(&(map->data[hash_func(key, map->map_size)]), key);
}

/**
 * Finds the data linked with the given key.
 *
 * @param [in] map The Hashmap to be queried.
 * @param [in] key The key to be searched for.
 * @return The data associated with the given key.
 */
void * hashmap_find(Hashmap map, char *key) {
  if(map.data[0].data != NULL)
    printf("In hashmap_find with stack = {%s, %d, %p}\n", map.data[0].key,
           *(int *)map.data[0].data, map.data[0].next);

  Node *res = stack_find(map.data[hash_func(key, map.map_size)], key);
  
  if(res == NULL)
    return NULL;

  return res->data;
}

/**
 * Frees all the memory used by this hashmap.
 *
 * @param [in, out] map A pointer to the Hashmap to be removed.
 */
void hashmap_free(Hashmap *map) {
  for(uint16_t i = 0; i < map->map_size; i++)
    stack_free(&(map->data[i]));

  free(map->data);
  free(map);
}

#ifdef DEBUG
/**
 * Prints out the contents of the hashmap.
 *
 * @param [in] map The hashmap to be printed.
 */
void hashmap_print(Hashmap map) {
  Node *curr;
  for(uint16_t i = 0; i < map.map_size; i++) {
    printf("[%d]:\n", i);
    curr = &(map.data[i]);
    while(curr->next != NULL) {
      if(curr->data != NULL)
        printf("\t%d\n", *(int *)curr->data);

      curr = curr->next;
    }
  }
}
#endif
