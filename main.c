#include "stm32f30x_conf.h"
#include "30010_io.h"
#include "ansi.h"
#include "window.h"
#include "joystick.h"
#include "timer.h"
#include "keyboard.h"
#include "lcd.h"
#include "players.h"
#include "shoot.h"
#include "alien.h"
#include "game.h"
#include "ui_screen.h"
#include "asteroid.h"


int main(void)
{
    uart_init(921600);
    clrscr();
    cursor_hide();



    WindowStyle_t myStyle;
    myStyle.wall = WALL_DOUBLE;
    myStyle.fg = 7;
    myStyle.bg = 0;
    myStyle.title = "Asteroids";

    P1 p1;
    P2 p2;
    player_init(&p1,&p2);

    Bounds bounds;
    bounds_init(&bounds);

    //Initialise Asteroid System
    initAst();

    uint16_t frame_counter = 0;
    uint8_t screen_width = 100;  // Standard terminal width
    uint8_t screen_height = 35; // Standard terminal height



    menu_action_t act = menu(&p1, &p2, &myStyle);

    if (act == MENU_ACTION_QUIT) {
        while (1) {}
    }

    while (1) {

        if (Time.hs % 10 == 0) {
        	lcd_update(&p1, &p2);

        }

        if (Time.hs % 10 == 0) {
        	lcd_update(&p1, &p2);
        }


         // loop forever
    	player_step(&p1, &p2, &bounds);
    	Bullets_Update();

    	point_count(&p1, &p2);

        // 3. Spawn logic: Try to spawn an asteroid every 50 frames
        if (frame_counter % 500 == 0) {
            spawnAstro(screen_width);
        }

        // 4. Update and Draw
        // This function handles the deleting, moving, and redrawing
        if (frame_counter % 50 == 0) {
        	updateAstro(screen_height);;
        }


        // 5. Timing Control
        // Adjust the delay to control the game speed
        if ((frame_counter % 10000)==0){
        	frame_counter = 0;
        }
        frame_counter++;

    }

}
