#pragma once

#include <ncurses.h>
#include <cinttypes>
#include <string>
#include <vector>
#include <string>

void wfill(WINDOW* win, char c);                                         /* ncurses-like function to fill 
                                                                            a window with a char (space usually) */

void init_theme();                                                       // Initializes color pairs used in the program
void startup();                                                          // Set of functions starting ncurses window
void cleanup();                                                          // Set of functions enging ncurses window
void warning(std::string warning_content);                               // Displays pop-up window with warning info
std::vector<std::string> word_wrap(std::string source, int line_length); // Word-wraps long strings for warning function

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