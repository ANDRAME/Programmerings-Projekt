#ifndef LCD_H_
#define LCD_H_

#include <stdint.h>
#include "players.h"
extern uint8_t lcd_buffer[512];

static inline uint16_t lcd_index(uint8_t x, uint8_t page)
{
    return (uint16_t)page * 128 + x;
}

void lcd_write_string(int16_t x, uint8_t page, const char *str);
static int16_t wrap_int16(int16_t v, int16_t period);
void lcd_update(P1 *p1, P2 *p2);

#endif /* LCD_H_ */
