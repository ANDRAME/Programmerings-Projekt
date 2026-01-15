#ifndef TRIG_H_
#define TRIG_H_

#include <stdint.h>

int32_t expand(int32_t i);
void    printFix(int32_t x);
int32_t sinus(int32_t deg);


typedef struct {
int32_t x, y;
} vector_t;

void rotateVector(vector_t *v, int32_t angle);

#endif
