#include "stm32f30x_conf.h"
#include "30010_io.h"
#include <stdint.h>
#include <stdio.h>

#include "ansi.h"
#include "players.h"
#include "window.h"
#include "game.h"    // for game_init(...)
#include "ui_screen.h"

#define BG_COLOR 0   // your game/menu background
#define UI_FG    7   // menu text color (light gray/white)


/* The drawing of the box */
void draw_box(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2)
{
    if (x2 <= x1 + 1 || y2 <= y1 + 1) return;

    gotoxy(x1, y1); putchar('+');
    for (uint8_t x = x1 + 1; x < x2; x++) putchar('-');
    putchar('+');

    for (uint8_t y = y1 + 1; y < y2; y++) {
        gotoxy(x1, y); putchar('|');
        gotoxy(x2, y); putchar('|');
    }

    gotoxy(x1, y2); putchar('+');
    for (uint8_t x = x1 + 1; x < x2; x++) putchar('-');
    putchar('+');
}

/* Welcome banner */
void draw_welcome_banner(uint8_t x, uint8_t y)
{

    gotoxy(x, y);
    printf(" _       __     __                             ");
    gotoxy(x, y + 1);
    printf("| |     / /__  / /________  ____ ___  ___     ");
    gotoxy(x, y + 2);
    printf("| | /| / / _ \\/ / ___/ __ \\/ __ `__ \\/ _ \\    ");
    gotoxy(x, y + 3);
    printf("| |/ |/ /  __/ / /__/ /_/ / / / / / /  __/    ");
    gotoxy(x, y + 4);
    printf("|__/|__/\\___/_/\\___/\\____/_/ /_/ /_/\\___/     ");

}


/* Header */
void render_header(void)
{
    draw_box(2, 1, 100, 7);
    draw_welcome_banner(10, 2);

    gotoxy(2, 8);
}

/* Main menu */
void render_main(void)
{
	bgcolor(BG_COLOR);
	fgcolor(UI_FG);
	clrscr();
    render_header();

    draw_box(2, 8, 100, 40);

    gotoxy(4, 10);
    printf("Choose an option by pressing a key:");

    gotoxy(6, 12);
    printf("[s] Start game");

    gotoxy(6, 13);
    printf("[h] Help menu");

    gotoxy(6, 14);
    printf("[b] Boss key (toggle)");

    gotoxy(6, 15);
    printf("[m] Main menu (from any screen)");

    gotoxy(6, 16);
    printf("[q] Quit (stops here)");

    fflush(stdout);
}

/* Help */
void render_help(void)
{
clrscr();

 gotoxy(10, 4);
 printf("========== HELP / CONTROLS ==========");

 gotoxy(10, 7);
 printf("PLAYER 1 (Joystick):");
 gotoxy(12, 9);
 printf("- Move: Joystick");
 gotoxy(12, 10);
 printf("- Shoot: Button 2");

 gotoxy(10, 13);
 printf("PLAYER 2 (Keyboard):");
 gotoxy(12, 15);
 printf("- Move: Arrow keys");
 gotoxy(12, 16);
 printf("- Shoot: 'p'");

 gotoxy(10, 19);
 printf("BOSS KEY:");
 gotoxy(12, 21);
 printf("- Press 'b' to toggle boss screen ;)");

 gotoxy(10, 24);
 printf("POWERUPS (falling blocks):");

 // Purple = Triple shot
 gotoxy(12, 26);
 fgcolor(5);
 printf("%c", (char)219);
 fgcolor(7);
 printf(" Purple  - Triple Shot: shoots 3 bullets at once");

 // Yellow = Auto fast
 gotoxy(12, 28);
 fgcolor(11);
 printf("%c", (char)219);
 fgcolor(7);
 printf(" Yellow  - Auto Fast: automatic rapid fire while active");

 // Blue = Invincible
 gotoxy(12, 30);
 fgcolor(12);
 printf("%c", (char)219);
 fgcolor(7);
 printf(" Blue    - Invincible: no damage from asteroids for a while");

 gotoxy(10, 34);
 printf("Press 'm' again to return to the menu.");

 gotoxy(10, 36);
 printf("=====================================");

 resetbgcolor();
}

/* Boss screen */
void render_boss(void)
{
	bgcolor(BG_COLOR);
	fgcolor(UI_FG);
	clrscr();
    draw_box(10, 6, 70, 18);

    gotoxy(18, 9);
    printf("SYSTEM MONITORING DASHBOARD");

    gotoxy(16, 11);
    printf("All systems working. Processing reports...");

    gotoxy(2, 24);
    printf(" LOG: STATUS=OK  CPU=12%% ");

    fflush(stdout);
}

/* Fixed menu: takes game state pointers + loops */
menu_action_t menu(P1 *p1, P2 *p2, WindowStyle_t *style)
{
    screen_t screen = SCREEN_MAIN;
    uint8_t boss_active = 0;

    render_main();

    while (1)
    {
        char c = uart_get_char();

        /* Quit */
        if (c == 'q' || c == 'Q') {
            return MENU_ACTION_QUIT;
        }

        /* Always go to main menu */
        if (c == 'm' || c == 'M') {
            boss_active = 0;
            screen = SCREEN_MAIN;
            render_main();
            continue;
        }

        /* Boss toggle */
        if (c == 'b' || c == 'B') {
            boss_active = (uint8_t)!boss_active;
            screen = boss_active ? SCREEN_BOSS : SCREEN_MAIN;
            if (boss_active) render_boss();
            else render_main();
            continue;
        }

        /* Help toggle (from main or help) */
        if (c == 'h' || c == 'H') {
            if (screen == SCREEN_HELP) {
                screen = SCREEN_MAIN;
                render_main();
            } else if (screen == SCREEN_MAIN) {
                screen = SCREEN_HELP;
                render_help();
            }
            continue;
        }

        /* Start game ONLY from main */
        if (screen == SCREEN_MAIN && (c == 's' || c == 'S')) {
            game_init(p1, p2, style);     /* draws game screen once */
            return MENU_ACTION_START_GAME;     /* EXIT menu so it can't draw over game */
        }

        /* ignore everything else */
    }
}
