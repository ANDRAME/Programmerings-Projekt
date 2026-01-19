
#include "game.h"
#include "stm32f30x_conf.h"
#include "30010_io.h"
#include "ansi.h"
#include "window.h"
#include "joystick.h"
#include "timer.h"
#include "keyboard.h"
#include "lcd.h"
#include "players.h"
#include "shoot.h"
#include "alien.h"
#include <stdio.h>
#include <stdint.h>
#include "LUTSrc.h"
#include "asteroid.h"


#define ANSI_RED   "\033[31m"
#define ANSI_RESET "\033[0m"


void draw_heart(int16_t x, int16_t y)
{
    char h1[] = {32,32,219,219,219,32,32,32,219,219,219,32,32,'\0'};
    char h2[] = {32,219,219,219,219,219,32,219,219,219,219,219,32,'\0'};
    char h3[] = {219,219,219,219,219,219,219,219,219,219,219,219,219,'\0'};
    char h4[] = {32,219,219,219,219,219,219,219,219,219,219,32,32,'\0'};
    char h5[] = {32,32,219,219,219,219,219,219,219,219,32,32,32,'\0'};
    char h6[] = {32,32,32,219,219,219,219,219,219,32,32,32,32,'\0'};
    char h7[] = {32,32,32,32,32,219,219,219,32,32,32,32,32,32,'\0'};

    printf(ANSI_RED);

    gotoxy(x, y);     printf("%s", h1);
    gotoxy(x, y + 1); printf("%s", h2);
    gotoxy(x, y + 2); printf("%s", h3);
    gotoxy(x, y + 3); printf("%s", h4);
    gotoxy(x, y + 4); printf("%s", h5);
    gotoxy(x, y + 5); printf("%s", h6);
    gotoxy(x, y + 6); printf("%s", h7);

    printf(ANSI_RESET);
}

/* Draw N hearts (max 3) next to each other.
   Heart width is ~13 chars; we use spacing 15 to avoid overlap. */
static void draw_player_hearts(int16_t x, int16_t y, int lives)
{
    if (lives < 0) lives = 0;
    if (lives > 3) lives = 3;

    for (int i = 0; i < lives; i++)
    {
        draw_heart(x + (int16_t)(i * 15), y);
    }
}

/* Optional: clear the heart area before redraw (useful if lives drop).
   Clears a rectangle that fits 3 hearts: width ~ (3*15)=45, height 7. */
static void clear_heart_area(int16_t x, int16_t y)
{
    for (int r = 0; r < 7; r++)
    {
        gotoxy(x, y + r);
        printf("                                             "); // 45 spaces
    }
}


void game_init(P1 *p1, P2 *p2, WindowStyle_t *style)
{
    lcd_init();
    setupTimer();

    char buf[32];

    snprintf(buf, sizeof(buf), "P1 <3 :%ld Score: %d", (long)p1->hlth, p1->pnt);
    lcd_write_string(1, 1, buf);

    snprintf(buf, sizeof(buf), "P2 <3 :%ld Score: %d", (long)p2->hlth, p2->pnt);
    lcd_write_string(1, 2, buf);

    lcd_push_buffer(lcd_buffer);

    
    window((uint8_t[]){1, 1}, (uint8_t[]){100, 40}, *style);//main window

    
    window((uint8_t[]){101, 1}, (uint8_t[]){120, 40}, *style);//hearts window

    
    gotoxy(103, 3);  printf("PLAYER 1");
    clear_heart_area(103, 4);
    draw_player_hearts(103, 4, (int)p1->hlth);

    gotoxy(103, 14); printf("PLAYER 2");
    clear_heart_area(103, 15);
    draw_player_hearts(103, 15, (int)p2->hlth);

    //alien
    gotoxy(10, 2); printf("<<==++==>>");
    gotoxy(10, 3); printf("||[]||[]||");
    gotoxy(10, 4); printf("<<======>>");

    gotoxy(45, 2); printf("<<==++==>>");
    gotoxy(45, 3); printf("||[]||[]||");
    gotoxy(45, 4); printf("<<======>>");

    gotoxy(80, 2); printf("<<==++==>>");
    gotoxy(80, 3); printf("||[]||[]||");
    gotoxy(80, 4); printf("<<======>>");

    joystick_init();
    joy_init();
}
