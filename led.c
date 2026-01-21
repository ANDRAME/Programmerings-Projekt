#include "led.h"
#include "30010_io.h"
#include "stm32f30x.h"
#include "joystick.h"

#define LED_RED_PORT    GPIOB
#define LED_RED_PIN     4

#define LED_GREEN_PORT  GPIOC
#define LED_GREEN_PIN   7

#define LED_BLUE_PORT   GPIOA
#define LED_BLUE_PIN    9


void led_init(void)
{
    // Enable clock for GPIO Port A, B, C
    RCC->AHBENR |= RCC_AHBPeriph_GPIOA;
    RCC->AHBENR |= RCC_AHBPeriph_GPIOB;
    RCC->AHBENR |= RCC_AHBPeriph_GPIOC;

    /*********************/
    /* PA9 as output     */
    /*********************/
    GPIOA->OSPEEDR &= ~(0x00000003 << (9 * 2));   // Clear speed register
    GPIOA->OSPEEDR |=  (0x00000002 << (9 * 2));   // Set speed register (0x02)

    GPIOA->OTYPER  &= ~(0x0001 << 9);            // Clear output type register
    GPIOA->OTYPER  |=  (0x0000 << 9);            // Set output type (0x00 - Push pull)

    GPIOA->MODER   &= ~(0x00000003 << (9 * 2));  // Clear mode register
    GPIOA->MODER   |=  (0x00000001 << (9 * 2));  // Set mode (0x01 - Output)

    GPIOA->PUPDR   &= ~(0x00000003 << (9 * 2));  // Clear pull register
    GPIOA->PUPDR   |=  (0x00000000 << (9 * 2));  // No pull

    /*********************/
    /* PC7 as output     */
    /*********************/
    GPIOC->OSPEEDR &= ~(0x00000003 << (7 * 2));
    GPIOC->OSPEEDR |=  (0x00000002 << (7 * 2));

    GPIOC->OTYPER  &= ~(0x0001 << 7);
    GPIOC->OTYPER  |=  (0x0000 << 7);

    GPIOC->MODER   &= ~(0x00000003 << (7 * 2));
    GPIOC->MODER   |=  (0x00000001 << (7 * 2));

    GPIOC->PUPDR   &= ~(0x00000003 << (7 * 2));
    GPIOC->PUPDR   |=  (0x00000000 << (7 * 2));

    /*********************/
    /* PB4 as output     */
    /*********************/
    GPIOB->OSPEEDR &= ~(0x00000003 << (4 * 2));
    GPIOB->OSPEEDR |=  (0x00000002 << (4 * 2));

    GPIOB->OTYPER  &= ~(0x0001 << 4);
    GPIOB->OTYPER  |=  (0x0000 << 4);

    GPIOB->MODER   &= ~(0x00000003 << (4 * 2));
    GPIOB->MODER   |=  (0x00000001 << (4 * 2));

    GPIOB->PUPDR   &= ~(0x00000003 << (4 * 2));
    GPIOB->PUPDR   |=  (0x00000000 << (4 * 2));
}



void setLED(LedColor color)
{
    // Clear all LED outputs
	// Turn all LEDs OFF initially (active-low)
	LED_RED_PORT->ODR   |= (1 << LED_RED_PIN);
	LED_GREEN_PORT->ODR |= (1 << LED_GREEN_PIN);
	LED_BLUE_PORT->ODR  |= (1 << LED_BLUE_PIN);


    switch (color)
    {
        case LED_RED:
            LED_RED_PORT->ODR &= ~(1 << LED_RED_PIN);
            break;

        case LED_GREEN:
            LED_GREEN_PORT->ODR &= ~(1 << LED_GREEN_PIN);
            break;

        case LED_BLUE:
            LED_BLUE_PORT->ODR &= ~(1 << LED_BLUE_PIN);
            break;

        case LED_YELLOW:   // red + green
            LED_RED_PORT->ODR   &= ~(1 << LED_RED_PIN);
            LED_GREEN_PORT->ODR &= ~(1 << LED_GREEN_PIN);
            break;

        case LED_CYAN:     // green + blue
            LED_GREEN_PORT->ODR &= ~(1 << LED_GREEN_PIN);
            LED_BLUE_PORT->ODR  &= ~(1 << LED_BLUE_PIN);
            break;

        case LED_MAGENTA:  // red + blue
            LED_RED_PORT->ODR  &= ~(1 << LED_RED_PIN);
            LED_BLUE_PORT->ODR &= ~(1 << LED_BLUE_PIN);
            break;

        case LED_WHITE:    // red + green + blue
            LED_RED_PORT->ODR   &= ~(1 << LED_RED_PIN);
            LED_GREEN_PORT->ODR &= ~(1 << LED_GREEN_PIN);
            LED_BLUE_PORT->ODR  &= ~(1 << LED_BLUE_PIN);
            break;

        case LED_OFF:
        default:
            // already off
            break;
    }
}

/*
void joystickToLed(void)
{
    uint8_t state = readJoystick();
    JoystickDirection dir = getJoystickDirection(state);

    switch (dir)
    {
        case JOY_UP:
            setLED(LED_RED);
            break;

        case JOY_DOWN:
            setLED(LED_BLUE);
            break;

        case JOY_LEFT:
            setLED(LED_GREEN);
            break;

        case JOY_RIGHT:
            setLED(LED_YELLOW);
            break;

        case JOY_CENTER:
            setLED(LED_WHITE);
            break;

        case JOY_NONE:
        default:
            setLED(LED_OFF);
            break;
    }
}
*/
