#ifndef TILE_H
#define TILE_H

/**
 * The different kinds of blocking a tile can do.
 */
typedef enum {
  BLOCK_PLAYER = 1, ///< If a player unit can enter this tile.
  OCCUPY_PLAYER = 2, ///< If a player unit can stop on this tile.
  BLOCK_ALLY = 4, ///< If an allied unit can enter this tile.
  OCCUPY_ALLY = 8, ///< If an allied unit can stop on this tile.
  BLOCK_ENEMY = 16, ///< If an enemy unit can enter this tile.
  OCCUPY_ENEMY = 32 ///< If an enemy unit can stop on this tile.
} Block_Status;

/**
 * Holds the information on a given tile.
 */
typedef struct Tile {
  void *ent; ///< The entity in this tile. Must be typecast to the correct type.
  Block_Status block; ///< The types of blocking conditions this tile has.
} Tile;

#endif /* TILE_H */
