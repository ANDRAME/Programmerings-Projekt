#ifndef _ANSI_H_
#define _ANSI_H_

#include <stdint.h>

#define ESC 0x1B

void fgcolor(uint8_t foreground);
void bgcolor(uint8_t background);
void color(uint8_t foreground, uint8_t background);
void resetbgcolor(void);
void clrscr(void);
void clreol(void);
void gotoxy(uint8_t x, uint8_t y);
void underline(uint8_t on);
void blink(uint8_t on);
void inverse(uint8_t on);
static inline void cursor_hide(void) { printf("\x1b[?25l"); }


#endif
