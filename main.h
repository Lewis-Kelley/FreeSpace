/** @file
 * Used to DEBUG and ERROR macros, various constants, and many of the
 * include statements needed by most files.
 */
#ifndef MAIN_H
#define MAIN_H

#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdarg.h>
#include "src/game_state.h"
#include "src/update.h"
#include "src/surface.h"
#include "src/event_handler.h"
#include "src/image.h"

#define DEBUG ///< Flag saying to include debugging information at compile time.
#define STR_LEN 75 ///< The standard length of strings when intitialized.
#define MOVE_SPEED 0.007 ///< The standard speed of a unit.
#define ROUNDOFF 0.001 ///< Roundoff to be used when testing for equal doubles.
#define CAM_SPEED 0.01 ///< The speed of the camera.

/**
 * Convinience macro to return the absolute value of an expression.
 */
#define ABS(exp)                                \
  ((exp) < 0 ? -(exp) : (exp))

#ifdef DEBUG

/**
 * Used only in debugging to assert that the expression is true.
 * If it is, nothing happens, otherwise there is a print to the terminal.
 */
#define ASSERT(exp)                                           \
  if(!exp)                                                    \
    printf("ASSERT ERROR: %s is not true at line %d in %s\n", \
           #exp, __LINE__, __FILE__);                       

#endif

/**
 * Used as a uniform way to show an error in the console.
 */
#define ERROR(exp)                              \
  printf("ERROR: %s at line %d in %s\n",        \
         exp, __LINE__, __FILE__);

#endif
