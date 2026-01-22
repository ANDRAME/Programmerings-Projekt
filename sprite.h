#ifndef SPRITE_H
#define SPRITE_H

#include <stdint.h>

typedef struct {
    const char **data;   // array of strings (rows)
} Spr;


void sprite_draw(int x, int y);

void sprite_erase(int x, int y);



#endif /* SPRITE_H_ */
