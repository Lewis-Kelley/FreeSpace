/** @file
 * Holds the declaration of the Cell_State struct.
 */
#ifndef CELL_STATE_H
#define CELL_STATE_H

/** @enum Cell_State
 * Holds all the different values that a cell can be.
 */
typedef enum {
    CELL_EMPTY, ///< The cell is empty
    CELL_X, ///< The cell has an X in it
    CELL_O ///< The cell has an O in it
} Cell_State;

#endif
