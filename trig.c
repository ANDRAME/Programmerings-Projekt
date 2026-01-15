#include "ansi.h"
#include "LUTSrc.h"
#include "trig.h"
#include "stdio.h"

int32_t expand(int32_t i) {
// Converts an (6)2.14 fixed point number to 16.16
return i << 2;
}


void printFix(int32_t i) {
// Prints a signed 16.16 fixed point number
if ((i & 0x80000000) != 0) { // Handle negative numbers
	printf("-");
	i = ~i + 1;
		}
	printf("%ld.%04ld", i >> 16, 10000 * (uint32_t)(i & 0xFFFF) >> 16);
	// Print a maximum of 4 decimal digits to avoid overflow
}


int32_t sinus(int32_t angle)
{
    return SIN[angle & 0x1FF];
}


int32_t cosinus(int32_t angle)
{
    return SIN[(angle + 0x80) & 0x1FF];
}

void rotateVector(vector_t *v, int32_t angle)
{
    int32_t s = sinus(angle);     // (16)2.14
    int32_t c = cosinus(angle);   // (16)2.14

    int32_t x = v->x;             // 18.14
    int32_t y = v->y;             // 18.14

    // (18.14 * 2.14) -> 20.28, then >>14 -> 20.14
    v->x = (x * c - y * s) >> 14;
    v->y = (x * s + y * c) >> 14;
}




