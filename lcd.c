#include <stdint.h>
#include <string.h>
#include "lcd.h"
#include "charset.h"
#include "players.h"

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


void lcd_update(P1 *p1, P2 *p2)
{
    static int16_t offset = 0;  // scroll offset (persists across calls)

    const char text[] = "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx";
    int16_t text_width = (int16_t)strlen(text) * 6;

    // Advance scroll so first letter starts at x=0 initially
    offset = wrap_int16(offset + 1, text_width);
    int16_t x1 = -offset;

    // Clear ALL pages
    for (uint8_t page = 0; page < 4; page++) {
        for (uint8_t col = 0; col < 128; col++) {
            lcd_buffer[lcd_index(col, page)] = 0x00;
        }

        // Draw scrolling text on each page (if you only want it on page 0, wrap in: if (page == 0) { ... })
        if (page == 0)
        {lcd_write_string(x1, page, text);
        lcd_write_string(x1 + text_width, page, text);}

        if (page == 3)
        {lcd_write_string(x1, page, text);
        lcd_write_string(x1 + text_width, page, text);}
    }

    // HUD / scores (fixed pages)
    char buf[32];

    snprintf(buf, sizeof(buf), "P1 <3:%ld Score:%d", (long)p1->hlth, p1->pnt);
    lcd_write_string(1, 1, buf);

    snprintf(buf, sizeof(buf), "P2 <3:%ld Score:%d", (long)p2->hlth, p2->pnt);
    lcd_write_string(1, 2, buf);

    // Push once after everything is drawn
    lcd_push_buffer(lcd_buffer);
}
