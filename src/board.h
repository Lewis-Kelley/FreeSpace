/** @file
 */
#ifndef BOARD_H
#define BOARD_H

#include <stdint.h>
#include "tile.h"

/**
 * Holds the dimensions and array of Tile's for a board.
 */
typedef struct Board {
  Tile *tiles; ///< Doubly indexed array of tiles that make up the board.
  uint16_t rows; ///< The number of rows in the board.
  uint16_t cols; ///< The number of columns in the board.
} Board;

#endif /* BOARD_H */
