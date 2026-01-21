
#ifndef JOYSTICK_H_
#define JOYSTICK_H_

#include <stdint.h>


uint8_t readJoystick(void);

void joy_init(void);
uint16_t adc1_read(void);
uint16_t adc2_read(void);

#endif /* JOYSTICK_H_ */
