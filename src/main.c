/**@file
 * Starting point for the program and handles overall rendering functions.
 */
#include "main.h"

/**
 * @def INIT_SURF(surf)
 * Local macro that loads the image file associated with a given surface
 * variable.
 */
#define INIT_SURF(surf)                         \
  strcat(file, "assets/");                      \
  strcat(file, #surf);                          \
  strcat(file, ".bmp");                         \
  if((*surf = load_img(file)) == NULL) {        \
    ERROR(Could not load #surf on init.);       \
    return -1;                                  \
  }                                             \
  set_invis_color(*surf, 255, 0, 255);          \
  memset(file, '\0', sizeof(file));

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

  if((*surf_disp = SDL_SetVideoMode(WIN_WIDTH, WIN_HEIGHT, 32,
                                    SDL_HWSURFACE | SDL_DOUBLEBUF)) == NULL) {
    ERROR(Cannot initialize surf_disp.);
    return -1;
  }

  INIT_SURF(surf_player);

  return 0;
}

/**
 * Renders all of the surfaces onto the display surface.
 *
 * @param [in, out] surf_disp The background SDL_Surface.
 * @param [in] game_data The current state of the game.
 * @param [in] num The number of Image's that are being passed in.
 * @param [in] ... Any number of Image's to be drawn on the surf_disp.
 */
void render(SDL_Surface *surf_disp, Game_Data game_data, int num, ...) {
  va_list valist;
  va_start(valist, num);

  for(int i = 0; i < GRID_COLS * GRID_ROWS; i++) {
    if(game_data.battle_data.board[i]->team != TEAM_EMPTY) {
      if(game_data.battle_data.board[i]->img.w == 0 ||
         game_data.battle_data.board[i]->img.h == 0) {
        draw_surf(surf_disp,
                  *game_data.battle_data.board[i]->img.surf,
                  game_data.battle_data.board[i]->img.dest_x,
                  game_data.battle_data.board[i]->img.dest_y);
      } else {
        draw_surf_region(surf_disp,
                         *game_data.battle_data.board[i]->img.surf,
                         game_data.battle_data.board[i]->img.dest_x,
                         game_data.battle_data.board[i]->img.dest_y,
                         game_data.battle_data.board[i]->img.src_x,
                         game_data.battle_data.board[i]->img.src_y,
                         game_data.battle_data.board[i]->img.w,
                         game_data.battle_data.board[i]->img.h);
      }
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
int main(int argc, char **argv) {
  SDL_Surface *surf_disp = NULL,
    *surf_player = NULL,
    *surf_empty = NULL;

  surfs_init(&surf_disp, &surf_player);

  Game_Data game_data;

  game_data.battle_data.state = GAME_BATTLE_MOVE;
  game_data.battle_data.num_units = 2;
  game_data.battle_data.board =
    (Battle_Entity **)malloc(GRID_COLS * GRID_COLS * sizeof(Battle_Entity *));
  game_data.battle_data.turn_order =
    (Battle_Entity **)malloc(game_data.battle_data.num_units *
                             sizeof(Battle_Entity *));
  game_data.battle_data.camera = (Coord_f){0.0, 0.0};
  game_data.battle_data.cols = GRID_COLS;
  game_data.battle_data.rows = GRID_ROWS;
  game_data.battle_data.turn = 0;

  for(int i = 0; i < GRID_COLS; i++)
    for(int j = 0; j < GRID_ROWS; j++) {
      game_data.battle_data.board[j * GRID_COLS + i]
        = (Battle_Entity *)malloc(sizeof(Battle_Entity));
      *game_data.battle_data.board[j * GRID_COLS + i]
        = (Battle_Entity){(Image){&surf_empty, i * WIN_WIDTH / GRID_COLS,
                                  j * WIN_HEIGHT / GRID_ROWS, 0, 0, 0, 0},
                          TEAM_EMPTY, (Coord_i){i, j}};
    }

  SDL_Event event;

  game_data.battle_data.board[10 * GRID_ROWS + 5]->img.surf = &surf_player;
  game_data.battle_data.board[10 * GRID_ROWS + 5]->team = TEAM_PLAYER;
  game_data.battle_data.turn_order[0]
    = game_data.battle_data.board[10 * GRID_ROWS + 5];

  game_data.battle_data.board[19 * GRID_ROWS + 19]->img.surf = &surf_player;
  game_data.battle_data.board[19 * GRID_ROWS + 19]->team = TEAM_PLAYER;
  game_data.battle_data.turn_order[1]
    = game_data.battle_data.board[19 * GRID_ROWS + 19];

  SDL_Flip(surf_disp);

  while(game_data.battle_data.state != GAME_STOPPED) {
    while(SDL_PollEvent(&event))
      handle_event(&event, &game_data);

    render(surf_disp, game_data, 0);
  }

  SDL_FreeSurface(surf_disp);
  SDL_FreeSurface(surf_player);
  SDL_Quit();

  return 0;
}

#undef INIT_SURF
