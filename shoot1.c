#include "shoot1.h"
#include "players.h"
#include "ansi.h"
#include "powerup.h"
#include "physics.h"
#include "asteroid.h"
#include <stddef.h>
#include <stdint.h>

/* Your game window */
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

//Lorentz params once
static LorentzParams_t g_lp;
static uint8_t g_lp_inited = 0;

static void ensure_params(void)
{
    if (g_lp_inited) return;
    g_lp = lorentz_defaults();

    // lorenz curve (asteroid)
    g_lp.radius = 6;
    g_lp.edge   = 6;
    g_lp.range2 = 10 * 10;
    g_lp_inited = 1;
}

static int in_draw_area(int32_t x, int32_t y)
{
    return (x >= DRAW_MIN_X && x <= DRAW_MAX_X &&
            y >= DRAW_MIN_Y && y <= DRAW_MAX_Y);
}

static void bullet_erase_at(int32_t x, int32_t y)
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

//asteroid centers
static size_t build_asteroid_centers(int16_t *ax, int16_t *ay, size_t cap)
{
    size_t n = 0;
    for (uint8_t i = 0; i < MAX_ASTROIDS && n < cap; i++) {
        if (!astro[i].active) continue;


        ax[n] = (int16_t)(astro[i].x + 5);
        ay[n] = (int16_t)(astro[i].y + 2);
        n++;
    }
    return n;
}

void Bullets_Update(void)
{
    ensure_params();

    static uint8_t buffer = 0;
    buffer++;
    if (buffer < 5) return;   // keep original update rate
    buffer = 0;

    // Collect asteroids once per bullet update
    int16_t ax[MAX_ASTROIDS];
    int16_t ay[MAX_ASTROIDS];
    size_t n_ast = build_asteroid_centers(ax, ay, MAX_ASTROIDS);

    for (int i = 0; i < bullet_count; i++)
    {

        bullet_erase_at(bullets[i].x, bullets[i].y);


        int alive = physics_step_bullet_lorentz(&bullets[i].phys, ax, ay, n_ast, &g_lp);

        bullets[i].x = FX16_TO_INT(bullets[i].phys.x);
        bullets[i].y = FX16_TO_INT(bullets[i].phys.y);


        // kill if physics says so OR out of bounds
        if (!alive || !in_draw_area(bullets[i].x, bullets[i].y))
        {

            bullets[i] = bullets[bullet_count - 1];
            bullet_count--;
            i--;
            continue;
        }


        bullet_draw_at(bullets[i].x, bullets[i].y);
    }
}

void Bullet_Spawn(int32_t shooter, P1 *p1, P2 *p2)
{
    ensure_params();


    void make_room(int need)
    {
        while (bullet_count > (MAX_BULLETS - need)) {
            bullet_erase_at(bullets[bullet_count - 1].x, bullets[bullet_count - 1].y);
            bullet_count--;
        }
    }


    void push_one(int32_t x, int32_t y, int32_t x_off, int32_t vy_int)
    {
        if (bullet_count >= MAX_BULLETS) return;

        Bullet_t *b = &bullets[bullet_count];
        b->type   = powerup_autofast_active((uint8_t)shooter) ? BULL_FAST : BULL_SLOW;
        b->player = shooter;

        int32_t sx = x + x_off;
        int32_t sy = y;

        b->phys = phys_from_int(sx, sy, 0, vy_int);

        b->x = sx;
        b->y = sy;

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


    int32_t vy_int = powerup_autofast_active((uint8_t)shooter) ? -2 : -1;

    if (powerup_triple_active((uint8_t)shooter)) {
        make_room(3);
        push_one(base_x, base_y, -1, vy_int);
        push_one(base_x, base_y,  0, vy_int);
        push_one(base_x, base_y, +1, vy_int);
    } else {
        make_room(1);
        push_one(base_x, base_y, 0, vy_int);
    }
}
