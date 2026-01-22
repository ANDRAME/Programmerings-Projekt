#ifndef _STOPWATCH_H
#define _STOPWATCH_H

#include "timer.h"


void stopwatchPrint(time_s split1, time_s split2);
void stopwatchControl(uint8_t joyPos, uint8_t* isRunning, time_s* split1, time_s* split2);


#endif // _STOPWATCH_H

