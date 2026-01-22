#include "stopwatch.h"
#include "ansi.h"
#include "gpio.h"

/*
 * void stopwatchPrint(time_s split1, time_s split2){
	gotoxy(10,10);

	printf("STOPWATCH\n\n");



	printf("Time since start:  %02d:%02d:%02d\n", gTime.m, gTime.s, gTime.hs);
	printf("Split time 1:      %02d:%02d:%02d\n", split1.m, split1.s, split1.hs);
	printf("Split time 2:      %02d:%02d:%02d\n", split2.m, split2.s, split2.hs);
}

void stopwatchControl(uint8_t joyPos, uint8_t* isRunning, time_s* split1, time_s* split2){

	switch (joyPos){

		case JOY_DOWN:

			resetTime();

			break;

		case JOY_LEFT:
			 //det fra gtime ind i split1
			split1->hs = gTime.hs;
			split1->s = gTime.s;


			break;

		case JOY_RIGHT:

			split2->hs=gTime.hs;
			split2->s=gTime.s;

			break;

		case JOY_CENTER:
			if (*isRunning == 1){
				stopTimer();
				*isRunning=0;
			}else {
				startTimer();
				*isRunning =1;
			}
			break;

		default:
			break;
		}
}
*/
