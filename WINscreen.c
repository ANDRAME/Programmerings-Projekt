#include "ansi.h"
#include <stdio.h>
#include <stdint.h>
#include "WINscreen.h"

void draw_win_screen(uint8_t x, uint8_t y, uint8_t winner_player)
{
    char one[]    = {219,'\0'};
    char two[]    = {219,219,'\0'};
    char three[]  = {219,219,219,'\0'};
    char four223[]  = {223,223,223,223,'\0'};
    char three223[] = {223,223,223,'\0'};

    clrscr();

    // ---------- BIG "WIN" ----------
    // Colors: W + N green, I white
    uint8_t wx = x;
    uint8_t ix = x + 12;
    uint8_t nx = x + 18;

    // W (green)
    fgcolor(2);
    // left column
    gotoxy(wx, y);   printf("%s", one);
    gotoxy(wx, y+1); printf("%s", one);
    gotoxy(wx, y+2); printf("%s", one);
    gotoxy(wx, y+3); printf("%s", one);
    gotoxy(wx, y+4); printf("%s", one);

    // right column
    gotoxy(wx+6, y);   printf("%s", one);
    gotoxy(wx+6, y+1); printf("%s", one);
    gotoxy(wx+6, y+2); printf("%s", one);
    gotoxy(wx+6, y+3); printf("%s", one);
    gotoxy(wx+6, y+4); printf("%s", one);

    // middle “V” legs
    gotoxy(wx+2, y+3); printf("%s", one);
    gotoxy(wx+3, y+4); printf("%s", one);
    gotoxy(wx+4, y+3); printf("%s", one);

    // I (white)
    fgcolor(15);
    gotoxy(ix, y);     printf("%s", three223);
    gotoxy(ix+1, y+1); printf("%s", one);
    gotoxy(ix+1, y+2); printf("%s", one);
    gotoxy(ix+1, y+3); printf("%s", one);
    gotoxy(ix, y+4);   printf("%s", three223);

    // N (green)
    fgcolor(2);
    // left column
    gotoxy(nx, y);   printf("%s", one);
    gotoxy(nx, y+1); printf("%s", one);
    gotoxy(nx, y+2); printf("%s", one);
    gotoxy(nx, y+3); printf("%s", one);
    gotoxy(nx, y+4); printf("%s", one);

    // diagonal
    gotoxy(nx+1, y+1); printf("%s", one);
    gotoxy(nx+2, y+2); printf("%s", one);
    gotoxy(nx+3, y+3); printf("%s", one);

    // right column
    gotoxy(nx+5, y);   printf("%s", one);
    gotoxy(nx+5, y+1); printf("%s", one);
    gotoxy(nx+5, y+2); printf("%s", one);
    gotoxy(nx+5, y+3); printf("%s", one);
    gotoxy(nx+5, y+4); printf("%s", one);

    // ---------- Winner text ----------
    fgcolor(7);
    gotoxy(x, y + 7);
    printf("====================================");

    gotoxy(x, y + 9);
    if (winner_player == 1) {
        fgcolor(1); // yellow
        printf("PLAYER 1 WINS!");
    } else {
        fgcolor(1); // blue
        printf("PLAYER 2 WINS!");
    }

    fgcolor(7);
    gotoxy(x, y + 11);
    printf("Press 'b' to return / continue");

    gotoxy(x, y + 13);
    printf("====================================");

    // little extra line (optional)
    fgcolor(7);
    gotoxy(10, y + 16);
    printf("WOAAAAAA YOU SO GOOD!!! Mandem done been at some retro arcades eh? ");
}
