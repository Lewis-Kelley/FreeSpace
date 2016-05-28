#include "image_update.h"

/**
 * Sets the given Image's position to the place corresponding to the
 * given game position.
 *
 * @param [in, out] img The Image to be moved.
 * @param [in] x The x game position.
 * @param [in] y The y game position.
 * @param [in] cols The number of columns in the current board.
 * @param [in] rows The number of rows in the current board.
 * @param [in] win_width The width of the window in pixels.
 * @param [in] win_height The height of the window in pixels.
 */
void _image_pos (Image *img, double x, double y,
                        double cam_x, double cam_y,
                        uint16_t cols, uint16_t rows,
                        uint16_t win_width, uint16_t win_height) {
  img->dest_x = (x - cam_x) * (double)win_width / cols;
  img->dest_y = (y - cam_y) * (double)win_height / rows;
}

/**
 * Takes an Image and updates its positions given the change in game position.
 *
 * @param [in, out] img The Image that will be updated.
 * @param [in] The destination game x position.
 * @param [in] The destination game y position.
 * @param [in] battle_data The current state of the game.
 */
void battle_image_move (Image *img, double x, double y,
                        Battle_Data *battle_data) {
  _image_pos(img, x, y, battle_data->camera_pos.x, battle_data->camera_pos.y,
             battle_data->board.cols, battle_data->board.rows,
             WIN_WIDTH, WIN_HEIGHT);
}

/**
 * Takes an Image and updates its positions given the change in game position.
 *
 * @param [in, out] img The Image that will be updated.
 * @param [in] The destination game x position.
 * @param [in] The destination game y position.
 * @param [in] exp_data The current state of the game.
 */
void explore_image_move (Image *img, double x, double y,
                         Explore_Data *exp_data) {
  _image_pos(img, x, y, exp_data->camera_pos.x, exp_data->camera_pos.y,
             exp_data->board.cols, exp_data->board.rows, WIN_WIDTH, WIN_HEIGHT);
}
