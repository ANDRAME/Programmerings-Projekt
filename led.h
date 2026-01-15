#ifndef LED_H_
#define LED_H_

typedef enum
{
    LED_OFF = 0,
    LED_RED,
    LED_GREEN,
    LED_BLUE,
    LED_YELLOW,
    LED_CYAN,
    LED_MAGENTA,
    LED_WHITE
} LedColor;

void setLED(LedColor);

void led_init(void);

void joystickToLed(void);

#endif /* LED_H_ */
