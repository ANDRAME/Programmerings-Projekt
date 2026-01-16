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



void game_init(P1 *p1, P2 *p2, WindowStyle_t *style)
{
    lcd_init();
    setupTimer();

    char buf[32];
    snprintf(buf, sizeof(buf), "Player 1 <3 :%ld", (long)p1->hlth);
    lcd_write_string(1, 1, buf);

    snprintf(buf, sizeof(buf), "Player 2 <3 :%ld", (long)p2->hlth);
    lcd_write_string(1, 2, buf);

    lcd_push_buffer(lcd_buffer);

    window((uint8_t[]){1,1}, (uint8_t[]){100,40}, *style);

    gotoxy(10,2); printf("&&&&&&&&&&");
    gotoxy(45,2); printf("&&&&&&&&&&");
    gotoxy(80,2); printf("&&&&&&&&&&");

    joystick_init();
    joy_init();
}
