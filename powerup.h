
#ifndef POWERUP_H_
#define POWERUP_H_

#include <stdint.h>
#include "players.h"
#include "timer.h"

typedef enum {
    POWERUP_NONE = 0,
    POWERUP_TRIPLE_SHOT = 1,   /* purple */
    POWERUP_AUTO_FAST   = 2,   /* yellow */
    POWERUP_INVINCIBLE  = 3    /* blue - NEW */
} PowerupType_t;

void powerups_init(void);

/* Call every frame/tick */
void powerups_update(P1 *p1, P2 *p2, Bounds *bounds);

/* Effects */
uint8_t powerup_triple_active(uint8_t player);
uint8_t powerup_autofast_active(uint8_t player);
uint8_t powerup_invincible_active(uint8_t player);  /* NEW */

#endif /* POWERUP_H_ */
