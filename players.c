#include <stdio.h>
#include "players.h"
#include "joystick.h"
#include "ansi.h"
#include "keyboard.h"
#include "30010_io.h"
#include "timer.h"
#include "shoot.h"
#include "asteroid.h"

#define PLAYER_SPEED 1

P1 P1_player;
P2 P2_player;

void player_init(P1 *p1, P2 *p2)
{
    p1->x = 10; p1->y = 80;
    p1->vx = 0; p1->vy = 0;
    p1->pnt = 0; p1->hlth = 3;
    gotoxy(p1->x, p1->y);
    printf("@");

    p2->x = 86; p2->y = 80;
    p2->vx = 0; p2->vy = 0;
    p2->pnt = 0; p2->hlth = 3;
    gotoxy(p2->x, p2->y);
    printf("?");
}

void bounds_init(Bounds *bounds)
{
    bounds->min_x = 2;
    bounds->max_x = 96;
    bounds->min_y = 10;
    bounds->max_y = 36;
}

void player_step(P1 *p1, P2 *p2, Bounds *bounds){


    uint8_t state = readJoystick();

    p1->vx = 0;
    p1->vy = 0;

    if (state & (1 << 4)) Bullet_Spawn(1, p1, p2); // shoot

    if (state & (1 << 0)) p1->vy = -PLAYER_SPEED;  // up
    if (state & (1 << 1)) p1->vy =  PLAYER_SPEED;  // down
    if (state & (1 << 2)) p1->vx = -PLAYER_SPEED;  // left
    if (state & (1 << 3)) p1->vx =  PLAYER_SPEED;  // right

    uint8_t state2 = uart_getJoystickDirection();

    p2->vx = 0;
    p2->vy = 0;

    if (state2 & (1<<0))    p2->vy = -PLAYER_SPEED;
    if (state2 & (1<<1))  p2->vy =  PLAYER_SPEED;
    if (state2 & (1<<2))  p2->vx = -PLAYER_SPEED;
    if (state2 & (1<<3)) p2->vx =  PLAYER_SPEED;

    if (state2 & (1<<4)) {
        Bullet_Spawn(2, p1, p2);
        // optional: clear shoot so it becomes “one-shot per keypress”
    }

    sprite_erase(p1->x, p1->y);
    sprite_erase(p2->x, p2->y);


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

    for (uint8_t i = 0; i < MAX_ASTROIDS; i++)
        {
            if (!astro[i].active)
                continue;

            int ax = astro[i].x;
            int ay = astro[i].y;

            // inside asteroid rectangle: (x → x+10, y → y+5)
            if (p1->x >= ax && p1->x <= ax + 10 &&
                p1->y >= ay && p1->y <= ay + 5)
            {
                // teleport player out
                p1->x = 2;
                p1->y = 30;
                p1->hlth--;
            }
        }
    for (uint8_t i = 0; i < MAX_ASTROIDS; i++)
        {
            if (!astro[i].active)
                continue;

            int ax = astro[i].x;
            int ay = astro[i].y;

            // inside asteroid rectangle: (x → x+10, y → y+5)
            if (p2->x >= ax && p2->x <= ax + 10 &&
                p2->y >= ay && p2->y <= ay + 5)
            {
                // teleport player out  //change to blinkning?
                p2->x = 2;
                p2->y = 30;
                p2->hlth--;
            }
        }
    // -------- draw new --------
    sprite_draw(p1->x, p1->y);
    sprite_draw(p2->x, p2->y);
}
