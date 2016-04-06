/** @file
 */
#ifndef IMAGE_H
#define IMAGE_H

#include <SDL2/SDL.h>
#include <stdint.h>

/** @struct Image
 * Holds the details on how to draw a surface, including its draw coordinates.
 */
typedef struct {
    SDL_Texture *tex; ///< The SDL_Texture that actually holds the image.
    uint16_t dest_x; ///< The x coordinate to draw this Image at.
    uint16_t dest_y; ///< The y coordinate to draw this Image at.
    uint16_t src_x; ///< The x coordinate to read the image from.
    uint16_t src_y; ///< The y coordinate to read the image from.
    uint16_t w; ///< The width of the image to read, 0 means use whole image.
    uint16_t h; ///< The width of the image to read. 0 means use whole image.
} Image;

#endif
