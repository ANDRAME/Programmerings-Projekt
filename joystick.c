#include "joystick.h"
#include "stm32f30x.h"

/*
 * Joystick mapping (from schematic):
 * UP     -> PA4
 * DOWN   -> PB0
 * LEFT   -> PC1
 * RIGHT  -> PC0
 * CENTER -> PB5
 */

void joystick_init(void)
{
    // Enable clock for GPIO Port A, B, C
    RCC->AHBENR |= RCC_AHBPeriph_GPIOA;
    RCC->AHBENR |= RCC_AHBPeriph_GPIOB;
    RCC->AHBENR |= RCC_AHBPeriph_GPIOC;

    // Set PA4 to input
    GPIOA->MODER &= ~(0x00000003 << (4 * 2));  // Clear mode register
    GPIOA->MODER |=  (0x00000000 << (4 * 2));  // Set mode register (0x00 - Input)
    GPIOA->PUPDR &= ~(0x00000003 << (4 * 2));  // Clear push/pull register
    GPIOA->PUPDR |=  (0x00000000 << (4 * 2));  // Set push/pull register (0x00 - No pull)

    // Set PB0 to input
    GPIOB->MODER &= ~(0x00000003 << (0 * 2));
    GPIOB->MODER |=  (0x00000000 << (0 * 2));
    GPIOB->PUPDR &= ~(0x00000003 << (0 * 2));
    GPIOB->PUPDR |=  (0x00000000 << (0 * 2));

    // Set PC1 to input
    GPIOC->MODER &= ~(0x00000003 << (1 * 2));
    GPIOC->MODER |=  (0x00000000 << (1 * 2));
    GPIOC->PUPDR &= ~(0x00000003 << (1 * 2));
    GPIOC->PUPDR |=  (0x00000000 << (1 * 2));

    // Set PC0 to input
    GPIOC->MODER &= ~(0x00000003 << (0 * 2));
    GPIOC->MODER |=  (0x00000000 << (0 * 2));
    GPIOC->PUPDR &= ~(0x00000003 << (0 * 2));
    GPIOC->PUPDR |=  (0x00000000 << (0 * 2));

    // Set PB5 to input
    GPIOB->MODER &= ~(0x00000003 << (5 * 2));
    GPIOB->MODER |=  (0x00000000 << (5 * 2));
    GPIOB->PUPDR &= ~(0x00000003 << (5 * 2));
    GPIOB->PUPDR |=  (0x00000000 << (5 * 2));
}

uint8_t readJoystick(void)
{
    uint8_t state = 0;

    // bit 0: 1 if joystick pressed UP (PA4), 0 otherwise
    if (GPIOA->IDR & (0x0001 << 4))
        state |= (0x01 << 0);

    // bit 1: 1 if joystick pressed DOWN (PB0), 0 otherwise
    if (GPIOB->IDR & (0x0001 << 0))
        state |= (0x01 << 1);

    // bit 2: 1 if joystick pressed LEFT (PC1), 0 otherwise
    if (GPIOC->IDR & (0x0001 << 1))
        state |= (0x01 << 2);

    // bit 3: 1 if joystick pressed RIGHT (PC0), 0 otherwise
    if (GPIOC->IDR & (0x0001 << 0))
        state |= (0x01 << 3);

    // bit 4: 1 if joystick pressed CENTER (PB5), 0 otherwise
    if (GPIOB->IDR & (0x0001 << 5))
        state |= (0x01 << 4);

    // bit 5-7: 0
    return state;
}

JoystickDirection getJoystickDirection(uint8_t state)
{
    // Priority order
    if (state & (0x01 << 4)) return JOY_CENTER;
    if (state & (0x01 << 0)) return JOY_UP;
    if (state & (0x01 << 1)) return JOY_DOWN;
    if (state & (0x01 << 2)) return JOY_LEFT;
    if (state & (0x01 << 3)) return JOY_RIGHT;

    return JOY_NONE;
}

const char* joystickString(JoystickDirection dir)
{
    switch (dir)
    {
        case JOY_UP:     return "UP";
        case JOY_DOWN:   return "DOWN";
        case JOY_LEFT:   return "LEFT";
        case JOY_RIGHT:  return "RIGHT";
        case JOY_CENTER: return "SHOOT";
        default:         return "NONE";
    }
}
