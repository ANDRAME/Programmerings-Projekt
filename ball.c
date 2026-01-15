#include "Ball.h"

int bounce_out(Ball_t *b, const Bounds_t *w)
{
    int bounced = 0;

    int32_t left   = ((int32_t)w->x1 + 1) << 16;
    int32_t right  = ((int32_t)w->x2 - 1) << 16;
    int32_t top    = ((int32_t)w->y1 + 1) << 16;
    int32_t bottom = ((int32_t)w->y2 - 1) << 16;

    if (b->x < left)  { b->x = left;  b->vx = -b->vx; bounced = 1; }
    if (b->x > right) { b->x = right; b->vx = -b->vx; bounced = 1; }
    if (b->y < top)   { b->y = top;   b->vy = -b->vy; bounced = 1; }
    if (b->y > bottom){ b->y = bottom;b->vy = -b->vy; bounced = 1; }

    return bounced;
}

int bounce_in(Ball_t *b, const Bounds_t *w)
{
    int bounced = 0;

    int32_t left   = ((int32_t)w->x1) << 16;
    int32_t right  = ((int32_t)w->x2) << 16;
    int32_t top    = ((int32_t)w->y1) << 16;
    int32_t bottom = ((int32_t)w->y2) << 16;

    int32_t nx = b->x + b->vx;
    int32_t ny = b->y + b->vy;

    if (!(nx >= left && nx <= right && ny >= top && ny <= bottom)) {
        return 0;
    }

    if (b->x < left && nx >= left) {
        b->vx = -b->vx;
        nx = left - (1 << 16);
        bounced = 1;
    } else if (b->x > right && nx <= right) {
        b->vx = -b->vx;
        nx = right + (1 << 16);
        bounced = 1;
    }

    if (b->y < top && ny >= top) {
        b->vy = -b->vy;
        ny = top - (1 << 16);
        bounced = 1;
    } else if (b->y > bottom && ny <= bottom) {
        b->vy = -b->vy;
        ny = bottom + (1 << 16);
        bounced = 1;
    }

    b->x = nx;
    b->y = ny;
    return bounced;
}

int Ball_step(Ball_t *b, const Bounds_t *outer, const Bounds_t *inner)
{
    // move
    b->x += b->vx;
    b->y += b->vy;

    int bounces = 0;
    bounces += bounce_out(b, outer);
    bounces += bounce_in(b, inner);

    return bounces;
}
