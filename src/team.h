/** @file
 */

#ifndef TEAM_H
#define TEAM_H

/**
 * Indicates what team a given cell or entity is.
 */
typedef enum {
  SELECTED, ///< Currently controlled directly by the player.
  PLAYER, ///< Can be controlled directly by the player, but not in this turn.
  ALLY, ///< AI controlled, but on the same team as the player.
  ENEMY, ///< AI controlled and on opposing team from the player.
  STATIC, ///< Non-moving, neutral entity that cannot attack or be attacked.
  EMPTY ///< Empty cell.
} Team;

#endif
