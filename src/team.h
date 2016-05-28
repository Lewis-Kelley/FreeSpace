/** @file
 */

#ifndef TEAM_H
#define TEAM_H

/**
 * Indicates what team a given cell or entity is.
 */
typedef enum {
  TEAM_SELECTED = 1, ///< Currently controlled directly by the player.
  TEAM_PLAYER = 2, ///< Can be controlled directly by the player, but not in this turn.
  TEAM_ALLY = 4, ///< AI controlled, but on the same team as the player.
  TEAM_ENEMY = 8, ///< AI controlled and on opposing team from the player.
} Team;

#endif
