
#ifndef KEYBOARD_H_
#define KEYBOARD_H_

#include "players.h"
#include "window.h"


uint8_t uart_getJoystickDirection(void);
void pause_manager_step(P1 *p1, P2 *p2, WindowStyle_t *style);


typedef enum {
    GAME_RUNNING = 0,
    GAME_PAUSED  = 1
} GameState;

extern volatile uint8_t g_pause_request;
extern volatile GameState gGameState;
extern volatile uint8_t g_pause;

#endif /* KEYBOARD_H_ */
