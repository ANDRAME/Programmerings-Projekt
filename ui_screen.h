#ifndef MENU_H_
#define MENU_H_

#include <stdint.h>
#include "players.h"
#include "window.h"

/* Screens */
typedef enum {
    SCREEN_MAIN = 0,
    SCREEN_HELP = 1,
    SCREEN_BOSS = 2,
    SCREEN_GAME = 3
} screen_t;

typedef enum {
    MENU_ACTION_NONE = 0,
    MENU_ACTION_START_GAME,
    MENU_ACTION_QUIT
} menu_action_t;



/* Drawing helpers */
void draw_box(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2);
void draw_welcome_banner(uint8_t x, uint8_t y);

/* Render functions */
void render_header(void);
void render_main(void);
void render_help(void);
void render_boss(void);

/* Menu controller */
menu_action_t menu(P1 *p1, P2 *p2, WindowStyle_t *style);


#endif /* MENU_H_ */
