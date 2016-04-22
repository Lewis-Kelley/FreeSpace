#include "update.h"

/**
 * Takes an Battle_Entity to update given that it is at a cell
 * intersection and a move key has been pressed.
 *
 * @param [in, out] ent The Battle_Entity that is being updated.
 * @param [in, out] game_data The current state of the game.
 */
void battle_entity_key_update(Battle_Entity *ent, Game_Data *game_data) {
  int dest;
  switch(game_data->battle_data.keys & KEY_MOVE) {
  case KEY_MOVE_LEFT:
  case KEY_MOVE_RIGHT:
    if(ent->vel.x != 0.0) {
      ent->pos.x = ((Coord_i *)ent->move_queue.head->data)->x
        + game_data->battle_data.camera_pos.x;

      ent->img.dest_x = ent->pos.x * (double)WIN_WIDTH /
        game_data->battle_data.cols + game_data->battle_data.camera_pos.x;      
      printf("Set img.dest_x: %f\n", ent->img.dest_x);
      printf("camera_pos.x: %f\n", game_data->battle_data.camera_pos.x);
      printf("ent->pos.x: %f\n", ent->pos.x);

      stack_remove(&ent->move_queue, NULL);
    } else if (ent->vel.y != 0.0) {
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
      //FIXME The destination and origin entities aren't being swapped.
      Battle_Entity *dest_ent = bat_ent_lookup(game_data, dest, ent->pos.y);
      dest_ent->pos.x = ent->pos.x;
      bat_ent_put_coord(game_data, bat_ent_lookup(game_data, ent->pos.x,
                                                  ent->pos.y),
                        dest, ent->pos.y);
      bat_ent_put_coord(game_data, dest_ent, ent->pos.x, ent->pos.y);
    } else {
      ent->vel.x = 0.0;
    }
    break;
  case KEY_MOVE_UP:
  case KEY_MOVE_DOWN:
    if(ent->vel.y != 0.0) {
      ent->pos.y = ((Coord_i *)ent->move_queue.head->data)->y
        + game_data->battle_data.camera_pos.y;

      ent->img.dest_y = (ent->pos.y + game_data->battle_data.camera_pos.y)
        * (double)WIN_HEIGHT / game_data->battle_data.rows;

      stack_remove(&ent->move_queue, NULL);
    } else if (ent->vel.x != 0.0) {
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
      //FIXME The destination and origin entities aren't being swapped.
      Battle_Entity *dest_ent = bat_ent_lookup(game_data, ent->pos.x, dest);
      dest_ent->pos.y = ent->pos.y;
      bat_ent_put_coord(game_data, bat_ent_lookup(game_data, ent->pos.x,
                                                  ent->pos.y),
                        ent->pos.x, dest);
      bat_ent_put_coord(game_data, dest_ent, ent->pos.x, ent->pos.y);
    } else {
      ent->vel.y = 0.0;
    }
    break;
  default:
    break;
  }
}

/**
 * Updates the various fields of ent given the amount of time passed since
 * the last tick.
 *
 * @param [in, out] ent The Battle_Entity to be updated.
 * @param [in, out] game_data The current state of the game.
 */
void battle_entity_update(Battle_Entity *ent, Game_Data *game_data) {
  if(ent->team != TEAM_EMPTY) {
    if(game_data->battle_data.camera_vel.x != 0.0) {
      ent->img.dest_x -= game_data->battle_data.camera_vel.x
        * game_data->battle_data.delta;
    }

    if(game_data->battle_data.camera_vel.y != 0.0) {
      ent->img.dest_y -= game_data->battle_data.camera_vel.y
        * game_data->battle_data.delta;
    }

    if(ent->move_queue.head != NULL) {
      if(ent->vel.x != 0.0) {
        ent->pos.x += ent->vel.x * game_data->battle_data.delta;

        if(ABS(ent->pos.x
               - ((Coord_i *)ent->move_queue.head->data)->x) < ROUNDOFF
           || (ent->vel.x > 0.0 && ent->pos.x >
               ((Coord_i *)ent->move_queue.head->data)->x)
           || (ent->vel.x < 0.0 && ent->pos.x <
               ((Coord_i *)ent->move_queue.head->data)->x)) {
          if((game_data->battle_data.keys & KEY_MOVE) != 0) {
            battle_entity_key_update(ent, game_data);
          } else {
            ent->vel.x = 0.0;
            ent->pos.x = ((Coord_i *)ent->move_queue.head->data)->x
              + game_data->battle_data.camera_pos.x;

            stack_remove(&ent->move_queue, NULL);
          }
        } else {
          ent->img.dest_x += ent->vel.x * ent->img.dest_w
            * game_data->battle_data.delta;
        }
      } else if(ent->vel.y != 0.0) {
        ent->pos.y += ent->vel.y * game_data->battle_data.delta;

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
          ent->img.dest_y += ent->vel.y * ent->img.dest_h
            * game_data->battle_data.delta;
        }
      }
    } else if(ent->team == TEAM_SELECTED
              && (game_data->battle_data.keys & KEY_MOVE) != 0) {
      battle_entity_key_update(ent, game_data);
    }
  }
}

  /**
   * Checks the time delta and updates the game state accordingly.
   *
   * @param [in, out] game_data The current state of the game.
   */
  void update_world(Game_Data *game_data) {
    printf("camera_pos: (%3f, %3f)\n", game_data->battle_data.camera_pos.x,
           game_data->battle_data.camera_pos.y);
    double time = SDL_GetTicks();
    switch(game_data->battle_data.state % STATES) {
    case STATE_MENU:
      break;
    case STATE_BATTLE:
      game_data->battle_data.delta = time - game_data->battle_data.last_time;
      game_data->battle_data.last_time = time;

      if((game_data->battle_data.keys & KEY_CAM_LEFT) != 0) {
        game_data->battle_data.camera_vel.x = -CAM_SPEED;
        game_data->battle_data.camera_pos.x -= CAM_SPEED
          * game_data->battle_data.delta;
      } else if((game_data->battle_data.keys & KEY_CAM_RIGHT) != 0) {
        game_data->battle_data.camera_vel.x = CAM_SPEED;
        game_data->battle_data.camera_pos.x += CAM_SPEED
          * game_data->battle_data.delta;
      } else {
        game_data->battle_data.camera_vel.x = 0.0;
      }

      if((game_data->battle_data.keys & KEY_CAM_UP) != 0) {
        game_data->battle_data.camera_vel.y = -CAM_SPEED;
        game_data->battle_data.camera_pos.x -= CAM_SPEED
          * game_data->battle_data.delta;
      } else if((game_data->battle_data.keys & KEY_CAM_DOWN) != 0) {
        game_data->battle_data.camera_vel.y = CAM_SPEED;
        game_data->battle_data.camera_pos.x += CAM_SPEED
          * game_data->battle_data.delta;
      } else {
        game_data->battle_data.camera_vel.y = 0.0;
      }

      for(uint16_t i = 0; i < game_data->battle_data.rows *
            game_data->battle_data.cols; i++) {
        battle_entity_update(game_data->battle_data.board[i], game_data);
      }
      break;
    case STATE_EXPLORE:
      break;
    default:
      ERROR("Invalid state.");
    }
  }
