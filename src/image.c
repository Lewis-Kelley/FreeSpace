#include "image.h"

/**
 * Draws the given Image to the screen using rend.
 *
 * @param [in] img The Image struct to be drawn.
 * @param [in] rend The SDL_Renderer to be used to draw the image.
 */
void image_draw(Image *img, SDL_Renderer *rend) {
  if(ABS(img->src_w) < ROUNDOFF  || ABS(img->src_h) < ROUNDOFF) {
    if(img->dest_w == 0 || img->dest_h == 0) {
      SDL_RenderCopy(rend, img->tex, NULL, NULL);
    } else {
      SDL_Rect dest;
      dest.x = img->dest_x;
      dest.y = img->dest_y;
      dest.w = img->dest_w;
      dest.h = img->dest_h;

      SDL_RenderCopy(rend, img->tex, NULL, &dest);
    }
  } else {
    if(img->dest_w == 0 || img->dest_h == 0) {
      SDL_Rect src;
      src.x = img->src_x;
      src.y = img->src_y;
      src.w = img->src_w;
      src.h = img->src_h;

      SDL_RenderCopy(rend, img->tex, &src, NULL);
    } else {
      SDL_Rect src;
      src.x = img->src_x;
      src.y = img->src_y;
      src.w = img->src_w;
      src.h = img->src_h;

      SDL_Rect dest;
      dest.x = img->dest_x;
      dest.y = img->dest_y;
      dest.w = img->dest_w;
      dest.h = img->dest_h;

      SDL_RenderCopy(rend, img->tex, &src, &dest);
    }
  }
}
