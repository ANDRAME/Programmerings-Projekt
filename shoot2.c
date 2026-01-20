#include "shoot.h"
#include "players.h"
#include "ansi.h"
#include "powerup.h"

/* Your game window (same as you used before) */
#define WIN_X1  1
#define WIN_Y1  3
#define WIN_X2  97
#define WIN_Y2  38

/* Inside the border */
#define DRAW_MIN_X  (WIN_X1 + 1)
#define DRAW_MAX_X  (WIN_X2 - 1)
#define DRAW_MIN_Y  (WIN_Y1 + 1)
#define DRAW_MAX_Y  (WIN_Y2 - 1)

Bullet_t bullets[MAX_BULLETS];
int bullet_count = 0;

static int in_draw_area(int32_t x, int32_t y)
{
    return (x >= DRAW_MIN_X && x <= DRAW_MAX_X &&
            y >= DRAW_MIN_Y && y <= DRAW_MAX_Y);
}

void bullet_erase_at(int32_t x, int32_t y)
{
    if (!in_draw_area(x, y)) return;
    gotoxy((uint8_t)x, (uint8_t)y);
    putchar(' ');
}

static void bullet_draw_at(int32_t x, int32_t y)
{
    if (!in_draw_area(x, y)) return;
    gotoxy((uint8_t)x, (uint8_t)y);
    putchar('*');
}

void Bullets_Update(void)
{
    static uint8_t buffer = 0;
    buffer++;
    if (buffer < 5) return;
    buffer = 0;

    for (int i = 0; i < bullet_count; i++)
    {
        /* erase old */
        bullet_erase_at(bullets[i].x, bullets[i].y);

        /* move up */
        switch (bullets[i].type)
        {
            case BULL_SLOW: bullets[i].y -= 1; break;
            case BULL_FAST: bullets[i].y -= 2; break;
            default:        bullets[i].y -= 1; break;
        }


        if (bullets[i].y < DRAW_MIN_Y)
        {
            bullets[i] = bullets[bullet_count - 1];
            bullet_count--;
            i--;
            continue;
        }

        /* draw new */
        bullet_draw_at(bullets[i].x, bullets[i].y);
    }
}

void Bullet_Spawn(int32_t shooter, P1 *p1, P2 *p2)
{
    /* Make room for N bullets by deleting from the end */
    void make_room(int need)
    {
        while (bullet_count > (MAX_BULLETS - need)) {
            /* erase the bullet we're dropping so it doesn't leave pixels */
            bullet_erase_at(bullets[bullet_count - 1].x, bullets[bullet_count - 1].y);
            bullet_count--;
        }
    }

    /* Helper to push one bullet with a given X offset */
    void push_one(int32_t x, int32_t y, int32_t x_off)
    {
        if (bullet_count >= MAX_BULLETS) return; /* safety */

        Bullet_t *b = &bullets[bullet_count];
        b->type   = powerup_autofast_active((uint8_t)shooter) ? BULL_FAST : BULL_SLOW;
        b->player = shooter;
        b->x      = x + x_off;
        b->y      = y;

        bullet_count++;
        bullet_draw_at(b->x, b->y);
    }

    int32_t base_x, base_y;

    switch (shooter)
    {
        case 1:
            base_x = p1->x + 1;
            base_y = p1->y - 1;
            break;

        case 2:
            base_x = p2->x + 1;
            base_y = p2->y - 1;
            break;

        default:
            return;
    }

    if (powerup_triple_active((uint8_t)shooter)) {
        make_room(3);
        push_one(base_x, base_y, -1);
        push_one(base_x, base_y,  0);
        push_one(base_x, base_y, +1);
    } else {
        make_room(1);
        push_one(base_x, base_y, 0);
    }
}

