

#ifndef TIMER_H_
#define TIMER_H_

void setupTimer(void);
void TIM1_BRK_TIM15_IRQHandler(void);


volatile struct {
    int32_t s;             // sekond
    int32_t m;			 //minut
    int32_t h;      // hour
    int32_t hs;// hundreth s
} Time;


#endif /* TIMER_H_ */
