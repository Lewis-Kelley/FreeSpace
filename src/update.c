#include "update.h"

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

    battle_image_move(&ent->img, ent->pos.x, ent->pos.y, battle_data);
    
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
 * @param [in, out] battle_data The current state of the game.
 * @param [in] delta The time since the last tick.
 */
void battle_entity_update(Battle_Entity *ent, Battle_Data *battle_data,
                          double delta) {
  if(ent->team != TEAM_EMPTY) {
    if(battle_data->camera_vel.x != 0.0
       || battle_data->camera_vel.y != 0.0) {
      battle_image_move(&ent->img, ent->pos.x, ent->pos.y, battle_data);
    }

    if(ent->move_queue.head != NULL) {
      double *vel = NULL;
      double *pos = NULL;
      int dest;
      
      if(ent->vel.x != 0.0) {
        vel = &ent->vel.x;
        pos = &ent->pos.x;
        dest = ((Coord_i *)ent->move_queue.head->data)->x;
      } else if(ent->vel.y != 0.0) {
        vel = &ent->vel.y;
        pos = &ent->pos.y;
        dest = ((Coord_i *)ent->move_queue.head->data)->y;
      }

      if(pos != NULL) {
        *pos += *vel * delta;

        if(ABS(*pos - dest) < ROUNDOFF || (*vel > 0.0 && *pos > dest)
           || (*vel < 0.0 && *pos < dest)) {
          *vel = 0.0;
          *pos = dest;
        
          stack_remove(&ent->move_queue, NULL);
        }

        battle_image_move(&ent->img, ent->pos.x, ent->pos.y, battle_data);
      }
    } else if(ent->team == TEAM_SELECTED
              && (battle_data->keys & KEY_MOVE) != 0) {
      battle_entity_key_update(ent, battle_data);
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
      battle_entity_update(game_data->battle_data.board[i],
                           &game_data->battle_data, delta);
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
