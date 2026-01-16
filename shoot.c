#include "shoot.h"
#include "players.h"
#include "ansi.h"

Bullet_t bullets[MAX_BULLETS];
int bullet_count = 0;

void bullet_erase_at(int32_t x, int32_t y)
{
    gotoxy(x, y);
    putchar(' ');
}

void bullet_draw_at(int32_t x, int32_t y)
{
    gotoxy(x, y);
    putchar('*');
}

void Bullets_Update(void)

{

	static uint8_t buffer = 0;
	buffer++;

	if ((buffer) >= 10) {
	    buffer = 0;
		for (int i = 0; i < bullet_count; i++)
		{
			/* erase old */
			bullet_erase_at(bullets[i].x, bullets[i].y);

			/* move up */
			switch (bullets[i].type)
			{
				case BULL_SLOW: bullets[i].y -= 1; break;
				case BULL_FAST: bullets[i].y -= 2; break;
				default:        bullets[i].y -= 2; break;
			}

			/* delete if off screen */
			if (bullets[i].y <= 2)
			{
				bullets[i] = bullets[bullet_count - 1];
				bullet_count--;
				i--;
				continue;
			}

			/* draw new */
			bullet_draw_at(bullets[i].x, bullets[i].y);
		}
	}
}

void Bullet_Spawn(int32_t shooter, P1 *p1, P2 *p2)
{
    if (bullet_count >= MAX_BULLETS)
        return;

    Bullet_t *b = &bullets[bullet_count];

    b->type   = BULL_SLOW;
    b->player = shooter;

    switch (b->player)
    {
        case 1:
            b->x = p1->x + 1;        /* optional offset: +1 etc */
            b->y = p1->y - 1;
            break;

        case 2:
            b->x = p2->x + 1;    /* your offset */
            b->y = p2->y - 1;
            break;

        default:
            return;
    }

    bullet_count++;
    bullet_draw_at(b->x, b->y);   /* draw immediately */
}
