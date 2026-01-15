#include "30010_io.h"
#include "timer.h"
#include "stm32f30x.h"


void setupTimer(void)
{
    RCC->APB2ENR |= RCC_APB2Periph_TIM15; // Enable clock line to timer 15

    TIM15->CR1  = 0x0000;     // stop timer while configuring
    TIM15->ARR  = 63999;      // (keep your values if they already give 100 Hz)
    TIM15->PSC  = 9;
    TIM15->EGR  = 0x0001;     // load PSC/ARR
    TIM15->DIER |= 0x0001;    // update interrupt enable

    NVIC_SetPriority(TIM1_BRK_TIM15_IRQn, 0);
    NVIC_EnableIRQ(TIM1_BRK_TIM15_IRQn);

    TIM15->CR1  |= 0x0001;    // start timer
}

void TIM1_BRK_TIM15_IRQHandler(void)
{
    if (TIM15->SR & 0x0001) {
        TIM15->SR &= ~0x0001; // clear interrupt flag

        Time.hs++;
        if (Time.hs >= 100) {
            Time.hs = 0;
            Time.s++;
            if (Time.s >= 60) {
                Time.s = 0;
                Time.m++;
                if (Time.m >= 60) {
                    Time.m = 0;
                    Time.h++;
                    if (Time.h >= 24) {
                        Time.h = 0;
                    }
                }
            }
        }
    }
}
