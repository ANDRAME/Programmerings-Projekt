
#ifndef KEYBOARD_H_
#define KEYBOARD_H_

typedef enum
{
    JOY_NONE2   = 0,
    JOY_UP2     = 1,
    JOY_DOWN2   = 2,
    JOY_LEFT2   = 3,
    JOY_RIGHT2  = 4,
    JOY_CENTER2 = 5,
	JOY_SHOOT2  = 6
} JoystickDirection2;
uint8_t readJoystick2(void);
JoystickDirection2 uart_getJoystickDirection(void);
const char* joystickString2(JoystickDirection2 dir2);


#endif /* KEYBOARD_H_ */
