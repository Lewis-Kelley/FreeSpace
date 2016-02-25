/** @file
 * Used to DEBUG and ERROR macros, various constants, and many of the include statements needed
 * by most files.
 */
#ifndef MAIN_H
#define MAIN_H

#include <SDL/SDL.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdarg.h>
#include "game_state.h"
#include "surface.h"
#include "event_handler.h"
#include "image.h"

#define DEBUG ///< Flag saying to include debugging information at compile time.
#define STR_LEN 75 ///< The standard length of strings when intitialized.

#define WIN_WIDTH 600 ///< The width of the window in pixels
#define WIN_HEIGHT 600 ///<The height of the window in pixels

#ifdef DEBUG

/**
 * Used only in debugging to assert that the expression is true.
 * If it is, nothing happens, otherwise there is a print to the terminal.
 */
#define ASSERT(exp)                                                 \
    if(!exp)                                                        \
        printf("ASSERT ERROR: %s is not true at line %d in %s\n",   \
               #exp, __LINE__, __FILE__);                       

#endif

/**
 * Used as a uniform way to show an error in the console.
 */
#define ERROR(exp)                                                      \
    printf("ERROR: %s at line %d in %s\n",                              \
           #exp, __LINE__, __FILE__);

#endif
