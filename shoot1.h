#ifndef SHOOT_H
#define SHOOT_H

#include <stdint.h>
#include "players.h"
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
    PhysBullet_t phys;
} Bullet_t;

extern Bullet_t bullets[MAX_BULLETS];
extern int bullet_count;

void Bullets_Update(void);
void Bullet_Spawn(int32_t shooter, P1 *p1, P2 *p2);

#endif
