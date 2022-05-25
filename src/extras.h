#pragma once

#include <ncurses.h>
#include <cinttypes>

void wfill(WINDOW* win, char c); 
/* ncurses-like function to fill a window with a char
   (space usually) */

void init_theme();
void startup();
void cleanup();

struct GameParameters {
    uint16_t rows = 5;
    uint16_t columns = 7;
    uint16_t victory_condition = 4;
    
    uint8_t player1_color;
    uint8_t player2_color;
};

enum GameState {
    active,
    paused,
    menu,
    menu_settings
};