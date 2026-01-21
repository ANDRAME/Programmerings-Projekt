#ifndef GAME_H_
#define GAME_H_

#include "players.h"   // <-- REQUIRED (defines P1 and P2)
#include "window.h"    // <-- for WindowStyle_t

void game_init(P1 *p1, P2 *p2, WindowStyle_t *style);
void game_update_hearts(P1 *p1, P2 *p2);
void game_update_points(P1 *p1, P2 *p2);


#endif /* GAME_H_ */
