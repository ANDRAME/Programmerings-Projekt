#ifndef BALL_H_
#define BALL_H_

#include <stdint.h>

typedef struct {
    uint8_t x1, y1, x2, y2;   // inclusive border coords
} Bounds_t;

typedef struct {
    int32_t x, y;             // 16.16 position
    int32_t vx, vy;           // 16.16 velocity
} Ball_t;

int bounce_out(Ball_t *b, const Bounds_t *w);
int bounce_in(Ball_t *b, const Bounds_t *w);
int Ball_step(Ball_t *b, const Bounds_t *outer, const Bounds_t *inner);


#endif
