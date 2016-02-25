#include "main.h"

SDL_Surface * load_img(char *file);
uint8_t draw_surf(SDL_Surface *surf_dest, SDL_Surface *surf_src,
                  uint16_t dest_x, uint16_t dest_y);
uint8_t draw_surf_region(SDL_Surface *surf_dest, SDL_Surface *surf_src,
                         uint16_t dest_x, uint16_t dest_y,
                         uint16_t src_x, uint16_t src_y, uint16_t src_w, uint16_t src_h);
uint8_t set_invis_color(SDL_Surface *surf, uint8_t r, uint8_t g, uint8_t b);
