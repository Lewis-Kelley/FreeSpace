#ifndef IMAGE_UPDATE_H
#define IMAGE_UPDATE_H

#include "game_state.h"

void _image_pos (Image *img, double dx, double dy,
                        double cam_x, double cam_y,
                        uint16_t cols, uint16_t rows,
                        uint16_t win_width, uint16_t win_height);

void battle_image_move (Image *img, double x, double y,
                        Battle_Data *battle_data);

void explore_image_move (Image *img, double x, double y,
                         Explore_Data *exp_data);

#endif
