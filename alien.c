#include "alien.h"
#include "players.h"
#include "shoot1.h"

void point_count(P1 *p1, P2 *p2)
{
    for (int i = 0; i < bullet_count; i++)
    {
        if (bullets[i].y == 6 &&
            ((bullets[i].x >= 10 && bullets[i].x <= 20) ||
             (bullets[i].x >= 45 && bullets[i].x <= 55) ||
             (bullets[i].x >= 80 && bullets[i].x <= 90)))
        {
            if (bullets[i].player == 1)      p1->pnt += 1;
            else if (bullets[i].player == 2) p2->pnt += 1;
        }
    }
}

