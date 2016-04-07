/** @file
 * Contains functions pertaining to handling different input events.
 */

#include "event_handler.h"

/**
 * Takes a generic event and decides what handler function to call with it.
 *
 * @param [in] event The generic event to be handled.
 * @param [in, out] game_data The state of the game.
 */
void handle_event(SDL_Event *event, Game_Data *game_data) {
	switch(event->type) {
	case SDL_KEYDOWN:
    key_down(event->key.keysym.sym, game_data);
		break;
	case SDL_KEYUP :
    key_up(event->key.keysym.sym, game_data);
		//EMPTY
		break;
	case SDL_MOUSEMOTION:
		//EMPTY
		break;
	case SDL_MOUSEBUTTONDOWN:
		switch(event->button.button) {
		case SDL_BUTTON_LEFT:
      //EMPTY
			break;
		case SDL_BUTTON_RIGHT:
			//EMPTY
			break;
		case SDL_BUTTON_MIDDLE:
			//EMPTY
			break;
		}
		break;
	case SDL_MOUSEBUTTONUP:
		switch(event->button.button) {
		case SDL_BUTTON_LEFT:
      //EMPTY
			break;
		case SDL_BUTTON_RIGHT:
			//EMPTY
			break;
		case SDL_BUTTON_MIDDLE:
			//EMPTY
			break;
		}
		break;
	case SDL_JOYAXISMOTION:
		//EMPTY
		break;
	case SDL_JOYBALLMOTION:
		//EMPTY
		break;
	case SDL_JOYHATMOTION:
		//EMPTY
		break;
	case SDL_JOYBUTTONDOWN:
		//EMPTY
		break;
	case SDL_JOYBUTTONUP:
		//EMPTY
		break;
	case SDL_QUIT:
    on_quit(game_data);
		break;
	case SDL_SYSWMEVENT:
		break;
	}
}

/**
 * Attempts to set the velocity of the entity at the origin coordinates 
 * so as to reach the destination. If the move is illegal, does not move
 * the entity and returns an error enum.
 *
 * @param [in] origin The coordinates of the entity to move.
 * @param [in] dest The coordinates of where to move the entity to.
 * @param [in, out] game_data The current state of the game.
 * @return An enum signifying the status of the move operation.
 */
Move_Status move_entity(Coord_i origin, Coord_i dest, Game_Data* game_data) {
  if(game_data->battle_data.state % 3 == 1) { // In a battle state
    if(dest.x >= game_data->battle_data.cols ||
       dest.y >= game_data->battle_data.rows) {
      return MOVE_OUT_OF_BOUNDS;
    }

    Battle_Entity *orig_ent = game_data->battle_data.board[origin.y *
                                                           game_data->battle_data.cols
                                                           + origin.x];
    if(orig_ent->team == TEAM_EMPTY) {
      return MOVE_EMPTY_ORIGIN;
    }

    if(orig_ent->vel.x != 0.0 || orig_ent->vel.y != 0.0) {
      return MOVE_ONGOING;
    }

    Battle_Entity *dest_ent = game_data->battle_data.board[dest.y *
                                                           game_data->battle_data
                                                           .cols + dest.x];
    if(dest_ent->team == TEAM_EMPTY) {
      stack_put(&orig_ent->move_queue, NULL, &dest, sizeof(Coord_i));
      orig_ent->vel.x = (dest.x - origin.x) / MOVE_TIME;
      orig_ent->vel.y = (dest.y - origin.y) / MOVE_TIME;

      game_data->battle_data.board[dest.y * game_data->battle_data.cols
                                   + dest.x] = orig_ent;
      game_data->battle_data.board[origin.y * game_data->battle_data.cols
                                   + origin.x] = dest_ent;
      
      return MOVE_SUCCESS;
    } else if(dest_ent->team == orig_ent->team) {
      return MOVE_OCCUPIED;
    } else {
      return MOVE_OBSTRUCTED;
    }
  } else { // In an explore state
    if(dest.x >= game_data->explore_data.cols ||
       dest.y >= game_data->explore_data.rows) {
      return MOVE_OUT_OF_BOUNDS;
    }

    Explore_Entity *orig_ent = game_data->explore_data.board[origin.y *
                                                             game_data->battle_data.cols
                                                             + origin.x];
    if(orig_ent->team == TEAM_EMPTY) {
      return MOVE_EMPTY_ORIGIN;
    }

    Explore_Entity *dest_ent = game_data->explore_data.board[dest.y *
                                                             game_data->battle_data
                                                             .cols + dest.x];
    if(dest_ent->team == TEAM_EMPTY) {
      orig_ent->img.dest_x = dest.x * WIN_WIDTH / game_data->explore_data.cols;
      orig_ent->img.dest_y = dest.y * WIN_HEIGHT / game_data->explore_data.rows;
      orig_ent->pos = dest;

      game_data->explore_data.board[dest.y * game_data->explore_data.cols
                                    + dest.x] = orig_ent;
      game_data->explore_data.board[origin.y * game_data->explore_data.cols
                                    + origin.x] = dest_ent;
      
      return MOVE_SUCCESS;
    } else if(dest_ent->team == orig_ent->team) {
      return MOVE_OCCUPIED;
    } else {
      return MOVE_OBSTRUCTED;
    }
  }
}

/**
 * Handles a released key event.
 *
 * @param [in] keycode The key that has been released.
 * @param [in, out] game_data The current state of the game.
 */
void key_up(SDL_Keycode keycode, Game_Data *game_data) {

}

/**
 * Event handles a key press.
 *
 * @param [in] keycode An SDL_Keycode instance which represents which key was pressed.
 * @param [in, out] game_data The current state of the game.
 */
void key_down(SDL_Keycode keycode, Game_Data *game_data) {
  Battle_Entity *ent = game_data->battle_data.turn_order[game_data->
                                                         battle_data.turn];
  switch(keycode) {
  case SDLK_UP:
    move_entity((Coord_i){ent->pos.x, ent->pos.y},
                (Coord_i){ent->pos.x, ent->pos.y - 1}, game_data);
    break;
  case SDLK_DOWN:
    move_entity((Coord_i){ent->pos.x, ent->pos.y},
                (Coord_i){ent->pos.x, ent->pos.y + 1}, game_data);
    break;
  case SDLK_LEFT:
    move_entity((Coord_i){ent->pos.x, ent->pos.y},
                (Coord_i){ent->pos.x - 1, ent->pos.y}, game_data);
    break;
  case SDLK_RIGHT:
    move_entity((Coord_i){ent->pos.x, ent->pos.y},
                (Coord_i){ent->pos.x + 1, ent->pos.y}, game_data);
    break;
  case SDLK_SPACE:
    game_data->battle_data.turn = (game_data->battle_data.turn + 1)
      % game_data->battle_data.num_units;
    break;
  case SDLK_q:
    on_quit(game_data);
    break;
  case SDLK_w:
    game_data->battle_data.camera_vel.y = 10;
    break;
  case SDLK_r:
    game_data->battle_data.camera_vel.y = -10;
    break;
  case SDLK_a:
    game_data->battle_data.camera_vel.x = 10;
    break;
  case SDLK_s:
    game_data->battle_data.camera_vel.x = -10;
    break;
  default:
    break;
  }
}

/**
 * Handles what happens on a quit event.
 * At this point, it only sets running to GAME_STOPPED.
 *
 * @param [in, out] game_data The state of the game.
 */
void on_quit(Game_Data *game_data) {
  game_data->battle_data.state = GAME_STOPPED;
}
