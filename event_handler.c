/** @file
 * Contains functions pertaining to handling different input events.
 */

#include "event_handler.h"

/**
 * Takes a generic event and decides what handler function to call with it.
 *
 * @param [in] event The generic event to be handled.
 * @param [in, out] state The state of the game.
 */
void handle_event(SDL_Event *event, Game_State *state) {
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
		//EMPTY
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
        on_quit(state);
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
 * Handles what happens on a quit event.
 * At this point, it only sets running to 0.
 *
 * @param [in, out] state The state of the game.
 */
void on_quit(Game_State *state) {
    state->running = 0;
}
