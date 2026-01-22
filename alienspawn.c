/*
 * alien.c
 *
 *  Created on: 16. jan. 2026
 *      Author: elina
 */
#include "alienspawn.h"
#include "ansi.h"

#include "timer.h"
#include <stdio.h>
#include <stdlib.h>


extern volatile time_s gTime;





void draw_alien(uint16_t x, uint16_t y){

	char top_ears[] = {220,'\0'};
	char bottom_ears[] ={219,'\0'};
	char forehead[] ={219,219,219,219,219,219,'\0'};
	char face1[] = {219,'\0'};
	char face2[] = {219, 219,'\0'};
	char face3[] = {223, 223, '\0'};

	//first row
	fgcolor(4);
	gotoxy(x,y);
	printf("%s", top_ears);
	gotoxy(x+5,y);
	printf("%s", top_ears);


	//second row
	gotoxy(x+1,y+1);
	printf("%s", bottom_ears);
	gotoxy(x+4,y+1);
	printf("%s", bottom_ears);

	//third row
	gotoxy(x,y+2);
	printf("%s", forehead);


	//fourth row
	gotoxy(x,y+3);
	printf("%s", face1);

	gotoxy(x+2, y+3);
	printf("%s", face2);

	gotoxy(x+5, y+3);
	printf("%s", face1);

	//fifth row

	gotoxy(x+1, y+4);
	printf("%s", face1);

	gotoxy(x+4, y+4);
	printf("%s", face1);

	//sixth row

	gotoxy(x+2, y+5);
	printf("%s", face3);


	// eyes

	fgcolor(1);
	gotoxy(x+1,y+3);
	printf("%s", face1);
	gotoxy(x+4,y+3);
	printf("%s", face1);


	//teeth
	fgcolor(15);
	gotoxy( x+2, y+4);
	printf("%s", face3);
}


static alienStruct aliens[MAX_ALIENS];


void initAlien (){ //starts by having all the aliens at 0

	for (uint8_t j=0; j<MAX_ALIENS; j++)
	{
		aliens[j].active =0;
		aliens[j].tick=0;
		aliens[j].speed= DEFAULT_SPEED;

}



}
void spawnAlien (uint8_t grid_width){ //how big the grid is
	for (uint8_t j=0; j<MAX_ALIENS; j++)
	{

		if (!aliens[j].active){ //if aliens are not active

			//uint8_t x= rand() % (grid_width-ALIEN_WIDTH); // by having these, the aliens will fak over
			aliens[j].x = rand() % (grid_width-ALIEN_WIDTH); // aliens will spawn randomly in the grid width

			aliens[j].y = 2; //where on y-axis they spawn
			aliens[j].active=1; //activates it
			break;
		}
	}
}









void delete_alien(alienStruct *aliens){
	for(uint8_t j=0; j<ALIEN_WIDTH; j++){
		gotoxy(aliens->x, aliens->y+j);
		printf("          ");
	}

}




void updateAlien(uint8_t grid_width)
{ // might have to be called grid_width

	for (uint8_t j = 0; j < MAX_ALIENS; j++)
	{
		if (aliens[j].active)
		{
			delete_alien(&aliens[j]);
			if (aliens[j].x + aliens[j].speed > (grid_width)-ALIEN_WIDTH)
			{
				aliens[j].speed =  -aliens[j].speed;
			}
			else if (aliens[j].x + aliens[j].speed <=1)
			{
				aliens[j].speed =  -aliens[j].speed;
			}
			aliens[j].x += aliens[j].speed;
			draw_alien(aliens[j].x, aliens[j].y);

		}
	}
}






void timeAlien()
{
	for (uint8_t j=0; j<MAX_ALIENS; j++){
		if (gTime.s ==0){


		}
	}
}







alienStruct* get_aliens(){
	return aliens;
}



