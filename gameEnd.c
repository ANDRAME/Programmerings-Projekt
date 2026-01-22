/*
 * gameEnd.c
 *
 *  Created on: 20. jan. 2026
 *      Author: elina
 */


#include "ansi.h"
#include "gpio.h"
#include "gameEnd.h"
#include <stdio.h>



void endScreenG(uint8_t x, uint8_t y){
	char three[] ={219,219,219,'\0'};
	char two[] = {219,219, '\0'};
	char one[] = {219,'\0'};


	//
	fgcolor(0);
	gotoxy(x+1,y);
	printf("%s", three);

	gotoxy(x,y+1);
	printf("%s", one);

	gotoxy(x,y+2);
	printf("%s", one);

	gotoxy(x,y+3);
	printf("%s", one);

	gotoxy(x+3,y+3);
	printf("%s", two);

	gotoxy(x,y+4);
	printf("%s", one);

	gotoxy(x+4,y+4);
	printf("%s", one);


	gotoxy(x+1,y+5);
	printf("%s", three);
}

void endScreenA(uint8_t x, uint8_t y){

	char two[] = {219,219, '\0'};
	char one[] = {219,'\0'};


	fgcolor(11);
	gotoxy(x+1,y);
	printf("%s", two);

	gotoxy(x,y+1);
	printf("%s", one);

	gotoxy(x,y+2);
	printf("%s", one);

	gotoxy(x+2,y+3);
	printf("%s", two);

	gotoxy(x+3,y+1);
	printf("%s", one);

	gotoxy(x+3,y+2);
	printf("%s", one);

	gotoxy(x+4,y+3);
	printf("%s", one);
}


void endScreenM(uint8_t x, uint8_t y){

	char two[] = {219,219, '\0'};
	char one[] = {219,'\0'};


	fgcolor(0);
	gotoxy(x,y);
	printf("%s", one);

	gotoxy(x,y+1);
	printf("%s", two);

	gotoxy(x,y+2);
	printf("%s", one);

	gotoxy(x,y+3);
	printf("%s", one);

	gotoxy(x+2,y+2);
	printf("%s", one);

	gotoxy(x+2,y+3);
	printf("%s", one);

	gotoxy(x+3,y+1);
	printf("%s", one);

	gotoxy(x+4,y+2);
	printf("%s", one);

	gotoxy(x+4,y+3);
	printf("%s", one);
}

void endScreenE(uint8_t x, uint8_t y){

	char one[] = {219,'\0'};
	char three[] = {219, 219, 219, '\0'};
	char one1[] = {223,'\0'};
	char three1[] = {223, 223, 223, '\0'};


	gotoxy(x+1,y);
	printf("%s", one1);

	gotoxy(x,y+1);
	printf("%s", one);

	gotoxy(x,y+2);
	printf("%s",three);

	gotoxy(x,y+3);
	printf("%s", three1);

	gotoxy(x+2, y+1);
	printf("%s", one);
}

void endScreenE_1(uint8_t x, uint8_t y){
	char three[] ={219,219,219,'\0'};
	char one[] = {219,'\0'};
	char four[] = {219, 219, 219 ,219,'\0'};

	fgcolor(4);
	gotoxy(x,y);
	printf("%s", four);

	gotoxy(x,y+1);
	printf("%s", one);

	gotoxy(x,y+2);
	printf("%s", three);

	gotoxy(x,y+3);
	printf("%s", one);

	gotoxy(x,y+4);
	printf("%s", four);

}




void endScreenN(uint8_t x, uint8_t y){

	char two[] = {219,219, '\0'};
	char one[] = {219,'\0'};

	fgcolor(4);
	gotoxy(x,y);
	printf("%s", one);

	gotoxy(x,y+1);
	printf("%s", two);

	gotoxy(x,y+2);
	printf("%s", one);

	gotoxy(x,y+3);
	printf("%s", one);

	gotoxy(x,y+4);
	printf("%s", one);

	gotoxy(x+2,y+3);
	printf("%s", one);

	gotoxy(x+3,y+3);
	printf("%s", two);

	gotoxy(x+4,y);
	printf("%s", one);

	gotoxy(x+4,y+1);
	printf("%s", one);

	gotoxy(x+4,y+2);
	printf("%s", one);

	gotoxy(x+4,y+4);
	printf("%s", one);
}

void endScreenED(uint8_t x, uint8_t y){

	char two[] = {219,219, '\0'};
	char one[] = {219,'\0'};

	fgcolor(4);
	gotoxy(x,y);
	printf("%s", two);

	gotoxy(x,y+1);
	printf("%s", one);

	gotoxy(x,y+2);
	printf("%s", one);

	gotoxy(x,y+3);
	printf("%s", one);

	gotoxy(x,y+4);
	printf("%s", two);

	gotoxy(x+2,y+1);
	printf("%s", one);

	gotoxy(x+2,y+2);
	printf("%s", one);

	gotoxy(x+2,y+3);
	printf("%s", one);
}




