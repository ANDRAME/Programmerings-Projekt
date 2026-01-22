
#include "stm32f30x_conf.h"
#include "30010_io.h"
#include "ansi.h"
#include "window.h"
#include "joystick.h"
#include "Alientimer.h"
#include "keyboard.h"
#include "lcd.h"
#include "players.h"
#include "shoot1.h"
#include "alien.h"
#include "alienspawn.h"
#include "game.h"
#include "ui_screen.h"
#include "asteroid.h"
#include "powerup.h"
#include <stdio.h>
#include <stdlib.h>
void draw_alien(uint16_t x, uint16_t y);
void initAlien();
void spawnAlien(uint8_t grid_width);

void updateAlien(uint8_t grid_width, uint8_t *bounce);

int main(void)
{
    uart_init(921600);
    clrscr();
    cursor_hide();

    uint8_t gTimeFlag = 0;


	uint8_t gameCounterTickRate = 5;
	uint8_t gameCounter =0;
	uint16_t alienSpawnCounter = 0;
	uint8_t bounce=1;


    WindowStyle_t myStyle;
    myStyle.wall  = WALL_DOUBLE;
    myStyle.fg    = 7;
    myStyle.bg    = 0;
    myStyle.title = "Asteroids";

    P1 p1;
    P2 p2;
    player_init(&p1, &p2);

    Bounds bounds;
    bounds_init(&bounds);
    powerups_init();


    initAst();
    initAlien();
    setUPTimer();

    uint16_t frame_counter = 0;
    uint8_t screen_width  = 100;
    uint8_t screen_height = 35;

    menu_action_t act = menu(&p1, &p2, &myStyle);
    if (act == MENU_ACTION_QUIT) {
        while (1) {}
    }

    uint32_t time_now_hs(void)
    {
        uint32_t sec = (uint32_t)(gTime.h * 3600 + gTime.m * 60 + gTime.s);
        return sec * 100u + (uint32_t)gTime.hs;
    }

    uint32_t last_autofire_hs_p1 = 0;
    uint32_t last_autofire_hs_p2 = 0;


    uint8_t last_frame_tick = gTime.hs;

    while (1) {


        uint8_t t = gTime.hs;

        last_frame_tick = t;

        // update LCD at 10 Hz
        if ((gTime.hs % 10) == 0) {
            lcd_update(&p1, &p2);
        }


        pause_manager_step(&p1, &p2, &myStyle);

        if (!g_pause)
        {
            gameCounter++;
            alienSpawnCounter++;

            player_step(&p1, &p2, &bounds);
            powerups_update(&p1, &p2, &bounds); // new
            Bullets_Update();
            point_count(&p1, &p2);
            game_update_hearts(&p1, &p2); // new
            game_update_points(&p1, &p2); // new



            uint32_t now = time_now_hs();

            /* Auto-fire while yellow powerup is active */
            if (powerup_autofast_active(1)) {
                if ((int32_t)(now - last_autofire_hs_p1) >= 0) {
                    Bullet_Spawn(1, &p1, &p2);
                    last_autofire_hs_p1 = now + 3;   // fire every 0.03s
                }
            }

            if (powerup_autofast_active(2)) {
                if ((int32_t)(now - last_autofire_hs_p2) >= 0) {
                    Bullet_Spawn(2, &p1, &p2);
                    last_autofire_hs_p2 = now + 3;   // fire every 0.03s
                }
            }

            if (gameCounter >= gameCounterTickRate)
            		{
            			// update all game components: e,g. astroids, bullets...

            			updateAlien(94, &bounce);

            			if (alienSpawnCounter >= 500) // how quick it spawns aliens, might not
            				//be important to change how fast they go but just how fast they spawn
            			{

            				spawnAlien(screen_width - 1); //spawning alien in the screen width
            				alienSpawnCounter = 0;
            			}

            			gameCounter = 0;
            		}

            // asteroid spawn/update timing
            if ((frame_counter % 500) == 0) {
                spawnAstro(screen_width);
                spawn_powerup(&bounds);
            }
            if ((frame_counter % 50) == 0) {
                updateAstro(screen_height);
            }

            frame_counter++;
            if (frame_counter >= 10000) frame_counter = 0;
        }
        else
        {
        	uart_getJoystickDirection();
        }
    }
}

