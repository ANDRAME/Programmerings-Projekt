

#ifndef ASTEROID_H_
#define ASTEROID_H_

/*
 * graphics.h
 *
 *  Created on: 15. jan. 2026
 *      Author: elina
 */
#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h" // Input/output library for this course
#define MAX_ASTROIDS 30
#define ASTROID_HEIGHT 5
#define ASTROID_WIDTH 9
typedef struct{
	int16_t x,y;
	int16_t active;
	uint16_t speed;
}Astroid;

extern Astroid astro[MAX_ASTROIDS];

void updateAstro(uint8_t grid_height);
void spawnAstro(uint8_t grid_width);
void initAst ();
void draw_astroid(int16_t x, int16_t y);
void delete_astroid (Astroid *astro);

#endif /* ASTEROID_H_ */
