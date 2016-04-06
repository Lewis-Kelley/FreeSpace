/** @file
 */

#ifndef TEAM_H
#define TEAM_H

/**
 * Indicates what team a given cell or entity is.
 */
typedef enum {
  TEAM_SELECTED, ///< Currently controlled directly by the player.
  TEAM_PLAYER, ///< Can be controlled directly by the player, but not in this turn.
  TEAM_ALLY, ///< AI controlled, but on the same team as the player.
  TEAM_ENEMY, ///< AI controlled and on opposing team from the player.
  TEAM_STATIC, ///< Non-moving, neutral entity that cannot attack or be attacked.
  TEAM_EMPTY ///< Empty cell.
} Team;

#endif
