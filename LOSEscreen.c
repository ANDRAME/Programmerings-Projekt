#include "ansi.h"
#include <stdio.h>
#include <stdint.h>

void draw_lose_screen(uint8_t x, uint8_t y)
{
    char three[]  = {219,219,219,'\0'};
    char two[]    = {219,219,'\0'};
    char one[]    = {219,'\0'};

    char one1[]   = {223,'\0'};
    char three1[] = {223,223,223,'\0'};
    char four[]   = {223,223,223,223,'\0'};

    // ---------- G ----------
    fgcolor(1);
    gotoxy(x+1,y);   printf("%s", three);
    gotoxy(x,y+1);   printf("%s", one);
    gotoxy(x,y+2);   printf("%s", one);
    gotoxy(x,y+3);   printf("%s", one);
    gotoxy(x+3,y+3); printf("%s", two);
    gotoxy(x,y+4);   printf("%s", one);
    gotoxy(x+4,y+4); printf("%s", one);
    gotoxy(x+1,y+5); printf("%s", three);

    // ---------- A ----------
    // (spacing tweak: move to the right of G)
    uint8_t ax = x + 7;
    fgcolor(1);
    gotoxy(ax+1,y);   printf("%s", two);
    gotoxy(ax,y+1);   printf("%s", one);
    gotoxy(ax,y+2);   printf("%s", one);
    gotoxy(ax+1,y+3); printf("%s", three);
    gotoxy(ax+3,y+1); printf("%s", one);
    gotoxy(ax+3,y+2); printf("%s", one);
    gotoxy(ax+4,y+3); printf("%s", one);

    // ---------- M ----------
    uint8_t mx = x + 14;
    fgcolor(1);
    gotoxy(mx,y);     printf("%s", one);
    gotoxy(mx,y+1);   printf("%s", two);
    gotoxy(mx,y+2);   printf("%s", one);
    gotoxy(mx,y+3);   printf("%s", one);
    gotoxy(mx+2,y+2); printf("%s", one);
    gotoxy(mx+2,y+3); printf("%s", one);
    gotoxy(mx+3,y+1); printf("%s", one);
    gotoxy(mx+4,y+2); printf("%s", one);
    gotoxy(mx+4,y+3); printf("%s", one);

    // ---------- E ----------
    uint8_t ex = x+8;
    fgcolor(1);
    gotoxy(ex+12,y);   printf("%s", four);
    gotoxy(ex+12,y+1); printf("%s", one);
    gotoxy(ex+12,y+2); printf("%s", one);
    gotoxy(ex+12,y+3); printf("%s", three);
    gotoxy(ex+12,y+4); printf("%s", one);
    gotoxy(ex+12,y+5); printf("%s", four);


    // ---------- OVER ----------
    // Put OVER a little lower and to the right (adjust as you like)
    uint8_t ox = x;
    uint8_t oy = y + 8;

    // O
    fgcolor(1);
    gotoxy(ox+1,oy);   printf("%s", three1);
    gotoxy(ox,oy+1);   printf("%s", one);
    gotoxy(ox,oy+2);   printf("%s", one);
    gotoxy(ox,oy+3);   printf("%s", one);
    gotoxy(ox,oy+4);   printf("%s", one);
    gotoxy(ox+1,oy+5); printf("%s", three1);

    gotoxy(ox+4,oy+1); printf("%s", one);
    gotoxy(ox+4,oy+2); printf("%s", one);
    gotoxy(ox+4,oy+3); printf("%s", one);
    gotoxy(ox+4,oy+4); printf("%s", one);

    // V
    gotoxy(ox+6,oy);   printf("%s", one);
    gotoxy(ox+6,oy+1); printf("%s", one);
    gotoxy(ox+6,oy+2); printf("%s", one);
    gotoxy(ox+6,oy+3); printf("%s", one);

    gotoxy(ox+7,oy+4); printf("%s", one);
    gotoxy(ox+8,oy+5); printf("%s", one);
    gotoxy(ox+9,oy+4); printf("%s", one);

    gotoxy(ox+10,oy+3); printf("%s", one);
    gotoxy(ox+10,oy+2); printf("%s", one);
    gotoxy(ox+10,oy+1); printf("%s", one);
    gotoxy(ox+10,oy);   printf("%s", one);

    // E
    gotoxy(ox+12,oy);   printf("%s", four);
    gotoxy(ox+12,oy+1); printf("%s", one);
    gotoxy(ox+12,oy+2); printf("%s", one);
    gotoxy(ox+12,oy+3); printf("%s", three);
    gotoxy(ox+12,oy+4); printf("%s", one);
    gotoxy(ox+12,oy+5); printf("%s", four);

    // R
    gotoxy(ox+17,oy);   printf("%s", three);
    gotoxy(ox+17,oy+1); printf("%s", one);
    gotoxy(ox+17,oy+2); printf("%s", one);
    gotoxy(ox+17,oy+3); printf("%s", three1);
    gotoxy(ox+17,oy+4); printf("%s", one);
    gotoxy(ox+17,oy+5); printf("%s", one);

    gotoxy(ox+20,oy+1); printf("%s", one);
    gotoxy(ox+20,oy+2); printf("%s", one);
    gotoxy(ox+20,oy+4); printf("%s", one);

    // message
    fgcolor(7);
    gotoxy(10, oy + 8);
    printf("L + ratio + skill issue + no money + no mama + git gud + no babes");
}
