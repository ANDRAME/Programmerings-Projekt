#include "stm32f30x_conf.h"
#include "30010_io.h"
#include "ansi.h"
#include "window.h"
#include "joystick.h"
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
#include "timer.h"
#include <stdio.h>
#include <stdlib.h>
#include "WINscreen.h"
#include "LOSEscreen.h"


//SEE IF U HAVE SHOOT OR SHOOT1, CHANGE ACCORDING TO UR OWN

int main(void)
{
    uart_init(921600);
    clrscr();
	clrcur();

	uint8_t gameTickPeriodHs = 50;
	uint8_t gameCounter =0;
	uint16_t alienSpawnCounter = 0;
	uint32_t asteroidSpawnCounter =0;
	uint32_t astroidSpawnPeriodHs = 400;
	uint16_t powerupCounter =0;

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

    while (1) {

        // update LCD at 10 Hz
        if ((gTime.hs % 10) == 0) {
            lcd_update(&p1, &p2);
        }


        pause_manager_step(&p1, &p2, &myStyle);

        if (!g_pause)
        {
            gameCounter++;
            alienSpawnCounter++;
            asteroidSpawnCounter++;
            powerupCounter++;

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
			        //end conditions
	        if ((p1.hlth<=0)&&(p2.hlth<=0)){
	        	clrscr();
	        	draw_lose_screen(10,10);
	        	while(1){
	        	}
	        }
	        if (p1.pnt  >= 40){
	        	clrscr();
	        	draw_win_screen(10,10,1);
	        	while(1){
	        	}
	        }
	        if (p2.pnt  >= 40){
	        	clrscr();
	        	draw_win_screen(10,10,2);
	        	while(1){
	        	}
	        }

            if (gameCounter >= gameTickPeriodHs)
			{
				// update all game components: e,g. astroids, bullets...

				updateAlien(screen_width);
				updateAstro(screen_height);


				if (alienSpawnCounter >= 500) // how quick it spawns aliens, might not
					//be important to change how fast they go but just how fast they spawn
				{

					spawnAlien(screen_width); //spawning alien in the screen width
					alienSpawnCounter = 0;
				}

				if (asteroidSpawnCounter >= astroidSpawnPeriodHs)
				{
					spawnAstro(screen_width);
					asteroidSpawnCounter=0;
				}
				if( powerupCounter >=700){
					spawn_powerup(&bounds);
					powerupCounter=0;
				}


				// Increase game speed by number of points
				if (p1.pnt + p2.pnt >= 30)
				{
					gameTickPeriodHs=5;
				}

				else if (p1.pnt + p2.pnt >= 20)
				{
					gameTickPeriodHs=10;
				}
				else if (p1.pnt + p2.pnt >=15)
				{
					gameTickPeriodHs=15;
				}
				else if (p1.pnt + p2.pnt>=10)
				{
					gameTickPeriodHs=30;
				}
				else if (p1.pnt + p2.pnt >=5)
				{
				    gameTickPeriodHs=40;
				}
				else
				{
					gameTickPeriodHs=50;
				}

				gameCounter = 0;
			}

        }
    }
}
        
