
#include "ansi.h"
#include "LOSEscreen.h"
#include <stdio.h>
#include "ansi.h"





void loseG(uint8_t x, uint8_t y){
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

void loseA(uint8_t x, uint8_t y){

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


void losenM(uint8_t x, uint8_t y){

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

void loseE(uint8_t x, uint8_t y){


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



void loseOVER (uint8_t, x, uint8_t y){

	char one[] = {219,'\0'};
	char three1[] = {223, 223, 223, '\0'};
	char four[] = {223, 223, 223, 223, '\0'};
	char three[] = {219, 219, 219, '\0'};


	//O
	fgcolor(1);
	gotoxy(x+1,y);
	printf("%s", three1);

	gotoxy(x,y+1);
	printf("%s", one);
	gotoxy(x,y+2);
	printf("%s", one);
	gotoxy(x,y+3);
	printf("%s", one);
	gotoxy(x,y+4);
	printf("%s", one);

	gotoxy(x+1,y+5);
	gotoxy(x,y+1);
	printf("%s", three1);

	gotoxy(x+4,y+1);
	printf("%s", one);
	gotoxy(x+4,y+2);
	printf("%s", one);
	gotoxy(x+4,y+3);
	printf("%s", one);
	gotoxy(x+4,y+4);
	printf("%s", one);


	//V
	gotoxy(x+6,y);
	printf("%s", one);
	gotoxy(x+6,y+1);
	printf("%s", one);
	gotoxy(x+6,y+2);
	printf("%s", one);
	gotoxy(x+6,y+3);
	printf("%s", one);

	gotoxy(x+7,y+4);
	printf("%s", one);

	gotoxy(x+8,y+5);
	printf("%s", one);

	gotoxy(x+9,y+4);
	printf("%s", one);

	gotoxy(x+10,y+3);
	printf("%s", one);
	gotoxy(x+10,y+2);
	printf("%s", one);
	gotoxy(x+10,y+1);
	printf("%s", one);
	gotoxy(x+10,y);
	printf("%s", one);

	//E

	gotoxy(x+12,y);
	printf("%s", four);
	gotoxy(x+12,y+1);
	printf("%s", one);
	gotoxy(x+12,y+2);
	printf("%s", one);

	gotoxy(x+12,y+3);
	printf("%s", three);

	gotoxy(x+12,y+4);
	printf("%s", one);

	gotoxy(x+12,y+5);
	printf("%s", four);


	//R

	gotoxy(x+17,y);
	printf("%s", three);

	gotoxy(x+17,y+1);
	printf("%s", one);

	gotoxy(x+17,y+2);
	printf("%s", one);

	gotoxy(x+17,y+3);
	printf("%s", three1);

	gotoxy(x+17,y+4);
	printf("%s", one);

	gotoxy(x+17,y+5);
	printf("%s", one);

	gotoxy(x+20,y+1);
	printf("%s", one);

	gotoxy(x+20,y+2);
	printf("%s", one);

	gotoxy(x+20,y+4);
	printf("%s", one);

	gotoxy(x+12,y+5);
	printf("%s", one);
}





