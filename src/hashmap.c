/** @file
 * Holds all the functions pertaining to Hashmap's.
 */

#include "hashmap.h"

/**
 * Returns a hash code representing the given key.
 * This is based on the djb2 hash code.
 *
 * @param [in] key The key to be hashed.
 * @param [in] key_size The size of whatever the key is.
 * @param [in] map_size The number of buckets in the hashmap. The hash will be less than this number.
 * @return Hash code representing the given key.
 */
uint16_t hash_func(void *key, size_t key_size, uint16_t map_size) {
  int32_t hash = 5381;
  int8_t c;

  if(key_size == 0)
    while((c = *(uint8_t *)key++))
      hash = (hash << 5) + hash + c; //hash * 33 + c
  else
    for(size_t i = 0; i < key_size; i++)
      hash = (hash << 5) + hash + *(uint8_t *)(key + i);

  return (hash % map_size);
}

/**
 * Stores the given item-key pair in the Hashmap.
 * If there was already an item stored under the given key,
 * that old item is replaced for the new one.
 * 
 * @param [in, out] map The Hashmap to store the items in.
 * @param [in] key The key to be added.
 * @param [in] item The item to be added.
 * @param [in] item_size The number of bytes stored at item.
 * @return Stack_Status representing the status of the insertion.
 */
Stack_Status hashmap_put(Hashmap *map, void *key, void *item, size_t item_size) {
  return stack_put(map->data + hash_func(key, map->data[0].key_size, map->map_size), key, item, item_size);
}

/**
 * Removes the key and its paired item from the Hashmap.
 *
 * @param [in, out] map The Hashmap to be edited.
 * @param [in] key The key to be removed.
 * @return A pointer to the data paired with the key or NULL if there wasn't any reference to the key in the map.
 */
void * hashmap_remove(Hashmap *map, void *key) {
  return stack_remove(map->data + hash_func(key, map->data[0].key_size, map->map_size), key);
}

/**
 * Finds the data linked with the given key.
 *
 * @param [in] map The Hashmap to be queried.
 * @param [in] key The key to be searched for.
 * @return a pointer to the Node associated with the given key or
 * NULL if the key wasn't found.
 */
Node * hashmap_find(Hashmap map, void *key) {
  return stack_find(map.data[hash_func(key, map.data[0].key_size, map.map_size)], key);
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
