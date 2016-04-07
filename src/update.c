#include "update.h"

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
      ent->img.dest_x += game_data->battle_data.camera_vel.x
        * game_data->battle_data.delta;
    }

    if(game_data->battle_data.camera_vel.y != 0.0) {
      ent->img.dest_y += game_data->battle_data.camera_vel.y
        * game_data->battle_data.delta;
    }

    if(ent->move_queue.head != NULL) {
      if(ent->vel.x != 0.0) {
        ent->pos.x += ent->vel.x * game_data->battle_data.delta;

        if(ABS(ent->pos.x -
               ((Coord_i *)ent->move_queue.head->data)->x) < ROUNDOFF
           || (ent->vel.x > 0.0 && ent->pos.x >
               ((Coord_i *)ent->move_queue.head->data)->x)
           || (ent->vel.x < 0.0 && ent->pos.x <
               ((Coord_i *)ent->move_queue.head->data)->x)) {

          ent->pos.x = ((Coord_i *)ent->move_queue.head->data)->x;
          ent->img.dest_x = ent->pos.x * ent->img.dest_w
            + game_data->battle_data.camera_pos.x;
          ent->vel = (Coord_f){0.0, 0.0};

          stack_remove(&ent->move_queue, NULL);
        } else {
          ent->img.dest_x += ent->vel.x * ent->img.dest_w
            * game_data->battle_data.delta;
        }
      } else if(ent->vel.y != 0.0) {
        ent->pos.y += ent->vel.y * game_data->battle_data.delta;

        if(ABS(ent->pos.y -
               ((Coord_i *)ent->move_queue.head->data)->y) < ROUNDOFF
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
    }
  }
}

/**
 * Checks the time delta and updates the game state accordingly.
 *
 * @param [in, out] game_data The current state of the game.
 */
void update_world(Game_Data *game_data) {
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
