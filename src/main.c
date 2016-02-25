/**@file
 * Starting point for the program and handles overall rendering functions.
 */
#include "main.h"

/**
 * @def INIT_SURF(surf)
 * Local macro that loads the image file associated with a given surface
 * variable.
 */
#define INIT_SURF(surf)                                               \
    strcat(file, "assets/");                                          \
    strcat(file, #surf);                                              \
    strcat(file, ".bmp");                                             \
    if((*surf = load_img(file)) == NULL) {                            \
        ERROR(Could not load #surf on init.);                         \
        return -1;                                                    \
    }                                                                 \
    set_invis_color(*surf, 255, 0, 255);                              \
    memset(file, '\0', sizeof(file));

/**
 * Initilizes all the surfaces used in this program.
 *
 * @param [out] surf_disp The background SDL_Surface.
 * @param [out] surf_player The surface containing the image of the player's ship.
 * @param [out] surf_empty A completely transparent surface to represent an empty tile.
 * @return Status code indicating how the function terminated.
 * 0 indicates success and -1 indicates a fail.
 */
uint8_t surfs_init(SDL_Surface **surf_disp, SDL_Surface **surf_player, SDL_Surface **surf_empty) {
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

    INIT_SURF(surf_player);
    INIT_SURF(surf_empty);

    return 0;
}

/**
 * Renders all of the surfaces onto the display surface.
 *
 * @param [in, out] surf_disp The background SDL_Surface.
 * @param [in] state The current state of the game.
 * @param [in] num The number of Image's that are being passed in.
 * @param [in] ... Any number of Image's to be drawn on the surf_disp.
 */
void render(SDL_Surface *surf_disp, Game_State state, int num, ...) {
    va_list valist;
    va_start(valist, num);

    for(int i = 0; i < GRID_COLS; i++) {
        for(int j = 0; j < GRID_ROWS; j++) {
            if(state.board[i][j].w == 0 || state.board[i][j].h == 0)
                draw_surf(surf_disp, *state.board[i][j].surf, state.board[i][j].dest_x,
                          state.board[i][j].dest_y);
            else
                draw_surf_region(surf_disp, *state.board[i][j].surf,
                                 state.board[i][j].dest_x, state.board[i][j].dest_y,
                                 state.board[i][j].src_x, state.board[i][j].src_y,
                                 state.board[i][j].w, state.board[i][j].h);
        }
    }

    Image img;
    
    for(int i = 0; i < num; i++) {
        img = va_arg(valist, Image);
        if(img.w == 0 || img.h == 0)
            draw_surf(surf_disp, *img.surf, img.dest_x, img.dest_y);
        else
            draw_surf_region(surf_disp, *img.surf, img.dest_x, img.dest_y,
                             img.src_x, img.src_y, img.w, img.h);
    }

    va_end(valist);

    SDL_Flip(surf_disp);
}

/**
 * Starting point for the program.
 */
int main() {
    SDL_Surface *surf_disp = NULL,
        *surf_player = NULL,
        *surf_empty = NULL;

    Game_State state;
    state.running = 1;
    state.turn = 0;
    for(int i = 0; i < GRID_ROWS; i++)
        for(int j = 0; j < GRID_COLS; j++)
            state.board[i][j] = (Image){&surf_empty, i * WIN_WIDTH / GRID_COLS,
                                        j * WIN_HEIGHT / GRID_ROWS, 0, 0, 0, 0};

    SDL_Event event;

    state.board[10][22].surf = &surf_player;

    surfs_init(&surf_disp, &surf_player, &surf_empty);

    SDL_Flip(surf_disp);

    while(state.running == 1) {
        while(SDL_PollEvent(&event))
            handle_event(&event, &state);

        render(surf_disp, state, 0);
    }

    SDL_FreeSurface(surf_disp);
    SDL_FreeSurface(surf_player);
    SDL_Quit();

    return 0;
}

#undef INIT_SURF
