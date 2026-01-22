/*
 * gpio.h
 *
 *  Created on: 9. jan. 2026
 *      Author: elina
 */

#ifndef GPIO_H_
#define GPIO_H_
#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h" // Input/output library for this course

#define COLOR_RED ( 0b00000001 )

// Read joystick and output as one hot encoded [0 0 0 CEBTER RIGHT LEFT DOWN UP]
#define JOY_UP     (0b00000001)
#define JOY_DOWN   (0b00000010)
#define JOY_LEFT   (0b00000100)
#define JOY_RIGHT  (0b00001000)
#define JOY_CENTER (0b00010000)











void ledInit();
void setLed(uint8_t color);
void joyInit();
void ledInit();
void joyLed(uint8_t direction);
uint8_t readJoystick();

#endif /* GPIO_H_ */
