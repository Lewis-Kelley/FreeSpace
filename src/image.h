/** @file
 */
#ifndef IMAGE_H
#define IMAGE_H

#include <SDL2/SDL.h>
#include <stdint.h>

#define ROUNDOFF 0.001 ///< Roundoff to be used when testing for equal doubles.

/**
 * Convinience macro to return the absolute value of an expression.
 */
#define ABS(exp)                                \
  ((exp) < 0 ? -(exp) : (exp))

/** @struct Image
 * Holds the details on how to draw a surface, including its draw coordinates.
 */
typedef struct {
  SDL_Texture *tex; ///< The SDL_Texture that actually holds the image.
  double dest_x; ///< The x coordinate to draw this Image at.
  double dest_y; ///< The y coordinate to draw this Image at.
  double dest_w; ///< The width of the image when drawn.
  double dest_h; ///< The height of the image when drawn.
  double src_x; ///< The x coordinate to read the image from.
  double src_y; ///< The y coordinate to read the image from.
  double src_w; ///< The width of the image to read, 0 means use whole image.
  double src_h; ///< The width of the image to read. 0 means use whole image.
} Image;

extern void image_draw(Image *img, SDL_Renderer *rend);

#endif
