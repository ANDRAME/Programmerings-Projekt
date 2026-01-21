#include <stdint.h>
#include "keyboard.h"

#include <stdint.h>
#include "keyboard.h"

volatile uint8_t g_pause = 0;

uint8_t uart_getJoystickDirection(void)
{
    static uint8_t state = 0;
    static uint8_t dir_ttl = 0;

    // ESC sequence parser state: 0=normal, 1=got ESC, 2=got ESC[
    static uint8_t esc = 0;

    uint8_t c = uart_get_char();

            if (esc == 0)
            {

                if (c == 'p') {
                    state |= (1<<4);          // shoot event
                } else if (c == 0x1B) {
                    esc = 1;
            } else if (c == 'b') {
            	g_pause ^= 1;
            }
            }

            else if (esc == 1)
            {
                if (c == '[') esc = 2;
                else esc = 0;
            }
            else if (esc == 2)
            {
                // arrow received: update direction
                state &= ~((1<<0)|(1<<1)|(1<<2)|(1<<3));

                switch (c) {
                    case 'A': state |= (1<<0); dir_ttl = 6; break; // up
                    case 'B': state |= (1<<1); dir_ttl = 6; break; // down
                    case 'D': state |= (1<<2); dir_ttl = 6; break; // left
                    case 'C': state |= (1<<3); dir_ttl = 6; break; // right
                    default: break;
                }
                esc = 0;
            }

    // direction decay
    if (dir_ttl > 0) dir_ttl--;
    else state &= ~((1<<0)|(1<<1)|(1<<2)|(1<<3));

    // Make shoot a ONE-FRAME event
    uint8_t out = state;
    state &= ~(1<<4);

    return out;
}
