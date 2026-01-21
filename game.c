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
/*


void game_init(P1 *p1, P2 *p2, WindowStyle_t *style)
{
    lcd_init();
    setupTimer();

    char buf[32];
    snprintf(buf, sizeof(buf), "P1 <3 :%ld Score: %d", (long)p1->hlth, p1->pnt);
    lcd_write_string(1, 1, buf);

    snprintf(buf, sizeof(buf), "P2 <3 :%ld Score:%d", (long)p2->hlth), p2->pnt;
    lcd_write_string(1, 2, buf);

    lcd_push_buffer(lcd_buffer);

    window((uint8_t[]){1,1}, (uint8_t[]){100,40}, *style);



    gotoxy(10,2); printf("<<==++==>>");
    gotoxy(10,3); printf("||[]||[]||");
    gotoxy(10,4); printf("<<======>>");

    gotoxy(45,2); printf("<<==++==>>");
    gotoxy(45,3); printf("||[]||[]||");
    gotoxy(45,4); printf("<<======>>");

    gotoxy(80,2); printf("<<==++==>>");
    gotoxy(80,3); printf("||[]||[]||");
    gotoxy(80,4); printf("<<======>>");


    joystick_init();
    joy_init();
} */
