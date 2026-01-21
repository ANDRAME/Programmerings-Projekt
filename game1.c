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
#include "shoot1.h"
#include "alien.h"
#include <stdio.h>
#include <stdint.h>
#include "LUTSrc.h"
#include "asteroid.h"

#define ANSI_RED   "\033[31m"
#define ANSI_GREY  "\033[90m"
#define ANSI_RESET "\033[0m"
#define MAX_LIVES_SHOWN 3

// Draw one heart using the given ANSI color string
void draw_heart_colored(int16_t x, int16_t y, const char *color)
{
    char h1[] = {32,32,219,219,219,32,32,32,219,219,219,32,32,'\0'};
    char h2[] = {32,219,219,219,219,219,32,219,219,219,219,219,32,'\0'};
    char h3[] = {219,219,219,219,219,219,219,219,219,219,219,219,219,'\0'};
    char h4[] = {32,219,219,219,219,219,219,219,219,219,219, 219, 32,32,'\0'};
    char h5[] = {32,32,219,219,219,219,219,219,219,219,219,32,32,32,'\0'};
    char h6[] = {32,32,32,219,219,219,219,219,219, 219, 32,32,32,32,'\0'};
    char h7[] = {32,32,32,32,32,219,219,219,32,32,32,32,32,32,'\0'};

    printf("%s", color);

    gotoxy((uint8_t)x, (uint8_t)y);       printf("%s", h1);
    gotoxy((uint8_t)x, (uint8_t)(y + 1)); printf("%s", h2);
    gotoxy((uint8_t)x, (uint8_t)(y + 2)); printf("%s", h3);
    gotoxy((uint8_t)x, (uint8_t)(y + 3)); printf("%s", h4);
    gotoxy((uint8_t)x, (uint8_t)(y + 4)); printf("%s", h5);
    gotoxy((uint8_t)x, (uint8_t)(y + 5)); printf("%s", h6);
    gotoxy((uint8_t)x, (uint8_t)(y + 6)); printf("%s", h7);

    printf("%s", ANSI_RESET);
}

// Clears a rectangle that fits 3 hearts: width ~45, height 7
void clear_heart_area(int16_t x, int16_t y)
{
    for (int r = 0; r < 7; r++) {
        gotoxy((uint8_t)x, (uint8_t)(y + r));
        printf("                                             "); // 45 spaces
    }
}

// Draw 3 hearts: red for remaining lives, grey for lost lives
void draw_player_hearts(int16_t x, int16_t y, int lives_now)
{
    if (lives_now < 0) lives_now = 0;
    if (lives_now > MAX_LIVES_SHOWN) lives_now = MAX_LIVES_SHOWN;

    for (int i = 0; i < MAX_LIVES_SHOWN; i++) {
        const char *col = (i < lives_now) ? ANSI_RED : ANSI_GREY;
        draw_heart_colored((int16_t)(x + (int16_t)(i * 15)), y, col);
    }
}

void game_init(P1 *p1, P2 *p2, WindowStyle_t *style)
{
    lcd_init();
    setupTimer();

    char buf[32];

    // Use %ld for int32_t/long to avoid the warnings you saw
    snprintf(buf, sizeof(buf), "P1 <3 :%ld Score: %ld", (long)p1->hlth, (long)p1->pnt);
    lcd_write_string(1, 1, buf);

    snprintf(buf, sizeof(buf), "P2 <3 :%ld Score: %ld", (long)p2->hlth, (long)p2->pnt);
    lcd_write_string(1, 2, buf);

    lcd_push_buffer(lcd_buffer);

    window((uint8_t[]){1, 1},   (uint8_t[]){100, 40}, *style);  // main window
    window((uint8_t[]){101, 1}, (uint8_t[]){150, 40}, *style);  // hearts window

    gotoxy(103, 3);  printf("PLAYER 1");
    clear_heart_area(103, 4);
    draw_player_hearts(103, 4, (int)p1->hlth);

    gotoxy(103, 18); printf("PLAYER 2");
    clear_heart_area(103, 19);
    draw_player_hearts(103, 19, (int)p2->hlth);

    gotoxy(103, 12); printf("P1 - Points: %ld", (long)p1->pnt);
    gotoxy(103, 27); printf("P2 - Points: %ld", (long)p2->pnt);




    // alien
    gotoxy(10, 2); printf("<<==++==>>");
    gotoxy(10, 3); printf("||[]||[]||");
    gotoxy(10, 4); printf("<<======>>");

    gotoxy(45, 2); printf("<<==++==>>");
    gotoxy(45, 3); printf("||[]||[]||");
    gotoxy(45, 4); printf("<<======>>");

    gotoxy(80, 2); printf("<<==++==>>");
    gotoxy(80, 3); printf("||[]||[]||");
    gotoxy(80, 4); printf("<<======>>");

    joy_init();
}

void game_update_hearts(P1 *p1, P2 *p2)
{
    static last_p1 = -999;
    static last_p2 = -999;

    int p1_l = (int)p1->hlth;
    int p2_l = (int)p2->hlth;

    if (p1_l != last_p1) {
        clear_heart_area(103, 4);
        draw_player_hearts(103, 4, p1_l);
        last_p1 = p1_l;
    }

    if (p2_l != last_p2) {
        clear_heart_area(103, 19);
        draw_player_hearts(103, 19, p2_l);
        last_p2 = p2_l;
    }
}

void game_update_points(P1 *p1, P2 *p2)
{
    static int last_p1 = -999;
    static int last_p2 = -999;

    if (p1->pnt != last_p1) {
        gotoxy(103, 12);
        printf("P1 - Points: %-5ld", (long)p1->pnt);
        last_p1 = p1->pnt;
    }

    if (p2->pnt != last_p2) {
        gotoxy(103, 27);
        printf("P2 - Points: %-5ld", (long)p2->pnt);
        last_p2 = p2->pnt;
    }
}
