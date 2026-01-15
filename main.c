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


int main(void)
{
    uart_init(115200);
    clrscr();
    cursor_hide();
    lcd_init();


    RCC->AHBENR |= RCC_AHBPeriph_GPIOA
                | RCC_AHBPeriph_GPIOB
                | RCC_AHBPeriph_GPIOC;
    setupTimer();

    WindowStyle_t myStyle;
    myStyle.wall = WALL_DOUBLE;
    myStyle.fg = "3";
    myStyle.bg = "6";
    myStyle.title = "Asteroids";

    P1 p1;
    P2 p2;
    player_init(&p1,&p2);


    Bounds bounds;
    bounds_init(&bounds);

    char buf[32];
    snprintf(buf, sizeof(buf), "Player 1 <3 :%d", p1.hlth);
    lcd_write_string(1, 1, buf);

    snprintf(buf, sizeof(buf), "Player 2 <3 :%d", p1.hlth);
    lcd_write_string(1, 2, buf);

    lcd_push_buffer(lcd_buffer);

    window((uint8_t[]){1,1}, (uint8_t[]){100,40}, myStyle);

    gotoxy(10,2);
    printf("&&&&&&&&&&");

    gotoxy(45,2);
    printf("&&&&&&&&&&");

    gotoxy(80,2);
    printf("&&&&&&&&&&");


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
    	gotoxy(104,6);
    	printf("points %d", P1_player.pnt);
    }

}
