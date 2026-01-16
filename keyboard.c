#include <stdint.h>
#include "keyboard.h"

#include <stdint.h>
#include "keyboard.h"

JoystickDirection2 uart_getJoystickDirection(void)
{
    uint8_t c = uart_get_char();

    switch (c)
    {
        case 'p':
            return JOY_SHOOT2;

        case 0x1B:   /* ESC */
        {
            uint8_t c2 = uart_get_char();
            if (c2 == '[')
            {
                uint8_t c3 = uart_get_char();
                switch (c3)
                {
                    case 'A': return JOY_UP2;
                    case 'B': return JOY_DOWN2;
                    case 'C': return JOY_RIGHT2;
                    case 'D': return JOY_LEFT2;
                    default:  return JOY_NONE2;
                }
            }
            break;
        }

        default:
            break;
    }

    return JOY_NONE2;
}



const char* joystickString2(JoystickDirection2 dir2)
{
    switch (dir2)
    {
        case JOY_UP2:     return "UP";
        case JOY_DOWN2:   return "DOWN";
        case JOY_LEFT2:   return "LEFT";
        case JOY_RIGHT2:  return "RIGHT";
        case JOY_CENTER2: return "CENTER";
        case JOY_SHOOT2: return "SHOOT";
        default:         return "NONE";
    }
}
