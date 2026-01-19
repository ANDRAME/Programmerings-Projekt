#include "shoot.h"
#include "ansi.h"
#include "asteroid.h"


#define WIN_X1  1
#define WIN_Y1  8
#define WIN_X2  97
#define WIN_Y2  38

//DRAW area INSIDE the window border
#define DRAW_MIN_X  (WIN_X1 + 1)
#define DRAW_MAX_X  (WIN_X2 - 1)
#define DRAW_MIN_Y  (WIN_Y1 + 1)
#define DRAW_MAX_Y  (WIN_Y2 - 1)

// ALIVE area 
#define ALIVE_MIN_X (WIN_X1)
#define ALIVE_MAX_X (WIN_X2)
#define ALIVE_MIN_Y (WIN_Y1)
#define ALIVE_MAX_Y (WIN_Y2)

Bullet_t bullets[MAX_BULLETS];
int bullet_count = 0;

static LorentzParams_t LP;
static uint8_t phys_init = 0;

static void physics_init_once(void)
{
    if (phys_init) return;
    phys_init = 1;
    LP = lorentz_defaults();
}

/* Safe area to DRAW/ERASE (never draw over border) */
static int in_draw_area(int32_t x, int32_t y)
{
    return (x >= DRAW_MIN_X && x <= DRAW_MAX_X &&
            y >= DRAW_MIN_Y && y <= DRAW_MAX_Y);
}

/* Area to KEEP bullet alive (dies only when it hits window edge) */
static int in_alive_area(int32_t x, int32_t y)
{
    return (x >= ALIVE_MIN_X && x <= ALIVE_MAX_X &&
            y >= ALIVE_MIN_Y && y <= ALIVE_MAX_Y);
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

void Bullets_Update(void)
{
    physics_init_once();

  
    static uint8_t buffer = 0;
    buffer++;
    if (buffer < 5) return;
    buffer = 0;

    /* Build asteroid centers ONCE per update */
    int16_t ax[MAX_ASTROIDS];
    int16_t ay[MAX_ASTROIDS];
    size_t n = 0;

    for (uint8_t j = 0; j < MAX_ASTROIDS; j++) {
        if (!astro[j].active) continue;
        if (n >= MAX_ASTROIDS) break;

        ax[n] = (int16_t)(astro[j].x + 5); // approx center
        ay[n] = (int16_t)(astro[j].y + 2);
        n++;
    }

    for (int i = 0; i < bullet_count; i++)
    {
        /* erase old safely */
        bullet_erase_at(bullets[i].x, bullets[i].y);

        /* physics update:
           - we do NOT let physics "kill" bullets near asteroids
           - if physics reports instability (ok==0), we keep moving straight
        */
        int ok = physics_step_bullet_lorentz(&bullets[i].phys, ax, ay, n, &LP);

        if (!ok) {
            /* FALLBACK: continue straight using current velocity
               NOTE: This assumes your phys struct has x,y,vx,vy fields.
               If your field names differ, tell me your struct and I’ll adapt it.
            */
            bullets[i].phys.x  += bullets[i].phys.vx;
            bullets[i].phys.y  += bullets[i].phys.vy;
        }

        /* write back integer position */
        phys_to_int(&bullets[i].phys, &bullets[i].x, &bullets[i].y);

        /* ONLY kill when hitting the window edge */
        if (!in_alive_area(bullets[i].x, bullets[i].y)) {
            bullets[i] = bullets[bullet_count - 1];
            bullet_count--;
            i--;
            continue;
        }

        /* draw new safely */
        bullet_draw_at(bullets[i].x, bullets[i].y);
    }
}

void Bullet_Spawn(int32_t shooter, P1 *p1, P2 *p2)
{
    physics_init_once();

    if (bullet_count >= MAX_BULLETS) return;

    Bullet_t *b = &bullets[bullet_count];

    b->type   = BULL_SLOW;
    b->player = shooter;

    int32_t x, y;
    int32_t vx = 0;
    int32_t vy = -2;

    if (shooter == 1) {
        x = p1->x + 1;
        y = p1->y - 1;
    } else if (shooter == 2) {
        x = p2->x + 1;
        y = p2->y - 1;
    } else {
        return;
    }

    b->x = x;
    b->y = y;
    b->phys = phys_from_int(x, y, vx, vy);

    /* Only draw if inside draw-safe area (never overwrite frame) */
    bullet_draw_at(b->x, b->y);

    bullet_count++;
}
