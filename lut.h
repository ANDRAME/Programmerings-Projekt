/** Generated using Dr LUT - Free Lookup Table Generator
  * https://github.com/ppelikan/drlut
  **/
// Formula: sin(2*pi*t/T) 
#ifndef _LUT_H
#define _LUT_H
#include <stdint.h>

typedef struct {
 int32_t x, y;
 } vector_t;

int32_t sine(int32_t angle);
int32_t expand(int32_t i);
void printFix(int32_t i);

#endif
