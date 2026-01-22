/*
 * alien.h
 *
 *  Created on: 16. jan. 2026
 *      Author: elina
 */

#ifndef ALIENSPAWN_H_
#define ALIENSPAWN_H_
#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h" // Input/output library for this course
#define MAX_ALIENS 5
#define ALIEN_HEIGHT 6
#define ALIEN_WIDTH 6
#define DEFAULT_SPEED 2
#define MOVE_TICKS 1000


typedef struct{
	int16_t x,y;
	int16_t active;
	int16_t speed;
	int16_t tick;
	int16_t dx;
	int16_t dy;
}alienStruct;

void draw_alien(uint16_t x, uint16_t y);
void initAlien();
void spawnAlien(uint8_t grid_width);

void delete_alien(alienStruct *aliens);
void updateAlien(uint8_t grid_width, uint8_t *bounce);



#endif /* ALIEN_H_ */
