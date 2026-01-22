/*
 * gpio.c
 *
 *  Created on: 9. jan. 2026
 *      Author: elina
 */
#include "gpio.h"
#include <stdint.h>


void setupJoystick0(void){
	RCC->AHBENR |= RCC_AHBPeriph_GPIOA; // Enable clock for GPIO Port A
	 // Set pin PA0 to input
	 GPIOA->MODER &= ~(0x00000003 << (4 * 2)); // Clear mode register
	 GPIOA->MODER |= (0x00000000 << (4 * 2)); // Set mode register (0x00 – Input, 0x01 - Output, 0x02 - Alternate Function, 0x03 - Analog in/out)
	 GPIOA->PUPDR &= ~(0x00000003 << (4 * 2)); // Clear push/pull register
	 GPIOA->PUPDR |= (0x00000002 << (4 * 2)); // Set push/pull register (0x00 - No pull, 0x01 - Pull-up, 0x02 - Pull-down)

}

uint8_t readJoy0(void){
	uint8_t out = 0;
	out |= (GPIOA->IDR & (0x0001 << 4))>>4; //being shifted
	return out;
}




void setupJoystick1(void){
	RCC->AHBENR |= RCC_AHBPeriph_GPIOB; // Enable clock for GPIO Port B




	 // Set pin PB0 to input
	 GPIOB->MODER &= ~(0x00000003 << (0 * 2)); // Clear mode register
	 GPIOB->MODER |= (0x00000000 << (0 * 2)); // Set mode register (0x00 – Input, 0x01 - Output, 0x02 - Alternate Function, 0x03 - Analog in/out)
	 GPIOB->PUPDR &= ~(0x00000003 << (0 * 2)); // Clear push/pull register
	 GPIOB->PUPDR |= (0x00000002 << (0 * 2)); // Set push/pull register (0x00 - No pull, 0x01 - Pull-up, 0x02 - Pull-down)

}

uint8_t readJoy1(void){
	uint8_t out1 = 0;
	out1 |= (GPIOB->IDR & (0x0001 << 0)); //being shifted

	return out1;
}







void setupJoystick2(void){
	RCC->AHBENR |= RCC_AHBPeriph_GPIOC; // Enable clock for GPIO Port C




	 // Set pin PC1 to input
	 GPIOC->MODER &= ~(0x00000003 << (1 * 2)); // Clear mode register
	 GPIOC->MODER |= (0x00000000 << (1 * 2)); // Set mode register (0x00 – Input, 0x01 - Output, 0x02 - Alternate Function, 0x03 - Analog in/out)
	 GPIOC->PUPDR &= ~(0x00000003 << (1 * 2)); // Clear push/pull register
	 GPIOC->PUPDR |= (0x00000002 << (1 * 2)); // Set push/pull register (0x00 - No pull, 0x01 - Pull-up, 0x02 - Pull-down)

}

uint8_t readJoy2(void){
	uint8_t out2 = 0;
	out2 |= (GPIOC->IDR & (0x0001 << 1))>>1; //being shifted

	return out2;
}









void setupJoystick3(void){
	RCC->AHBENR |= RCC_AHBPeriph_GPIOC; // Enable clock for GPIO Port B




	 // Set pin PA0 to input
	 GPIOC->MODER &= ~(0x00000003 << (0 * 2)); // Clear mode register
	 GPIOC->MODER |= (0x00000000 << (0 * 2)); // Set mode register (0x00 – Input, 0x01 - Output, 0x02 - Alternate Function, 0x03 - Analog in/out)
	 GPIOC->PUPDR &= ~(0x00000003 << (0 * 2)); // Clear push/pull register
	 GPIOC->PUPDR |= (0x00000002 << (0 * 2)); // Set push/pull register (0x00 - No pull, 0x01 - Pull-up, 0x02 - Pull-down)

}

uint8_t readJoy3(void){
	uint8_t out3 = 0;
	out3 |= (GPIOC->IDR & (0x0001 << 0)); //being shifted

	return out3;
}








void setupJoystick4(void){
	RCC->AHBENR |= RCC_AHBPeriph_GPIOB; // Enable clock for GPIO Port B




	 // Set pin PA0 to input
	 GPIOB->MODER &= ~(0x00000003 << (5 * 2)); // Clear mode register
	 GPIOB->MODER |= (0x00000000 << (5 * 2)); // Set mode register (0x00 – Input, 0x01 - Output, 0x02 - Alternate Function, 0x03 - Analog in/out)
	 GPIOB->PUPDR &= ~(0x00000003 << (5 * 2)); // Clear push/pull register
	 GPIOB->PUPDR |= (0x00000002 << (5 * 2)); // Set push/pull register (0x00 - No pull, 0x01 - Pull-up, 0x02 - Pull-down)

}

uint8_t readJoy4(void){
	uint8_t out4 = 0;
	out4 |= (GPIOB->IDR & (0x0001 << 5))>>5; //being shifted

	return out4;
}

// Setup all joystick GPIO
void setupAllJoy()
{
	setupJoystick0();
	setupJoystick1();
	setupJoystick2();
	setupJoystick3();
	setupJoystick4();

}

uint8_t READJoystick(){
// Read joystick and output as one hot encoded [0 0 0 CEBTER RIGHT LEFT DOWN UP]

	uint8_t out=0;

	out |= (readJoy0() << 0); // UP
	out |= (readJoy1() << 1); // DOWN
	out |= (readJoy2() << 2); // LEFT
	out |= (readJoy3() << 3); // RIGHT
	out |= (readJoy4() << 4); // CENTER


	return out;

}









void ledInit()
{
	RCC->AHBENR |= RCC_AHBPeriph_GPIOA; // Enable clock for GPIO Port A
	RCC->AHBENR |= RCC_AHBPeriph_GPIOB; // Enable clock for GPIO Port B
	RCC->AHBENR |= RCC_AHBPeriph_GPIOC; // Enable clock for GPIO Port C

	// Set pin PA1 to output -BLUE
		 GPIOA->OSPEEDR &= ~(0x00000003 << (9 * 2)); // Clear speed register
		 GPIOA->OSPEEDR |= (0x00000002 << (9 * 2)); // set speed register (0x01 - 10 MHz, 0x02 - 2 MHz, 0x03 - 50 MHz)
		 GPIOA->OTYPER &= ~(0x0001 << (9 * 1));  // Clear output type register
		 GPIOA->OTYPER |= (0x0000 << (9)); // Set output type register (0x00 -Push pull, 0x01 - Open drain)
		 GPIOA->MODER &= ~(0x00000003 << (9 * 2)); // Clear mode register
		 GPIOA->MODER |= (0x00000001 << (9 * 2)); // Set mode register (0x00 – Input, 0x01 - Output, 0x02 - Alternate Function, 0x03 - Analog in/out)




		 // Set pin PB4 - RED
		 GPIOB->OSPEEDR &= ~(0x00000003 << (4 * 2)); // Clear speed register
		 GPIOB->OSPEEDR |= (0x00000002 << (4 * 2)); // set speed register (0x01 - 10 MHz, 0x02 - 2 MHz, 0x03 - 50 MHz)
		 GPIOB->OTYPER &= ~(0x0001 << (4 * 1));  // Clear output type register
		 GPIOB->OTYPER |= (0x0000 << (4)); // Set output type register (0x00 -Push pull, 0x01 - Open drain)
		 GPIOB->MODER &= ~(0x00000003 << (4 * 2)); // Clear mode register
		 GPIOB->MODER |= (0x00000001 << (4 * 2)); // Set mode register (0x00 – Input, 0x01 - Output, 0x02 - Alternate Function, 0x03 - Analog in/out)

		 // Set pin PC7 - GREEN
		 GPIOC->OSPEEDR &= ~(0x00000003 << (7 * 2)); // Clear speed register
		 GPIOC->OSPEEDR |= (0x00000002 << (7 * 2)); // set speed register (0x01 - 10 MHz, 0x02 - 2 MHz, 0x03 - 50 MHz)
		 GPIOC->OTYPER &= ~(0x0001 << (7 * 1));  // Clear output type register
		 GPIOC->OTYPER |= (0x0000 << (7)); // Set output type register (0x00 -Push pull, 0x01 - Open drain)
		 GPIOC->MODER &= ~(0x00000003 << (7 * 2)); // Clear mode register
		 GPIOC->MODER |= (0x00000001 << (7 * 2)); // Set mode register (0x00 – Input, 0x01 - Output, 0x02 - Alternate Function, 0x03 - Analog in/out)



}

void setLed(uint8_t color){
	// color er one hot encoded 0bxxxxxBGR, hvor x er don't care

	// Turn off all LEDs
	GPIOA->ODR |= (0x0001 << 9); //Set pin PA1 to high
	GPIOB->ODR |= (0x0001 << 4); //Set pin PB4 to high
	GPIOC->ODR |= (0x0001 << 7); //Set pin PC7 to high
	//sætter LEDs på high så man ikke skal gøre det for hver case

	switch (color){
	case 0b00000000:
		// Already turned off above
		break;
	case 0b00000001: // RED
		GPIOB->ODR &= ~(0x0001 << 4); //Set pin PB4 to low
		break;
	case 0b00000010: // GREEN
		GPIOC->ODR &= ~(0x0001 << 7); //Set pin PB4 to low
		break;
	case 0b00000011:
		GPIOB->ODR &= ~(0x0001 << 4); //Set pin PB4 to low
		GPIOC->ODR &= ~(0x0001 << 7); //Set pin PB4 to low
		break;
	case 0b00000100: //BLUE
		GPIOA->ODR &= ~(0x0001 << 9); //Set pin PB4 to low
		break;
	case 0b00000101: //cool blue
		GPIOA->ODR &= ~(0x0001 << 9); //Set pin PB4 to low
		GPIOC->ODR &= ~(0x0001 << 7); //Set pin PB4 to low
		break;
	case 0b00000110:
		GPIOA->ODR &= ~(0x0001 << 9); //Set pin PB4 to low
		GPIOC->ODR &= ~(0x0001 << 7); //Set pin PB4 to low
		GPIOB->ODR &= ~(0x0001 << 4); //Set pin PB4 to low
		break;
	default:
		break;
	}
}


void joyInit()
{

	RCC->AHBENR |= RCC_AHBPeriph_GPIOA; // Enable clock for GPIO Port A
	RCC->AHBENR |= RCC_AHBPeriph_GPIOB; // Enable clock for GPIO Port B
	RCC->AHBENR |= RCC_AHBPeriph_GPIOC; // Enable clock for GPIO Port C



	//for joystick in up direction
	GPIOA->MODER &= ~(0x00000003 << (4 * 2)); // Clear mode register
	GPIOA->MODER |= (0x00000000 << (4 * 2)); // Set mode register (0x00 – Input, 0x01 - Output, 0x02 - Alternate Function, 0x03 - Analog in/out)
	GPIOA->PUPDR &= ~(0x00000003 << (4 * 2)); // Clear push/pull register
	GPIOA->PUPDR |= (0x00000002 << (4 * 2)); // Set push/pull register (0x00 - No pull, 0x01 - Pull-up, 0x02 - Pull-down)



	 // Set pin PB0 to input
	GPIOB->MODER &= ~(0x00000003 << (0 * 2)); // Clear mode register
	GPIOB->MODER |= (0x00000000 << (0 * 2)); // Set mode register (0x00 – Input, 0x01 - Output, 0x02 - Alternate Function, 0x03 - Analog in/out)
	GPIOB->PUPDR &= ~(0x00000003 << (0 * 2)); // Clear push/pull register
	GPIOB->PUPDR |= (0x00000002 << (0 * 2)); // Set push/pull register (0x00 - No pull, 0x01 - Pull-up, 0x02 - Pull-down)


	 // Set pin PC1 to input
	GPIOC->MODER &= ~(0x00000003 << (1 * 2)); // Clear mode register
	GPIOC->MODER |= (0x00000000 << (1 * 2)); // Set mode register (0x00 – Input, 0x01 - Output, 0x02 - Alternate Function, 0x03 - Analog in/out)
	GPIOC->PUPDR &= ~(0x00000003 << (1 * 2)); // Clear push/pull register
	GPIOC->PUPDR |= (0x00000002 << (1 * 2)); // Set push/pull register (0x00 - No pull, 0x01 - Pull-up, 0x02 - Pull-down)

}


void joyLed (uint8_t direction){


	GPIOA->ODR |= (0x0001 << 9); //Set pin PA1 to high
	GPIOB->ODR |= (0x0001 << 4); //Set pin PB4 to high
	GPIOC->ODR |= (0x0001 << 7); //Set pin PC7 to high

	uint8_t out0=0;
	uint8_t out1=1;
	uint8_t out2=1;

	out0  &= ~(GPIOA->IDR & (0x0001 << 4))>>4;
	out1  &= ~(GPIOB->IDR & (0x0001 << 0));
	out2  &= ~(GPIOC->IDR & (0x0001 << 1))>>1;



	switch (direction){

	case 0b001:

		GPIOB->ODR &= ~(0x0001 << 4); //Set pin PB4 to low
		out0 |= (GPIOA->IDR & (0x0001 << 4))>>4;

		break;
	case 0b010:

		out1 |= (GPIOB->IDR & (0x0001 << 0)); //being shifted
		//green
		GPIOC->ODR &= ~(0x0001 << 7); //Set pin PB4 to low
		break;

	case 0b100:
		out2 |= (GPIOC->IDR & (0x0001 << 1))>>1; //being shifted
		GPIOA->ODR &= ~(0x0001 << 9); //Set pin PB4 to low

		break;

	default:
		break;




	}




















//uint8_t readLed(void){
	//uint8_t in=1;



	// return in;
}









/*
void setLed1(void){ //RED

	// Set pin PA1 to output
	 GPIOB->OSPEEDR &= ~(0x00000003 << (4 * 2)); // Clear speed register
	 GPIOB->OSPEEDR |= (0x00000002 << (4 * 2)); // set speed register (0x01 - 10 MHz, 0x02 - 2 MHz, 0x03 - 50 MHz)
	 GPIOB->OTYPER &= ~(0x0001 << (4 * 1));  // Clear output type register
	 GPIOB->OTYPER |= (0x0000 << (4)); // Set output type register (0x00 -Push pull, 0x01 - Open drain)
	 GPIOB->MODER &= ~(0x00000003 << (4 * 2)); // Clear mode register
	 GPIOB->MODER |= (0x00000001 << (4 * 2)); // Set mode register (0x00 – Input, 0x01 - Output, 0x02 - Alternate Function, 0x03 - Analog in/out)



}
*/

//uint8_t readLed1(void){
	//uint8_t in1=1;

	// GPIOB->ODR |= (0x0001 << 4)>>4; //Set pin PA1 to high

	// return in1;
//}








//void setLed2(void){ //

	// Set pin PC7 - GREEN
	// GPIOC->OSPEEDR &= ~(0x00000003 << (7 * 2)); // Clear speed register
	// GPIOC->OSPEEDR |= (0x00000002 << (7 * 2)); // set speed register (0x01 - 10 MHz, 0x02 - 2 MHz, 0x03 - 50 MHz)
	// GPIOC->OTYPER &= ~(0x0001 << (7 * 1));  // Clear output type register
	// GPIOC->OTYPER |= (0x0000 << (7)); // Set output type register (0x00 -Push pull, 0x01 - Open drain)
	// GPIOC->MODER &= ~(0x00000003 << (7 * 2)); // Clear mode register
	 //GPIOC->MODER |= (0x00000001 << (7 * 2)); // Set mode register (0x00 – Input, 0x01 - Output, 0x02 - Alternate Function, 0x03 - Analog in/out)





//uint8_t readLed2(void){
	//uint8_t in2=1;

	// GPIOC->ODR |= (0x0001 << 7)>>7; //Set pin PA1 to high

	 //return in2;

