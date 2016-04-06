/** @file
 * Various functions for handling SDL_Surface's.
 */
#include "surface.h"

/**
 * Loads the image from a file and returns it as an SDL_Surface.
 *
 * @param [in] file The name of the file to be loaded.
 * @return A new SDL_Surface of the image in the loaded file.
 */
SDL_Surface * load_img(char *file) {
    SDL_Surface *surf_temp = NULL;
    SDL_Surface *surf_return = NULL;

    if((surf_temp = SDL_LoadBMP(file)) == NULL)
        return NULL;

    return surf_return;
}

/**
 * Draws the src surface onto the dest surface at the given coordinates.
 *
 * @param [in, out] surf_dest The surface that will be drawn on.
 * @param [in] surf_src The surface that will be drawn.
 * @param [in] dest_x The x coordinate to draw surf_src at.
 * @param [in] dest_y The y coordinate to draw surf_src at.
 * @return Status code indicating how the function terminated.
 * 0 indicates success and -1 indicates a null pointer.
 */
uint8_t draw_surf(SDL_Surface *surf_dest, SDL_Surface *surf_src,
                  uint16_t dest_x, uint16_t dest_y) {
    if(surf_dest == NULL || surf_src == NULL)
        return -1;

    SDL_Rect dest_rect;

    dest_rect.x = dest_x;
    dest_rect.y = dest_y;

    SDL_BlitSurface(surf_src, NULL, surf_dest, &dest_rect);

    return 0;
}


/**
 * Draws the portion of the src surface indicated by a rectangular bounds
 * onto the dest surface at the given coordinates.
 *
 * @param [in, out] surf_dest The surface that will be drawn on.
 * @param [in] surf_src The surface that will be drawn.
 * @param [in] dest_x The x coordinate to draw surf_src at.
 * @param [in] dest_y The y coordinate to draw surf_src at.
 * @param [in] src_x The x coordinate of the upper left corner of the selected portion of the src surface.
 * @param [in] src_y The y coordinate of the upper left corner of the selected portion of the src surface.
 * @param [in] src_w The width of the selected portion of the src surface.
 * @param [in] src_h The height of the selected portion of the src surface.
 * @return Status code indicating how the function terminated.
 * 0 indicates success and -1 indicates a null pointer.
 */
uint8_t draw_surf_region(SDL_Surface *surf_dest, SDL_Surface *surf_src,
                         uint16_t dest_x, uint16_t dest_y,
                         uint16_t src_x, uint16_t src_y, uint16_t src_w, uint16_t src_h) {
    if(surf_dest == NULL || surf_src == NULL)
        return -1;

    SDL_Rect dest_rect;

    dest_rect.x = dest_x;
    dest_rect.y = dest_y;

    SDL_Rect src_rect;

    src_rect.x = src_x;
    src_rect.y = src_y;
    src_rect.w = src_w;
    src_rect.h = src_h;

    SDL_BlitSurface(surf_src, &src_rect, surf_dest, &dest_rect);

    return 0;
}

/**
 * Sets what color in the image file to treat as invisible.
 *
 * @param [in, out] surf The SDL_Surface that will be configured.
 * @param [in] r The red component of the surface.
 * @param [in] b The blue component of the surface.
 * @param [in] g The green component of the surface.
 * @return Status code indicating how the function terminated.
 * 0 indicates success and -1 indicates a null pointer.
 */
/* uint8_t set_invis_color(SDL_Surface *surf, uint8_t r, uint8_t g, uint8_t b) { */
/*     if(surf == NULL) */
/*         return -1; */

/*     SDL_SetColorKey(surf, SDL_SRCCOLORKEY | SDL_RLEACCEL, SDL_MapRGB(surf->format, r, g, b)); */

/*     return 0; */
/* } */
