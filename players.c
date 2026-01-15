#include <stdio.h>
#include "players.h"
#include "joystick.h"
#include "ansi.h"
#include "keyboard.h"   // must provide: JoystickDirection2 uart_getJoystickDirection2(uint8_t c);
#include "30010_io.h"   // uart_get_char()
#include "timer.h"
#include "shoot.h"

#define PLAYER_SPEED 1

P1 P1_player;
P2 P2_player;

void player_init(P1 *p1, P2 *p2)
{
    p1->x = 10; p1->y = 10;
    p1->vx = 0; p1->vy = 0;
    p1->pnt = 0; p1->hlth = 5;
    gotoxy(p1->x, p1->y);
    printf("@");

    p2->x = 13; p2->y = 13;
    p2->vx = 0; p2->vy = 0;
    p2->pnt = 0; p2->hlth = 5;
    gotoxy(p2->x, p2->y);
    printf("?");
}

void bounds_init(Bounds *bounds)
{
    bounds->min_x = 2;
    bounds->max_x = 96;
    bounds->min_y = 2;
    bounds->max_y = 36;
}

void player_step(P1 *p1, P2 *p2, Bounds *bounds){

	static uint8_t buffer = 0;
	buffer++;

	if ((uint8_t)(buffer) >= 10) {
	    buffer = 0;

	    JoystickDirection dir = getJoystickDirection(readJoystick());

	    p1->vx = 0;
	    p1->vy = 0;

	    switch (dir)
	    {
	        case JOY_UP:    p1->vy = -PLAYER_SPEED; break;
	        case JOY_DOWN:  p1->vy =  PLAYER_SPEED; break;
	        case JOY_LEFT:  p1->vx = -PLAYER_SPEED; break;
	        case JOY_RIGHT: p1->vx =  PLAYER_SPEED; break;
	        case JOY_CENTER:
	            Bullet_Spawn(1, p1, p2);
	            break;

	        default: break;
	    	}
		}






    // -------- P2 input: UART (arrow keys) --------
    // This blocks waiting for UART input. If you want non-blocking, tell me what UART helpers you have.
    JoystickDirection2 dir2 = uart_getJoystickDirection();

    p2->vx = 0;
    p2->vy = 0;

    switch (dir2)
    {
        case JOY_UP2:    p2->vy = -PLAYER_SPEED; break;
        case JOY_DOWN2:  p2->vy =  PLAYER_SPEED; break;
        case JOY_LEFT2:  p2->vx = -PLAYER_SPEED; break;
        case JOY_RIGHT2: p2->vx =  PLAYER_SPEED; break;

        case JOY_SHOOT2:
            Bullet_Spawn(2, p1, p2);
            break;

        default: break;
    }

    // -------- erase old --------
    sprite_erase(p1->x, p1->y);
    sprite_erase(p2->x, p2->y);

    // -------- move --------
    p1->x += p1->vx;  p1->y += p1->vy;
    p2->x += p2->vx;  p2->y += p2->vy;

    // -------- clamp P1 --------
    if (p1->x < bounds->min_x) p1->x = bounds->min_x;
    else if (p1->x > bounds->max_x) p1->x = bounds->max_x;

    if (p1->y < bounds->min_y) p1->y = bounds->min_y;
    else if (p1->y > bounds->max_y) p1->y = bounds->max_y;

    // -------- clamp P2 --------
    if (p2->x < bounds->min_x) p2->x = bounds->min_x;
    else if (p2->x > bounds->max_x) p2->x = bounds->max_x;

    if (p2->y < bounds->min_y) p2->y = bounds->min_y;
    else if (p2->y > bounds->max_y) p2->y = bounds->max_y;

    // -------- draw new --------
    sprite_draw(p1->x, p1->y);
    sprite_draw(p2->x, p2->y);
}
