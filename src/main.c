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
    ERROR("Could not load surface on init.");   \
    return -1;                                  \
  }                                             \
  set_invis_color(*surf, 255, 0, 255);          \
  memset(file, '\0', sizeof(file));

/**
 * Initializes all the various SDL structures used to draw on the screen.
 *
 * @param [out] win The window that will be drawn on.
 * @param [out] rend The SDL_Renderer to be created.
 * @param [out] tex_player An SDL_Texture containing the image of the player ship.
 */
void init(SDL_Window **win, SDL_Renderer **rend, SDL_Texture **tex_player) {
  if(SDL_Init(SDL_INIT_VIDEO) != 0) {
    ERROR("SDL_Init failed.");
    return;
  }
  
  *win = SDL_CreateWindow("FreeSpace", 100, 100, WIN_WIDTH, WIN_HEIGHT,
                          SDL_WINDOW_SHOWN);
  if(*win == NULL) {
    ERROR("Failed to create window.");
    return;
  }

  *rend = SDL_CreateRenderer(*win, -1, SDL_RENDERER_ACCELERATED |
                             SDL_RENDERER_PRESENTVSYNC);
  if(*rend == NULL) {
    SDL_DestroyWindow(*win);
    ERROR("Failed to create renderer.");
    SDL_Quit();
    return;
  }

  SDL_Surface *bmp = SDL_LoadBMP("assets/surf_player.bmp");
  if(bmp == NULL) {
    SDL_DestroyRenderer(*rend);
    SDL_DestroyWindow(*win);
    ERROR("Failed to load surf_player.bmp.");
    SDL_Quit();
    return;
  }
  SDL_SetColorKey(bmp, SDL_TRUE, SDL_MapRGB(bmp->format, 0xFF, 0, 0xFF));

  *tex_player = SDL_CreateTextureFromSurface(*rend, bmp);
  SDL_FreeSurface(bmp);
  if(*tex_player == NULL) {
    SDL_DestroyRenderer(*rend);
    SDL_DestroyWindow(*win);
    ERROR("Failed to create tex_player.");
    SDL_Quit();
    return;
  }
}

/**
 * Checks the time delta and updates the game state accordingly.
 *
 * @param [in, out] game_data The current state of the game.
 */
void update(Game_Data *game_data) {
  Battle_Entity *temp;
  switch(game_data->battle_data.state % STATES) {
  case STATE_MENU:
    break;
  case STATE_BATTLE:
    for(uint16_t i = 0; i < game_data->battle_data.rows *
          game_data->battle_data.cols; i++) {
      temp = game_data->battle_data.board[i];

      if(temp->team != TEAM_EMPTY) {
        temp->pos.x += temp->vel.x;
        temp->pos.y += temp->vel.y;

        if(temp->move_queue.head != NULL) {
          if(temp->vel.x != 0.0 &&
             ABS(temp->pos.x -
                 ((Coord_i *)temp->move_queue.head->data)->x) < ROUNDOFF) {

            temp->pos.x = ((Coord_i *)temp->move_queue.head->data)->x;
            temp->vel = (Coord_f){0.0, 0.0};

            stack_remove(&temp->move_queue, NULL);
          } else if(temp->vel.y != 0.0 &&
             ABS(temp->pos.y - ((Coord_i *)temp->move_queue.head->data)->y)
             < ROUNDOFF) {

            temp->pos.y = ((Coord_i *)temp->move_queue.head->data)->y;
            temp->vel = (Coord_f){0.0, 0.0};

            stack_remove(&temp->move_queue, NULL);
          }
        }
      }
    }
    break;
  case STATE_EXPLORE:
    break;
  default:
    ERROR("Invalid state.");
  }
}

/**
 * Renders all of the surfaces onto the display surface.
 *
 * @param [in, out] rend The renderer for the window.
 * @param [in] game_data The current state of the game.
 */
void render(SDL_Renderer *rend, Game_Data *game_data) {
  SDL_Rect dest;
  for(int i = 0; i < GRID_COLS * GRID_ROWS; i++) {
    if(game_data->battle_data.board[i]->team != TEAM_EMPTY) {
      dest.w = WIN_WIDTH / game_data->battle_data.cols;
      dest.h = WIN_HEIGHT / game_data->battle_data.rows;
      dest.x = game_data->battle_data.board[i]->pos.x * dest.w +
        game_data->battle_data.camera.x;
      dest.y = game_data->battle_data.board[i]->pos.y * dest.h +
        game_data->battle_data.camera.y;

      SDL_RenderCopy(rend, game_data->battle_data.board[i]->img.tex,
                     NULL, &dest);
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

  init(&win, &rend, &tex_player);

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
        = (Battle_Entity){(Image){NULL, i * WIN_WIDTH / GRID_COLS,
                                  j * WIN_HEIGHT / GRID_ROWS, 0, 0, 0, 0},
                          TEAM_EMPTY, (Coord_f){i, j}, (Coord_f){0, 0},
                          (Stack){NULL, 0}};
    }

  SDL_Event event;

  game_data.battle_data.board[10 * GRID_ROWS + 5]->img.tex = tex_player;
  game_data.battle_data.board[10 * GRID_ROWS + 5]->team = TEAM_PLAYER;
  game_data.battle_data.turn_order[0]
    = game_data.battle_data.board[10 * GRID_ROWS + 5];

  game_data.battle_data.board[19 * GRID_ROWS + 19]->img.tex = tex_player;
  game_data.battle_data.board[19 * GRID_ROWS + 19]->team = TEAM_PLAYER;
  game_data.battle_data.turn_order[1]
    = game_data.battle_data.board[19 * GRID_ROWS + 19];

  while(game_data.battle_data.state != GAME_STOPPED) {
    SDL_RenderClear(rend);
    while(SDL_PollEvent(&event))
      handle_event(&event, &game_data);

    update(&game_data);
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
