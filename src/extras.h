#pragma once

#include <ncurses.h>
#include <cinttypes>
#include <string>
#include <vector>
#include <string>

void wfill(WINDOW* win, char c); 
/* ncurses-like function to fill a window with a char
   (space usually) */

void init_theme();
void startup();
void cleanup();
void warning(std::string warning_content);
std::vector<std::string> word_wrap(std::string source, int line_length);

struct GameParameters {
    uint16_t rows = 5;
    uint16_t columns = 7;
    uint16_t win_condition = 4;
    
    uint8_t player1_color;
    uint8_t player2_color;

    bool load_save = false;
    std::string save_path;
};

enum GameState {
    active,
    paused,
    menu,
    menu_settings
};