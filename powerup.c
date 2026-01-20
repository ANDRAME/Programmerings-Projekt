#include "powerup.h"
#include "ansi.h"

typedef struct {
    uint8_t active;
    int32_t x;
    int32_t y;
    PowerupType_t type;
    uint32_t next_spawn_hs;
} Powerup_t;

static Powerup_t g_pu;

/* effect timers in 1/100s ticks */
static uint32_t g_triple_until_hs[3];
static uint32_t g_autofast_until_hs[3];

/* simple PRNG */
static uint32_t lcg_state = 0x12345678u;
static inline uint32_t lcg_next(void)
{
    lcg_state = lcg_state * 1664525u + 1013904223u;
    return lcg_state;
}

static inline uint32_t time_now_hs(void)
{
    uint32_t sec = (uint32_t)(Time.h * 3600 + Time.m * 60 + Time.s);
    return sec * 100u + (uint32_t)Time.hs;
}

static inline int32_t clamp_i32(int32_t v, int32_t lo, int32_t hi)
{
    if (v < lo) return lo;
    if (v > hi) return hi;
    return v;
}

static void powerup_erase(int32_t x, int32_t y)
{
    gotoxy((uint8_t)x, (uint8_t)y);
    putchar(' ');
}

static void powerup_draw(PowerupType_t t, int32_t x, int32_t y)
{
    if (t == POWERUP_TRIPLE_SHOT) fgcolor(5);      /* purple */
    else if (t == POWERUP_AUTO_FAST) fgcolor(11);  /* yellow */
    else fgcolor(7);

    gotoxy((uint8_t)x, (uint8_t)y);
    putchar((char)219);

    resetbgcolor();
}

static uint8_t overlap_point_in_player(int32_t px, int32_t py, int32_t x, int32_t y)
{
    /* 4x4 sprite */
    return (x >= px && x <= px + 3 && y >= py && y <= py + 3);
}

static void spawn_powerup(Bounds *bounds)
{


    int32_t x = (int32_t)(bounds->min_x + (lcg_next() % (uint32_t)(bounds->max_x - bounds->min_x + 1)));


    uint32_t r = lcg_next();
    g_pu.type = ((r >> 16) & 2) ? POWERUP_TRIPLE_SHOT : POWERUP_AUTO_FAST;

    g_pu.active = 1;
    g_pu.x = clamp_i32(x, bounds->min_x, bounds->max_x);
    g_pu.y = bounds->min_y;

    powerup_draw(g_pu.type, g_pu.x, g_pu.y);
}

void powerups_init(void)
{
    g_pu.active = 0;
    g_pu.type = POWERUP_NONE;
    g_pu.x = 0;
    g_pu.y = 0;

    g_triple_until_hs[1] = g_triple_until_hs[2] = 0;
    g_autofast_until_hs[1] = g_autofast_until_hs[2] = 0;

    g_pu.next_spawn_hs = time_now_hs() + 200u; /* ~2s */
}

uint8_t powerup_triple_active(uint8_t player)
{
    if (player < 1 || player > 2) return 0;
    uint32_t now = time_now_hs();
    return ((int32_t)(g_triple_until_hs[player] - now) > 0);
}

uint8_t powerup_autofast_active(uint8_t player)
{
    if (player < 1 || player > 2) return 0;
    uint32_t now = time_now_hs();
    return ((int32_t)(g_autofast_until_hs[player] - now) > 0);
}

void powerups_update(P1 *p1, P2 *p2, Bounds *bounds)
{
    uint32_t now = time_now_hs();

    if (!g_pu.active) {
        if ((int32_t)(now - g_pu.next_spawn_hs) >= 0) {
            spawn_powerup(bounds);
        }
        return;
    }

    static uint8_t move_div = 0;
    move_div++;
    if (move_div < 10) {
        powerup_draw(g_pu.type, g_pu.x, g_pu.y);
        return;
    }
    move_div = 0;

    powerup_erase(g_pu.x, g_pu.y);
    g_pu.y += 1;

    if (g_pu.y > bounds->max_y) {
        g_pu.active = 0;
        g_pu.type = POWERUP_NONE;
        g_pu.next_spawn_hs = now + 400u;
        return;
    }

    if (overlap_point_in_player(p1->x, p1->y, g_pu.x, g_pu.y)) {
        if (g_pu.type == POWERUP_TRIPLE_SHOT) g_triple_until_hs[1] = now + 500u;
        if (g_pu.type == POWERUP_AUTO_FAST)   g_autofast_until_hs[1] = now + 500u;
        g_pu.active = 0;
        g_pu.type = POWERUP_NONE;
        g_pu.next_spawn_hs = now + 600u;
        return;
    }

    if (overlap_point_in_player(p2->x, p2->y, g_pu.x, g_pu.y)) {
        if (g_pu.type == POWERUP_TRIPLE_SHOT) g_triple_until_hs[2] = now + 500u;
        if (g_pu.type == POWERUP_AUTO_FAST)   g_autofast_until_hs[2] = now + 500u;
        g_pu.active = 0;
        g_pu.type = POWERUP_NONE;
        g_pu.next_spawn_hs = now + 600u;
        return;
    }

    powerup_draw(g_pu.type, g_pu.x, g_pu.y);
}
