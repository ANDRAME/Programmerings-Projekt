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
#include "powerup.h"


int main(void)
{
    uart_init(921600);
    clrscr();
    cursor_hide();

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

    uint16_t frame_counter = 0;
    uint8_t screen_width  = 100;
    uint8_t screen_height = 35;

    menu_action_t act = menu(&p1, &p2, &myStyle);
    if (act == MENU_ACTION_QUIT) {
        while (1) {}
    }

    uint32_t time_now_hs(void)
    {
        uint32_t sec = (uint32_t)(Time.h * 3600 + Time.m * 60 + Time.s);
        return sec * 100u + (uint32_t)Time.hs;
    }

    uint32_t last_autofire_hs_p1 = 0;
    uint32_t last_autofire_hs_p2 = 0;


    uint8_t last_frame_tick = Time.hs;

    while (1) {
        // ---- run game logic only once per timer tick ----
        uint8_t t = Time.hs;
        if (t == last_frame_tick) {
            continue;
        }
        last_frame_tick = t;

        // update LCD at 10 Hz (every 0.1s if Time.hs is centiseconds)
        if ((Time.hs % 10) == 0) {
            lcd_update(&p1, &p2);
        }

        player_step(&p1, &p2, &bounds);
        powerups_update(&p1, &p2, &bounds);
        Bullets_Update();
        point_count(&p1, &p2);
        game_update_hearts(&p1, &p2);

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

        // asteroid spawn/update timing
        if ((frame_counter % 500) == 0) {
            spawnAstro(screen_width);
        }
        if ((frame_counter % 50) == 0) {
            updateAstro(screen_height);
        }

        frame_counter++;
        if (frame_counter >= 10000) frame_counter = 0;
    }
}
