#ifndef SPRITE_H
#define SPRITE_H

#include <stdint.h>

/* Sprite dimensions */
#define SPRITE_W 4
#define SPRITE_Height 4

/* Color indices */
#define SPRITE_TRANSPARENT 0

/* Function prototypes */
void sprite_draw(int x, int y);
void sprite_erase(int x, int y);

/* Optional: expose sprite data if needed elsewhere */
extern const uint8_t PLAYER1_COLORSPRITE[SPRITE_Height][SPRITE_W];

void sprite_draw(int x, int y);

void sprite_erase(int x, int y);



#endif /* SPRITE_H_ */
