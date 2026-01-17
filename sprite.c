#include "sprite.h"
#include "ansi.h"
#include <stdio.h>

const uint8_t PLAYER1_COLORSPRITE[4][4] = {
  {0,1,1,0},
  {1,2,2,1},
  {1,2,3,1},
  {0,1,1,0}
};

void ansi_bg(uint8_t c)
{
    // Map 1..7 to ANSI background colors (40-47)
    // 0 should not be drawn (transparent)
    putchar('\x1b'); putchar('[');
    printf("%dm", 40 + (c % 8));
}

	void ansi_reset(void)
{
    printf("\x1b[0m");
}


void sprite_erase(int x, int y)
{
    for (uint8_t row = 0; row < 4; row++) {
        gotoxy(x, y + row);
        // reset styling so we truly erase
        ansi_reset();
        for (uint8_t col = 0; col < 4; col++) {
            putchar(' ');
        }
    }
}

void sprite_draw(int cx, int cy)
{
    for (uint8_t row = 0; row < 4; row++) {
        gotoxy(cx, cy + row);

        for (uint8_t col = 0; col < 4; col++) {
            uint8_t px = PLAYER1_COLORSPRITE[row][col];
            if (px == 0) {
                // transparent: don't overwrite, OR draw blank if you want solid rectangle
                putchar(' ');
            } else {
                ansi_bg(px);
                putchar(' ');     // colored pixel
                ansi_reset();     // avoid color “bleeding”
            }
        }
    }
}



