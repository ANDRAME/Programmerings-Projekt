
#ifndef JOYSTICK_H_
#define JOYSTICK_H_

#include <stdint.h>

/* Joystick direction enum */
typedef enum
{
    JOY_NONE   = 0,
    JOY_UP     = 1,
    JOY_DOWN   = 2,
    JOY_LEFT   = 3,
    JOY_RIGHT  = 4,
    JOY_CENTER = 5
} JoystickDirection;
void joystick_init(void);
uint8_t readJoystick(void);
JoystickDirection getJoystickDirection(uint8_t state);
const char* joystickString(JoystickDirection dir);
void joy_init(void);
uint16_t adc1_read(void);
uint16_t adc2_read(void);

#endif /* JOYSTICK_H_ */
