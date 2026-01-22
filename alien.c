#include "alien.h"
#include "players.h"
#include "shoot1.h"
#include "alienspawn.h"


void point_count(P1 *p1, P2 *p2 )
{
    alienStruct *aliens = get_aliens();

    for (int i = 0; i < bullet_count; i++)
    {
        int bx = bullets[i].x;
        int by = bullets[i].y;

        // skip bullets already offscreen
        if (by > 200) continue;   // adjust if your screen height differs

        for (int j = 0; j < MAX_ALIENS; j++)
        {
            if (!aliens[j].active) continue;

            int ax = aliens[j].x;
            int ay = aliens[j].y;

            // bullet inside alien rectangle?
            if (bx >= ax && bx < ax + ALIEN_WIDTH &&
                by >= ay && by < ay + ALIEN_HEIGHT)
            {
                // award point
                if (bullets[i].player == 1)
                    p1->pnt++;
                else if (bullets[i].player == 2)
                    p2->pnt++;

                // remove alien
                delete_alien(&aliens[j]);
                aliens[j].active = 0;

                // remove bullet (invalidate it)
                bullets[i].y = 255;

                break; // bullet can only hit one alien
            }
        }
    }
}
