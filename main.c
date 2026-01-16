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
#include "game.h"
#include "ui_screen.h"


int main(void)
{
    uart_init(115200);
    clrscr();
    cursor_hide();



    WindowStyle_t myStyle;
    myStyle.wall = WALL_DOUBLE;
    myStyle.fg = 7;
    myStyle.bg = 0;
    myStyle.title = "Asteroids";

    P1 p1;
    P2 p2;
    player_init(&p1,&p2);

    Bounds bounds;
    bounds_init(&bounds);


    menu_action_t act = menu(&p1, &p2, &myStyle);

    if (act == MENU_ACTION_QUIT) {
        while (1) {}
    }

    while (1) {

    	gotoxy(104,4);
        printf("second %d", Time.s);       // %s for strings
        printf("min %d", Time.m);         // %d for integers
        printf("Hour %d", Time.h);

        if (Time.hs % 10 == 0) {
        	lcd_update(3);
        }

        if (Time.hs % 10 == 0) {
        	lcd_update(0);
        }

        player_step(&p1, &p2, &bounds); // loop forever
    	Bullets_Update();
    	point_count();


    }

}
