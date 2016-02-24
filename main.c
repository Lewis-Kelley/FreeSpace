#include "main.h"

/**
 * Initilizes all the surfaces used in this program.
 *
 * @param [out] surf_disp The background SDL_Surface.
 * @param [out] surf_player The surface containing the image of the player's ship.
 * @return Status code indicating how the function terminated.
 * 0 indicates success and -1 indicates a fail.
 */
uint8_t surfs_init(SDL_Surface **surf_disp, SDL_Surface **surf_player) {
    char file[STR_LEN];
    memset(file, '\0', sizeof(file));
    
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        ERROR(SDL_INIT_EVERYTHING);
        return -1;
    }

    if((*surf_disp = SDL_SetVideoMode(WIN_WIDTH, WIN_HEIGHT, 32, SDL_HWSURFACE | SDL_DOUBLEBUF)) == NULL) {
        ERROR(Cannot initialize surf_disp.);
        return -1;
    }

#define INIT_SURF(surf)                                               \
    strcat(file, #surf);                                              \
    strcat(file, ".bmp");                                             \
    if((*surf = load_img(file)) == NULL) {                            \
        ERROR(Could not load #surf on init.);                         \
        return -1;                                                    \
    }                                                                 \
    set_invis_color(*surf, 255, 0, 255);                              \
    memset(file, '\0', sizeof(file));

    INIT_SURF(surf_player);

#undef INIT_SURF

    return 0;
}

/**
 * Renders all of the surfaces onto the display surface.
 *
 * @param [in, out] surf_disp The background SDL_Surface.
 * @param [in] surf_player The surface containing the image of the player's ship.
 * @param [in] state The current state of the game.
 */
void render(SDL_Surface *surf_disp, SDL_Surface *surf_player, Game_State state) {
    draw_surf(surf_disp, surf_player, 100, 100);

    SDL_Flip(surf_disp);
}

/**
 * Starting point for the program.
 */
int main() {
    Game_State state;
    state.running = 1;
    state.turn = 0;
    for(int i = 0; i < GRID_ROWS; i++)
        for(int j = 0; j < GRID_COLS; j++)
            state.board[i][j] = CELL_EMPTY;

    SDL_Surface *surf_disp = NULL,
        *surf_player = NULL;

    SDL_Event event;

    surfs_init(&surf_disp, &surf_player);

    SDL_Flip(surf_disp);

    while(state.running == 1) {
        while(SDL_PollEvent(&event))
            handle_event(&event, &state);

        render(surf_disp, surf_player, state);
    }

    SDL_FreeSurface(surf_disp);
    SDL_FreeSurface(surf_player);
    SDL_Quit();

    return 0;
}
