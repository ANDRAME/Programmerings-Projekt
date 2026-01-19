#ifndef SHOOT_H
#define SHOOT_H

#include <stdint.h>
#include "physics.h"

#define MAX_BULLETS 20

typedef enum {
    BULL_SLOW,
    BULL_FAST
} BulletType_t;

typedef struct {
    int32_t x, y;
    BulletType_t type;
    int32_t player;

    PhysBullet_t phys;   // <-- REQUIRED
} Bullet_t;

void Bullets_Update(void);
void Bullet_Spawn(int32_t shooter, struct P1 *p1, struct P2 *p2);

#endif
