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
#include "asteroid.h"

volatile uint8_t g_pause = 0;
volatile uint8_t g_pause_request = 0;


uint8_t uart_getJoystickDirection(void)
{
    static uint8_t state = 0;
    static uint8_t dir_ttl = 0;


    // ESC sequence parser state: 0=normal, 1=got ESC, 2=got ESC[
    static uint8_t esc = 0;

    uint8_t c = uart_get_char();

            if (esc == 0)
            {

                if (c == 'p') {
                    state |= (1<<4);          // shoot event
                }
                else if (c == 0x1B) {
                    esc = 1;
                }
                else if (c == 'b') {
                	g_pause_request = 1;
                }
            }

            else if (esc == 1)
            {
                if (c == '[') esc = 2;
                else esc = 0;
            }
            else if (esc == 2)
            {
                // arrow received: update direction
                state &= ~((1<<0)|(1<<1)|(1<<2)|(1<<3));

                switch (c) {
                    case 'A': state |= (1<<0); dir_ttl = 6; break; // up
                    case 'B': state |= (1<<1); dir_ttl = 6; break; // down
                    case 'D': state |= (1<<2); dir_ttl = 6; break; // left
                    case 'C': state |= (1<<3); dir_ttl = 6; break; // right
                    default: break;
                }
                esc = 0;
            }

    // direction decay
    if (dir_ttl > 0) dir_ttl--;
    else state &= ~((1<<0)|(1<<1)|(1<<2)|(1<<3));

    // Make shoot a ONE-FRAME event
    uint8_t out = state;
    state &= ~(1<<4);

    return out;
}

void pause_manager_step(P1 *p1, P2 *p2, WindowStyle_t *style)
{
    static uint8_t cooldown = 0;
    if (cooldown > 0) cooldown--;

    if (g_pause_request && cooldown == 0)
    {
    	g_pause_request = 0;
        cooldown = 20;   // debounce

        g_pause ^= 1;

        clrscr();
        if (g_pause) {
            render_boss();     // draw pause screen once (or you can redraw each loop)
        } else {
            window((uint8_t[]){1, 1},   (uint8_t[]){100, 40}, *style);
            window((uint8_t[]){101, 1}, (uint8_t[]){150, 40}, *style);

            gotoxy(103, 3);  printf("PLAYER 1");
            clear_heart_area(103, 4);
            draw_player_hearts(103, 4, (int)p1->hlth);

            gotoxy(103, 18); printf("PLAYER 2");
            clear_heart_area(103, 19);
            draw_player_hearts(103, 19, (int)p2->hlth);

            gotoxy(103, 12); printf("P1 - Points: %ld", (long)p1->pnt);
            gotoxy(103, 27); printf("P2 - Points: %ld", (long)p2->pnt);
        }
    }
    else if(g_pause_request){
    	g_pause_request = 0;
    }
}
