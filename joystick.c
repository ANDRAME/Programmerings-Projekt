#include "joystick.h"
#include "stm32f30x.h"

void joy_init(void)
{
    RCC->AHBENR |= RCC_AHBPeriph_GPIOA;
    RCC->AHBENR |= RCC_AHBPeriph_GPIOC;

    /* PA0 + PA1 ordinary input */
    GPIOA->MODER &= ~((0x3U << (0*2)) | (0x3U << (1*2)));
    GPIOA->PUPDR &= ~((0x3U << (0*2)) | (0x3U << (1*2)));

    RCC->CFGR2 &= ~RCC_CFGR2_ADCPRE12;
    RCC->CFGR2 |=  RCC_CFGR2_ADCPRE12_DIV6;
    RCC->AHBENR |= RCC_AHBPeriph_ADC12;

    ADC1->CR   = 0x00000000;
    ADC1->CFGR &= 0xFDFFC007;
    ADC1->SQR1 &= ~ADC_SQR1_L;

    ADC1->CR |= 0x10000000;
    for (volatile int i = 0; i < 1000; i++) { }

    ADC1->CR |= 0x80000000;
    while (ADC1->CR & 0x80000000) { }
    for (volatile int i = 0; i < 100; i++) { }

    ADC1->CR |= 0x00000001;
    while (!(ADC1->ISR & 0x00000001)) { }

    // Set PC8 to input this the shoot
    GPIOC->MODER &= ~(0x00000003 << (8 * 2));
    GPIOC->MODER |=  (0x00000000 << (8 * 2));
    GPIOC->PUPDR &= ~(0x00000003 << (8 * 2));
    GPIOC->PUPDR |=  (0x00000000 << (8 * 2));
}

uint16_t adc1_read(void)   /* joystick X*/
{
    ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 1, ADC_SampleTime_1Cycles5); // PA0
    ADC_StartConversion(ADC1);
    while (ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == 0) { }
    return ADC_GetConversionValue(ADC1);
}

uint16_t adc2_read(void)   /* joystick Y*/
{
    ADC_RegularChannelConfig(ADC1, ADC_Channel_2, 1, ADC_SampleTime_1Cycles5); // PA1
    ADC_StartConversion(ADC1);
    while (ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == 0) { }
    return ADC_GetConversionValue(ADC1);
}



uint8_t readJoystick(void)
{
    uint8_t state = 0b00000000;

    // bit 0: 1 if joystick pressed UP (PA4), 0 otherwise
    if (adc2_read() > 3800)
        state |= (0x01 << 0);

    // bit 1: 1 if joystick pressed DOWN (PB0), 0 otherwise
    if (adc2_read() < 3200)
        state |= (0x01 << 1);

    // bit 2: 1 if joystick pressed LEFT (PC1), 0 otherwise
    if (adc1_read() < 2500)
        state |= (0x01 << 2);

    // bit 3: 1 if joystick pressed RIGHT (PC0), 0 otherwise
    if (adc1_read() > 3800)
        state |= (0x01 << 3);

    // bit 4: 1 if Button 2 is pressed (PB5), 0 otherwise
    if (GPIOC->IDR & (0x0001 << 8))
    {
    	state |= (0x01 << 4);
    }
    // bit 5-7: 0
    return state;
}


