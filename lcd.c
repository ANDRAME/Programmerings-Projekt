#include <stdint.h>
#include <string.h>
#include "lcd.h"
#include "charset.h"

uint8_t lcd_buffer[512];

void lcd_write_string(int16_t x, uint8_t page, const char *str)
{
    while (*str) {
        char ch = *str++;
        if (ch < 0x20 || ch > 0x7E) ch = ' ';

        uint8_t glyph = (uint8_t)(ch - 0x20);

        for (uint8_t col = 0; col < 5; col++) {
            if (x >= 0 && x < 128) {
                lcd_buffer[lcd_index((uint8_t)x, page)] =
                    (uint8_t)character_data[glyph][col];
            }
            x++;
        }

        // spacing column
        if (x >= 0 && x < 128) {
            lcd_buffer[lcd_index((uint8_t)x, page)] = 0x00;
        }
        x++;
    }
}

static int16_t wrap_int16(int16_t v, int16_t period)
{
    // wrap v into [0, period)
    v %= period;
    if (v < 0) v += period;
    return v;
}

void lcd_update(uint8_t page)
{
    static int16_t offset = 0;          // scroll offset
    const char text[] = "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx";
    int16_t text_width = (int16_t)strlen(text) * 6;

    // Clear visible page
    for (uint8_t col = 0; col < 128; col++) {
        lcd_buffer[lcd_index(col, page)] = 0x00;
    }

    // Make it start ON the LCD: first letter at x=0 initially
    offset = wrap_int16(offset + 1, text_width);

    // Base x is negative offset (so it slides left)
    int16_t x1 = -offset;

    // Draw two copies so the end connects to the beginning seamlessly
    lcd_write_string(x1, page, text);
    lcd_write_string(x1 + text_width, page, text);

    lcd_push_buffer(lcd_buffer);
}
