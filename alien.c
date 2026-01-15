#include "alien.h"
#include "players.h"
#include "shoot.h"

void point_count(void)
{
    for (int i = 0; i < bullet_count; i++)
    {
    	if (bullets[i].y == 3 &&
    	    (
    	        (bullets[i].x >= 10 && bullets[i].x <= 20) ||
    	        (bullets[i].x >= 45 && bullets[i].x <= 55) ||
    	        (bullets[i].x >= 80 && bullets[i].x <= 90)
    	    ))
    	{
    	    if (bullets[i].player == 1)
    	    {
    	        P1_player.pnt += 1;
    	    }
    	    else if (bullets[i].player == 2)
    	    {
    	        P2_player.pnt += 1;
    	    }
    	}


        }
 }

