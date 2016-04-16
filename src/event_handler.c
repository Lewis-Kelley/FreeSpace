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
    if(event->key.repeat == 0) {
      key_down(event->key.keysym.sym, game_data);
    }
		break;
	case SDL_KEYUP :
    key_up(event->key.keysym.sym, game_data);
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
	case SDL_QUIT:
    on_quit(game_data);
		break;
  case SDL_WINDOWEVENT:
    //EMPTY
    break;
  case SDL_TEXTINPUT:
    //EMPTY
    break;
	case SDL_SYSWMEVENT:
    //EMPTY
		break;
  default:
    ERROR("Unhandled event");
    printf("Event is %d.\n", event->type);
    break;
	}
}

/**
 * Handles a released key event.
 *
 * @param [in] keycode The key that has been released.
 * @param [in, out] game_data The current state of the game.
 */
void key_up(SDL_Keycode keycode, Game_Data *game_data) {
  switch(keycode) {
  case SDLK_UP:
    game_data->battle_data.keys &= ~KEY_MOVE_UP;
    break;
  case SDLK_DOWN:
    game_data->battle_data.keys &= ~KEY_MOVE_DOWN;
    break;
  case SDLK_LEFT:
    game_data->battle_data.keys &= ~KEY_MOVE_LEFT;
    break;
  case SDLK_RIGHT:
    game_data->battle_data.keys &= ~KEY_MOVE_RIGHT;
    break;
  case SDLK_w:
    game_data->battle_data.keys &= ~KEY_CAM_UP;
    break;
  case SDLK_r:
    game_data->battle_data.keys &= ~KEY_CAM_DOWN;
    break;
  case SDLK_a:
    game_data->battle_data.keys &= ~KEY_CAM_LEFT;
    break;
  case SDLK_s:
    game_data->battle_data.keys &= ~KEY_CAM_RIGHT;
    break;
  }
}

/**
 * Event handles a key press.
 *
 * @param [in] keycode An SDL_Keycode instance which represents which key
 * was pressed.
 * @param [in, out] game_data The current state of the game.
 */
void key_down(SDL_Keycode keycode, Game_Data *game_data) {
  switch(keycode) {
  case SDLK_UP:
    game_data->battle_data.keys |= KEY_MOVE_UP;
    game_data->battle_data.keys &=
      ~(KEY_MOVE_DOWN | KEY_MOVE_LEFT | KEY_MOVE_RIGHT);
    break;
  case SDLK_DOWN:
    game_data->battle_data.keys |= KEY_MOVE_DOWN;
    game_data->battle_data.keys &=
      ~(KEY_MOVE_UP | KEY_MOVE_LEFT | KEY_MOVE_RIGHT);
    break;
  case SDLK_LEFT:
    game_data->battle_data.keys |= KEY_MOVE_LEFT;
    game_data->battle_data.keys &=
      ~(KEY_MOVE_DOWN | KEY_MOVE_UP | KEY_MOVE_RIGHT);
    break;
  case SDLK_RIGHT:
    game_data->battle_data.keys |= KEY_MOVE_RIGHT;
    game_data->battle_data.keys &=
      ~(KEY_MOVE_DOWN | KEY_MOVE_LEFT | KEY_MOVE_UP);
    break;
  case SDLK_SPACE:
    game_data->battle_data.turn_order[game_data->battle_data.turn]->team
      = TEAM_PLAYER;
    game_data->battle_data.turn = (game_data->battle_data.turn + 1)
      % game_data->battle_data.num_units;
    game_data->battle_data.turn_order[game_data->battle_data.turn]->team
      = TEAM_SELECTED;
    break;
  case SDLK_q:
    on_quit(game_data);
    break;
  case SDLK_w:
    game_data->battle_data.keys |= KEY_CAM_UP;
    game_data->battle_data.keys &=
      ~(KEY_CAM_DOWN | KEY_CAM_LEFT | KEY_CAM_RIGHT);
    break;
  case SDLK_r:
    game_data->battle_data.keys |= KEY_CAM_DOWN;
    game_data->battle_data.keys &=
      ~(KEY_CAM_UP | KEY_CAM_LEFT | KEY_CAM_RIGHT);
    break;
  case SDLK_a:
    game_data->battle_data.keys |= KEY_CAM_LEFT;
    game_data->battle_data.keys &=
      ~(KEY_CAM_DOWN | KEY_CAM_UP | KEY_CAM_RIGHT);
    break;
  case SDLK_s:
    game_data->battle_data.keys |= KEY_CAM_RIGHT;
    game_data->battle_data.keys &=
      ~(KEY_CAM_DOWN | KEY_CAM_LEFT | KEY_CAM_UP);
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
