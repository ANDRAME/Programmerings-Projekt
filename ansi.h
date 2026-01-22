#ifndef _ANSI_H_
#define _ANSI_H_





/* Includes -------------------------------------------------------------*/
// Whatever needs to be included
#include <stdint.h>
#include <stdio.h>
/* Exported types -------------------------------------------------------*/
/* Exported constants ---------------------------------------------------*/
/* Exported macro -------------------------------------------------------*/

#define colors // Whatever needs to be defined
/* Exported functions -------------------------------------------------- */

void fgcolor(uint8_t foreground);
void bgcolor(uint8_t background);
void color(uint8_t foreground, uint8_t background);
void resetbgcolor();
void gotoxy(uint8_t x, uint8_t y);
void clrscr();
void clreol();
void underline(uint8_t on);
void blink(uint8_t light);
void inverse(uint8_t inv);
void clrcur(void);








#endif /* _ANSI_H_ */
