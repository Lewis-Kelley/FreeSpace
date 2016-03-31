/** @file
 * Holds all the functions pertaining to Hashmap's.
 */

#include "hashmap.h"


/**
 * Returns a hash code representing the given key.
 *
 * @param key The key to be hashed.
 * @param map_size The number of buckets in the hashmap. The hash will be less than this number.
 * @return Hash code representing the given key.
 */
uint16_t hash_func(char *key, uint16_t map_size) {
    uint16_t hash = 0;
    return hash;
}

/**
 * Stores the given item-key pair in the Hashmap.
 * If there was already an item stored under the given key,
 * that old item is replaced for the new one.
 * 
 * @param map The Hashmap to store the items in.
 * @param key The key to be added.
 * @param item The item to be added.
 * @return 0 if successfully inserted, -1 if there was an invalid parameter,
 * or -2 if there was already an item mapped to that key.
 */
int8_t hashmap_put(Hashmap *map, char *key, void *item) {
    return stack_put(&(map->data[hash_func(key, map->map_size)]), key, item);
}

/**
 * Removes the key and its paired item from the Hashmap.
 *
 * @param map The Hashmap to be edited.
 * @param key The key to be removed.
 * @return A pointer to the data paired with the key or NULL if there wasn't any reference to the key in the map.
 */
void * hashmap_remove(Hashmap *map, char *key) {
    return stack_remove(&(map->data[hash_func(key, map->map_size)]), key);
}

/**
 * Finds the data linked with the given key.
 *
 * @param map The Hashmap to be queried.
 * @param key The key to be searched for.
 */
void * hashmap_find(Hashmap map, char *key) {
    return stack_find(map.data[hash_func(key, map.map_size)], key);
}

/**
 * Frees all the memory used by this hashmap.
 *
 * @param map A pointer to the Hashmap to be removed.
 */
void hashmap_free(Hashmap *map) {
    for(uint16_t i = 0; i < map->map_size; i++)
        stack_free(&(map->data[i]));

    free(map->data);
    free(map);
}
