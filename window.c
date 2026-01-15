#include "window.h"
#include "stdio.h"

// CP437 ASCII LOOKUP TABLE
const ASCII_LUT SINGLE_LINE = {218, 191, 192, 217, 196, 179, 180, 195};
const ASCII_LUT DOUBLE_LINE = {201, 187, 200, 188, 205, 186, 185, 204};

void window(uint8_t xy1[2], uint8_t xy2[2], WindowStyle_t style)
{
    uint8_t x1 = xy1[0], y1 = xy1[1];
    uint8_t x2 = xy2[0], y2 = xy2[1];


    ASCII_LUT box = (style.wall == WALL_SINGLE) ? SINGLE_LINE : DOUBLE_LINE;

    //COLOURING
    bgcolor(style.bg);
    fgcolor(style.fg);

    //EDGES BUILDING
    gotoxy(x1, y1);
    printf("%c", box.TL);

    int inner = (int)x2 - (int)x1 - 1;
    if (inner <= 0) return;
    printf("%c", box.CL);
    inner--;


    // TITLE
    int title_len = 0;
    while (style.title[title_len] != '\0') title_len++;
    if (title_len > inner) title_len = inner;

    printf("%.*s", title_len, style.title);
    inner -= title_len;

    printf("%c", box.CR);
    inner--;

    //EDGES CONTINUED
    for (int i = 0; i < inner; i++) {
        printf("%c", box.H);
    }

    printf("%c", box.TR);

    // SIDES + FILL
    bgcolor(style.bg);
    for (uint8_t y = y1 + 1; y < y2; y++) {
        gotoxy(x1, y); printf("%c", box.V);
        gotoxy(x1 + 1, y);
        for (uint8_t x = x1 + 1; x < x2; x++) putchar(' ');
        gotoxy(x2, y); printf("%c", box.V);
    }


    // BOTTOM
    gotoxy(x1, y2); printf("%c", box.BL);
    for (uint8_t x = x1 + 1; x < x2; x++) printf("%c", box.H);
    printf("%c", box.BR);

    //ERROR IN BG COLOURING?

    resetbgcolor();
    fgcolor(7);
}

