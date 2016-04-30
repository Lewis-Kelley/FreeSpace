#include "update.h"

void bat_entity_key_update(Battle_Entity *ent, Game_Data *game_data) {
  int dest;
  switch(game_data->battle_data.keys & KEY_MOVE) {
  case KEY_MOVE_LEFT:
  case KEY_MOVE_RIGHT:
    if(ABS(ent->vel.x) >= ROUNDOFF) {
      ent->pos.x = ((Coord_i *)ent->move_queue.head->data)->x
        + game_data->battle_data.camera_pos.x;

      ent->img.dest_x = ent->pos.x * (double)WIN_WIDTH /
        game_data->battle_data.cols + game_data->battle_data.camera_pos.x;      
      stack_remove(&ent->move_queue, NULL);
    } else if (ABS(ent->vel.y) >= ROUNDOFF) {
      ent->vel.y = 0.0;
      ent->pos.y = ((Coord_i *)ent->move_queue.head->data)->y
        + game_data->battle_data.camera_pos.y;

      ent->img.dest_y = (ent->pos.y + game_data->battle_data.camera_pos.y)
        * (double)WIN_HEIGHT / game_data->battle_data.rows;

      stack_remove(&ent->move_queue, NULL);
    }

    if((game_data->battle_data.keys & KEY_MOVE) == KEY_MOVE_RIGHT) {
      dest = ent->pos.x + 1;
      ent->vel.x = MOVE_SPEED;
    } else {
      dest = ent->pos.x - 1;
      ent->vel.x = -MOVE_SPEED;
    }

    if(dest < game_data->battle_data.cols && dest >= 0
       && bat_ent_lookup(game_data, dest, ent->pos.y)->team == TEAM_EMPTY) {
      Coord_i *dest_coord = malloc(sizeof *dest_coord);
      dest_coord->x = dest;
      dest_coord->y = ent->pos.y;

      stack_put(&ent->move_queue, NULL, dest_coord, sizeof *dest_coord);
      free(dest_coord);
      
      Battle_Entity *dest_ent = bat_ent_lookup(game_data, dest, ent->pos.y);
      game_data->battle_data.board[(int)ent->pos.y * game_data->battle_data.cols
                                   + (int)ent->pos.x] = dest_ent;
      game_data->battle_data.board[(int)dest_ent->pos.y
                                   * game_data->battle_data.cols
                                   + (int)dest_ent->pos.x] = ent;
      dest_ent->pos.x = ent->pos.x;
    } else {
      ent->vel.x = 0.0;
    }
    break;
  case KEY_MOVE_UP:
  case KEY_MOVE_DOWN:
    if(ABS(ent->vel.y) >= ROUNDOFF) {
      ent->pos.y = ((Coord_i *)ent->move_queue.head->data)->y
        + game_data->battle_data.camera_pos.y;

      ent->img.dest_y = (ent->pos.y + game_data->battle_data.camera_pos.y)
        * (double)WIN_HEIGHT / game_data->battle_data.rows;

      stack_remove(&ent->move_queue, NULL);
    } else if (ABS(ent->vel.x) >= ROUNDOFF) {
      ent->vel.x = 0.0;
      ent->pos.x = ((Coord_i *)ent->move_queue.head->data)->x
        + game_data->battle_data.camera_pos.x;

      ent->img.dest_x = (ent->pos.x + game_data->battle_data.camera_pos.x)
        * (double)WIN_WIDTH / game_data->battle_data.cols;

      stack_remove(&ent->move_queue, NULL);
    }

    if((game_data->battle_data.keys & KEY_MOVE) == KEY_MOVE_DOWN) {
      dest = ent->pos.y + 1;
      ent->vel.y = MOVE_SPEED;
    } else {
      dest = ent->pos.y - 1;
      ent->vel.y = -MOVE_SPEED;
    }

    if(dest < game_data->battle_data.rows && dest >= 0
       && bat_ent_lookup(game_data, ent->pos.x, dest)->team == TEAM_EMPTY) {
      Coord_i *dest_coord = malloc(sizeof *dest_coord);
      dest_coord->x = ent->pos.x;
      dest_coord->y = dest;

      stack_put(&ent->move_queue, NULL, dest_coord, sizeof *dest_coord);
      free(dest_coord);
      
      Battle_Entity *dest_ent = bat_ent_lookup(game_data, ent->pos.x, dest);
      game_data->battle_data.board[(int)ent->pos.y * game_data->battle_data.cols
                                   + (int)ent->pos.x] = dest_ent;
      game_data->battle_data.board[(int)dest_ent->pos.y
                                   * game_data->battle_data.cols
                                   + (int)dest_ent->pos.x] = ent;
      dest_ent->pos.y = ent->pos.y;
    } else {
      ent->vel.y = 0.0;
    }
    break;
  default:
    break;
  }
}

/**
 * Takes an Battle_Entity to update given that it is at a cell
 * intersection and a move key has been pressed.
 *
 * @param [in, out] ent The Battle_Entity that is being updated.
 * @param [in, out] battle_data The current state of the game.
 */
void battle_entity_key_update(Battle_Entity *ent, Battle_Data *battle_data) {
  Coord_i dest;
  if(ABS(ent->vel.x) >= ROUNDOFF || ABS(ent->vel.y) >= ROUNDOFF) {
    ent->pos.x = ((Coord_i *)ent->move_queue.head->data)->x
      + battle_data->camera_pos.x;
    ent->pos.y = ((Coord_i *)ent->move_queue.head->data)->y
      + battle_data->camera_pos.y;

    ent->img.dest_x = ent->pos.x * (double)WIN_WIDTH /
      battle_data->cols + battle_data->camera_pos.x;      
    ent->img.dest_y = (ent->pos.y + battle_data->camera_pos.y)
      * (double)WIN_HEIGHT / battle_data->rows;

    stack_remove(&ent->move_queue, NULL);
  }

  switch(battle_data->keys & KEY_MOVE) {
  case KEY_MOVE_RIGHT:
    dest.x = ent->pos.x + 1;
    dest.y = ent->pos.y;

    ent->vel.x = MOVE_SPEED;
    ent->vel.y = 0;
    break;
  case KEY_MOVE_LEFT:
    dest.x = ent->pos.x - 1;
    dest.y = ent->pos.y;

    ent->vel.x = -MOVE_SPEED;
    ent->vel.y = 0;
    break;
  case KEY_MOVE_UP:
    dest.x = ent->pos.x;
    dest.y = ent->pos.y - 1;

    ent->vel.x = 0;
    ent->vel.y = -MOVE_SPEED;
    break;
  case KEY_MOVE_DOWN:
    dest.x = ent->pos.x;
    dest.y = ent->pos.y + 1;

    ent->vel.x = 0;
    ent->vel.y = MOVE_SPEED;
    break;
  case 0:
    ent->vel.x = 0;
    ent->vel.y = 0;
    return;
  }

  if(dest.x < battle_data->cols && dest.y < battle_data->rows
     && battle_data->board[dest.y * battle_data->cols + dest.x]->team
     == TEAM_EMPTY) {

    stack_put(&ent->move_queue, NULL, &dest, sizeof dest);

    Battle_Entity *dest_ent = battle_data->board[dest.y * battle_data->cols
                                                 + dest.x];
    battle_data->board[(int)ent->pos.y * battle_data->cols
                       + (int)ent->pos.x] = dest_ent;
    battle_data->board[(int)dest_ent->pos.y * battle_data->cols
                       + (int)dest_ent->pos.x] = ent;
    dest_ent->pos.x = ent->pos.x;
    dest_ent->pos.y = ent->pos.y;
  } else {
    ent->vel.x = 0.0;
    ent->vel.y = 0.0;
  }
}

/**
 * Updates the various fields of ent given the amount of time passed since
 * the last tick.
 *
 * @param [in, out] ent The Battle_Entity to be updated.
 * @param [in, out] game_data The current state of the game.
 */
void battle_entity_update(Battle_Entity *ent, Game_Data *game_data,
                          double delta) {
  if(ent->team != TEAM_EMPTY) {
    if(game_data->battle_data.camera_vel.x != 0.0) {
      ent->img.dest_x -= game_data->battle_data.camera_vel.x * delta;
    }

    if(game_data->battle_data.camera_vel.y != 0.0) {
      ent->img.dest_y -= game_data->battle_data.camera_vel.y * delta;
    }

    if(ent->move_queue.head != NULL) {
      if(ent->vel.x != 0.0) {
        ent->pos.x += ent->vel.x * delta;

        if(ABS(ent->pos.x
               - ((Coord_i *)ent->move_queue.head->data)->x) < ROUNDOFF
           || (ent->vel.x > 0.0 && ent->pos.x >
               ((Coord_i *)ent->move_queue.head->data)->x)
           || (ent->vel.x < 0.0 && ent->pos.x <
               ((Coord_i *)ent->move_queue.head->data)->x)) {
          if((game_data->battle_data.keys & KEY_MOVE) != 0) {
            battle_entity_key_update(ent, &(game_data->battle_data));
          } else {
            ent->vel.x = 0.0;
            ent->pos.x = ((Coord_i *)ent->move_queue.head->data)->x
              + game_data->battle_data.camera_pos.x;

            stack_remove(&ent->move_queue, NULL);
          }
        } else {
          ent->img.dest_x += ent->vel.x * ent->img.dest_w * delta;
        }
      } else if(ent->vel.y != 0.0) {
        ent->pos.y += ent->vel.y * delta;

        if(ABS(ent->pos.y
               - ((Coord_i *)ent->move_queue.head->data)->y) < ROUNDOFF
           || (ent->vel.y > 0.0 && ent->pos.y >
               ((Coord_i *)ent->move_queue.head->data)->y)
           || (ent->vel.y < 0.0 && ent->pos.y <
               ((Coord_i *)ent->move_queue.head->data)->y)) {

          ent->pos.y = ((Coord_i *)ent->move_queue.head->data)->y;
          ent->img.dest_y = ent->pos.y * ent->img.dest_h
            + game_data->battle_data.camera_pos.y;
          ent->vel = (Coord_f){0.0, 0.0};

          stack_remove(&ent->move_queue, NULL);
        } else {
          ent->img.dest_y += ent->vel.y * ent->img.dest_h * delta;
        }
      }
    } else if(ent->team == TEAM_SELECTED
              && (game_data->battle_data.keys & KEY_MOVE) != 0) {
      battle_entity_key_update(ent, &(game_data->battle_data));
    }
  }
}

/**
 * Checks the time delta and updates the game state accordingly.
 *
 * @param [in, out] game_data The current state of the game.
 * @param [in] delta The time since the last update.
 */
void update_world(Game_Data *game_data, double delta) {
  switch(game_data->battle_data.state % STATES) {
  case STATE_MENU:
    break;
  case STATE_BATTLE:
    if((game_data->battle_data.keys & KEY_CAM_LEFT) != 0) {
      game_data->battle_data.camera_vel.x = -CAM_SPEED;
      game_data->battle_data.camera_pos.x -= CAM_SPEED * delta;
    } else if((game_data->battle_data.keys & KEY_CAM_RIGHT) != 0) {
      game_data->battle_data.camera_vel.x = CAM_SPEED;
      game_data->battle_data.camera_pos.x += CAM_SPEED * delta;
    } else {
      game_data->battle_data.camera_vel.x = 0.0;
    }

    if((game_data->battle_data.keys & KEY_CAM_UP) != 0) {
      game_data->battle_data.camera_vel.y = -CAM_SPEED;
      game_data->battle_data.camera_pos.y -= CAM_SPEED * delta;
    } else if((game_data->battle_data.keys & KEY_CAM_DOWN) != 0) {
      game_data->battle_data.camera_vel.y = CAM_SPEED;
      game_data->battle_data.camera_pos.y += CAM_SPEED * delta;
    } else {
      game_data->battle_data.camera_vel.y = 0.0;
    }

    for(uint16_t i = 0; i < game_data->battle_data.rows *
          game_data->battle_data.cols; i++) {
      battle_entity_update(game_data->battle_data.board[i], game_data, delta);
    }
    break;
  case STATE_EXPLORE:
    break;
  case GAME_STOPPED:
    break;
  default:
    ERROR("Invalid state.");
  }
}
