#ifndef PLAYERS_H_
#define PLAYERS_H_

#include <stdint.h>

typedef struct {
    int32_t x, y;
    int32_t vx, vy;
    int32_t pnt, hlth;
} P1;

typedef struct {
    int32_t x, y;
    int32_t vx, vy;
    int32_t pnt, hlth;
} P2;

typedef struct {
    int32_t min_x, max_x;
    int32_t min_y, max_y;
} Bounds;

/* GLOBAL players */
extern P1 P1_player;
extern P2 P2_player;

void player_init(P1 *p1, P2 *p2);
void bounds_init(Bounds *bounds);
void player_step(P1 *p1, P2 *p2, Bounds *bounds);

#endif
