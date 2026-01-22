#define ESC 0x1B
#define rows 20
#define side 30
#include "ansi.h"
#include <string.h>
#include "lut.h"



void fgcolor(uint8_t foreground) {
/*  Value      foreground     Value     foreground
    ------------------------------------------------
      0        Black            8       Dark Gray
      1        Red              9       Light Red
      2        Green           10       Light Green
      3        Brown           11       Yellow
      4        Blue            12       Light Blue
      5        Purple          13       Light Purple
      6        Cyan            14       Light Cyan
      7        Light Gray      15       White
*/
  uint8_t type = 22;             // normal text
	if (foreground > 7) {
	  type = 1;                // bold text
		foreground -= 8;
	}
  printf("%c[%d;%dm", ESC, type, foreground+30);
}

void bgcolor(uint8_t background) {
/* IMPORTANT:   When you first use this function you cannot get back to true white background in HyperTerminal.
   Why is that? Because ANSI does not support true white background (ANSI white is gray to most human eyes).
                The designers of HyperTerminal, however, preferred black text on white background, which is why
                the colors are initially like that, but when the background color is first changed there is no
 	              way comming back.
   Hint:        Use resetbgcolor(); clrscr(); to force HyperTerminal into gray text on black background.

    Value      Color
    ------------------
      0        Black
      1        Red
      2        Green
      3        Brown
      4        Blue
      5        Purple
      6        Cyan
      7        Gray
*/
  printf("%c[%dm", ESC, background+40);
}

void color(uint8_t foreground, uint8_t background) {
// combination of fgcolor() and bgcolor() - uses less bandwidth
  uint8_t type = 22;             // normal text
	if (foreground > 7) {
	  type = 1;                // bold text
		foreground -= 8;
	}
  printf("%c[%d;%d;%dm", ESC, type, foreground+30, background+40);
}

void resetbgcolor() {
// gray on black text, no underline, no blink, no reverse
  printf("%c[m", ESC);
}


void clrscr(void) {
	printf("%c[2J", ESC);
}




void clrcur(void) {
	printf("\x1b[?251");
}



void clreol() {
	printf("%c[2K", ESC);

}




void gotoxy(uint8_t x, uint8_t y){

	printf("%c[%d;%dH", ESC, y,x);
}


void underline (uint8_t on) {

	printf("%c[%cm", ESC, on? 04:24);
}



void blink (uint8_t light){
	printf("%c[%dm", ESC, light? 05:25);
}


void inverse (uint8_t inv){
	printf("%c[%c;%d;%dm", ESC, inv==1, inv==0, inv? 7:27);
}







void windwow(int x1, int y1, int x2, int y2, char text[])
{
    int length  = x2 - x1;
    int height = y2 - y1;

    int startpoint=(length/2) - ((strlen(text))/2); //strlen, ignorerer usynlige karakter som sizeof ser

// vil vide hvor midten af boxen er, så dividere med 2, da der vil komme et offsetm så minusser vi med offsettet
 // texten kommer til at være forskydt så der bliver justeret for offsettet ved at dividere længden af "text" i halv (papir analogi)




    for (int i = 0; i < length; i++) { // vores for loop, startet ved i=0, mens i er mindre end længden så plus til i

    	if (i==startpoint){ //hvis i og startpoint er det samme

    		printf("%s",text); //så kan vi printe texten

    		i= i+strlen(text); //nu når vi har printet texten, har vi printet flere karater end normalt, så skal springe nogle "-" over, så derfor sætter vi den til at være ækvivalent


    		}else{
    			printf("%c",196);

    		}




    }
    printf("\n");




    for (int j = 0; j < height - 1; j++) {
        printf("%c",179);
        for (int i = 0; i < length - 2; i++) {
            printf(" ");
        }
        printf("%c\n",179);
    }





    for (int i = 0; i < length; i++) {
        printf("%c",196);
    }
    printf("\n");
}


























