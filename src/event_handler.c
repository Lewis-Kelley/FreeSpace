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
	case SDL_ACTIVEEVENT:
		switch(event->active.state) {
		case SDL_APPMOUSEFOCUS:
			if(event->active.gain) {
				//EMPTY
			} else {
        //EMPTY
			}
			break;
		case SDL_APPINPUTFOCUS:
			if(event->active.gain) {
        //EMPTY
			} else {
        //EMPTY
			}
			break;
		case SDL_APPACTIVE:
			if(event->active.gain) {
				//EMPTY
			} else {
				//EMPTY
			}
			break;
		}
		break;
	case SDL_KEYDOWN:
    key_down(event->key.keysym, game_data);
		break;
	case SDL_KEYUP :
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
	case SDL_VIDEORESIZE:
    //EMPTY
		break;
	case SDL_VIDEOEXPOSE:
		//EMPTY
		break;
	}
}

/**
 * Event handles a key press.
 *
 * @param keysym An SDL_keysym instance which represents which key was pressed.
 * @param game_data The current state of the game.
 */
void key_down(SDL_keysym keysym, Game_Data *game_data) {
  switch(keysym.sym) {
  case SDLK_UP:
    break;
  case SDLK_DOWN:
    break;
  case SDLK_LEFT:
    break;
  case SDLK_RIGHT:
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
