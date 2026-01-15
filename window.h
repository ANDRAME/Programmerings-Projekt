#ifndef _WINDOW_H_
#define _WINDOW_H_

#include <stdint.h>
#include "ansi.h"  // for fgcolor, bgcolor, gotoxy, etc.

/* Wall style enum */
typedef enum {
    WALL_SINGLE,
    WALL_DOUBLE
} WallStyle_t;

/* Window style struct */
typedef struct {
    WallStyle_t wall; // single or double walls
    uint8_t fg;       // foreground color
    uint8_t bg;       // background color
    const char* title; // optional window title
} WindowStyle_t;


/* Box characters struct */
typedef struct {
    uint8_t TL, TR, BL, BR;  // corners
    uint8_t H, V;            // horizontal and vertical
    uint8_t CL, CR;			//Title Bars
} ASCII_LUT;

/* Window drawing function */
void window(uint8_t xy1[2], uint8_t xy2[2], WindowStyle_t style);

#endif
