/**@file
 * Starting point for the program and handles overall rendering functions.
 */
#include "main.h"

/**
 * Initializes all the various SDL structures used to draw on the screen.
 *
 * @param [out] win The window that will be drawn on.
 * @param [out] rend The SDL_Renderer to be created.
 * @param [out] tex_player An SDL_Texture containing the image of the player ship.
 * @return 0 if successful, 1 if error.
 */
uint8_t init(SDL_Window **win, SDL_Renderer **rend, SDL_Texture **tex_player) {
  if(SDL_Init(SDL_INIT_VIDEO) != 0) {
    ERROR("SDL_Init failed.");
    return 1;
  }
  
  *win = SDL_CreateWindow("FreeSpace", 100, 100, WIN_WIDTH, WIN_HEIGHT,
                          SDL_WINDOW_SHOWN);
  if(*win == NULL) {
    ERROR("Failed to create window.");
    return 1;
  }

  *rend = SDL_CreateRenderer(*win, -1, SDL_RENDERER_ACCELERATED |
                             SDL_RENDERER_PRESENTVSYNC);
  if(*rend == NULL) {
    SDL_DestroyWindow(*win);
    ERROR("Failed to create renderer.");
    SDL_Quit();
    return 1;
  }

  //TODO Figure out how to make this path work well
  SDL_Surface *bmp =
    SDL_LoadBMP("/home/kelleyld/programs/FreeSpace/assets/surf_player.bmp");
  if(bmp == NULL) {
    SDL_DestroyRenderer(*rend);
    SDL_DestroyWindow(*win);
    ERROR("Failed to load surf_player.bmp.");
    SDL_Quit();
    return 1;
  }
  SDL_SetColorKey(bmp, SDL_TRUE, SDL_MapRGB(bmp->format, 0xFF, 0, 0xFF));

  *tex_player = SDL_CreateTextureFromSurface(*rend, bmp);
  SDL_FreeSurface(bmp);
  if(*tex_player == NULL) {
    SDL_DestroyRenderer(*rend);
    SDL_DestroyWindow(*win);
    ERROR("Failed to create tex_player.");
    SDL_Quit();
    return 1;
  }

  return 0;
}

/**
 * Renders all of the surfaces onto the display surface.
 *
 * @param [in, out] rend The renderer for the window.
 * @param [in] game_data The current state of the game.
 */
void render(SDL_Renderer *rend, Game_Data *game_data) {
  for(int i = 0; i < GRID_COLS * GRID_ROWS; i++) {
    if(game_data->battle_data.board[i]->team != TEAM_EMPTY) {
      image_draw(&game_data->battle_data.board[i]->img, rend);
    }
  }

  SDL_RenderPresent(rend);
}

/**
 * Starting point for the program.
 *
 * @param argc The number of command line arguments.
 * @param argv The array of command line arguments.
 * @return Program exit status.
 */
int main(int argc, char **argv) {
  SDL_Window *win = NULL;
  SDL_Renderer *rend = NULL;
  SDL_Texture *tex_player = NULL;

  if(init(&win, &rend, &tex_player)) {
    return 1;
  }

  Game_Data game_data;

  game_data.battle_data.state = GAME_BATTLE_MOVE;
  game_data.battle_data.num_units = 2;
  game_data.battle_data.board =
    malloc(GRID_COLS * GRID_COLS * sizeof *game_data.battle_data.board);
  game_data.battle_data.turn_order =
    malloc(game_data.battle_data.num_units
           * sizeof *game_data.battle_data.turn_order);
  game_data.battle_data.camera_pos = (Coord_f){0.0, 0.0};
  game_data.battle_data.camera_vel = (Coord_f){0.0, 0.0};
  game_data.battle_data.cols = GRID_COLS;
  game_data.battle_data.rows = GRID_ROWS;
  game_data.battle_data.turn = 0;

  for(int i = 0; i < GRID_COLS; i++)
    for(int j = 0; j < GRID_ROWS; j++) {
      game_data.battle_data.board[j * GRID_COLS + i]
        = malloc(sizeof **game_data.battle_data.board);
      *game_data.battle_data.board[j * GRID_COLS + i]
        = (Battle_Entity){(Image){NULL, i * WIN_WIDTH / GRID_COLS,
                                  j * WIN_HEIGHT / GRID_ROWS,
                                  WIN_WIDTH /GRID_COLS, WIN_HEIGHT / GRID_ROWS,
                                  0, 0, 0, 0},
                          TEAM_EMPTY, (Coord_f){i, j}, (Coord_f){0, 0},
                          (Stack){NULL, 0}};
    }

  SDL_Event event;

  game_data.battle_data.board[10 * GRID_ROWS + 5]->img.tex = tex_player;
  game_data.battle_data.board[10 * GRID_ROWS + 5]->team = TEAM_SELECTED;
  game_data.battle_data.turn_order[0]
    = game_data.battle_data.board[10 * GRID_ROWS + 5];

  game_data.battle_data.board[19 * GRID_ROWS + 19]->img.tex = tex_player;
  game_data.battle_data.board[19 * GRID_ROWS + 19]->team = TEAM_PLAYER;
  game_data.battle_data.turn_order[1]
    = game_data.battle_data.board[19 * GRID_ROWS + 19];

  double time = SDL_GetTicks();

  while(game_data.battle_data.state != GAME_STOPPED) {
    SDL_RenderClear(rend);
    while(SDL_PollEvent(&event))
      handle_event(&event, &game_data);

    update_world(&game_data, SDL_GetTicks() - time);
    time = SDL_GetTicks();
    render(rend, &game_data);
    SDL_RenderPresent(rend);
  }

  SDL_DestroyTexture(tex_player);
  SDL_DestroyRenderer(rend);
  SDL_DestroyWindow(win);
  SDL_Quit();

  return 0;
}

#undef INIT_SURF
