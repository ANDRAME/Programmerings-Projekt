/*
 * graphics.c
 *
 *  Created on: 15. jan. 2026
 *      Author: elina
 */
#include <astro.h>
#include "ansi.h"
#include "gpio.h"
#include <stdio.h>
#include "lut.h"
#include "astro.h"





//atro drawing
void draw_astroid(int16_t x, int16_t y){
	char astRow1[] = {248,219,219,219,219, '\0'};//5 tegn
	char astRow2[] = {219,219,219,219,219,219,219, '\0'}; // 8 tegn
	char astRow3[] = {219,219,219,219,219,219,219,219,219,248,'\0'}; //9 tegn
	char astRow4[] = {219,219,219,219,219,219,219,219,219,219,'\0'};
	char astRow5[] = {219,219,219,219,219,219,219, '\0'};

	//the color

	fgcolor(7); // Set colour to red


	//row 1
	gotoxy( x+2,  y);
	printf("%s", astRow1);

	//row 2

	gotoxy(x+2,y+1);
	printf("%s", astRow2);

	//row 3

	gotoxy(x+1, y+2);
	printf("%s", astRow3);

	//row 4
	gotoxy(x, y+3);
	printf("%s", astRow4);

	gotoxy(x+1, y+4);
	printf("%s", astRow5);




	printf("\x1B[0m");

}


static Astroid astro[MAX_ASTROIDS];


void initAst (){ // puts all asts to 0(inactive)
	for (uint8_t i=0; i<MAX_ASTROIDS; i++){
		astro[i].active = 0;
	}
}

void spawnAstro(uint8_t grid_width){ //hvor stor gridth er
	for (uint8_t i=0; i<MAX_ASTROIDS; i++){

		if (!astro[i].active){
			astro[i].x =rand() % (grid_width-ASTROID_WIDTH); //modulo, so you will be inside ur grid
			astro[i].y =0;
			astro[i].active =1; //activates it
			astro[i].speed=3; //da speed
			break; //if there were no breaks there would be 5 astroids at once

		}

	}
}

void updateAstro(uint8_t grid_height){
	for (uint8_t i=0; i<MAX_ASTROIDS; i++){

		if(astro[i].active){
			delete_astroid(&astro[i]);

			astro[i].y += astro[i].speed;

			if (astro[i].y > grid_height){
				astro[i].active=0;


			} else{
				draw_astroid(astro[i].x,astro[i].y);
			}
		}

	}

}


void delete_astroid (Astroid *astro){
	for (uint8_t i=0; i<ASTROID_HEIGHT; i++){
		gotoxy(astro->x,astro->y+i);
		printf("            ");
	}
}

Astroid* get_astroids(){
	return astro;
}
