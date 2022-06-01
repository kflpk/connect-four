#pragma once

#include <string>
#include <map>
#include <iostream>
#include <iomanip>
#include <cinttypes>
#include <ncurses.h>
#include "extras.h"

enum Buttons : uint8_t {
    play,
    load_game,
    options,
    quit,
    _last
};

enum Settings : uint8_t {
    setting_rows,
    setting_cols,
    setting_win,
    setting_done,
    setting_back,
    setting_end,
    setting_color1,
    setting_color2,
};


class Menu {
    private:
        std::map<Buttons, std::string> button_labels;
        std::map<Settings, std::string> setting_labels;
        Buttons current_button;
        Settings current_setting;
        GameState state;
        GameParameters parameters;
        GameParameters temp_perameters;

        int width, height;
        struct {
            uint16_t x;
            uint16_t y;
        } logo_offset;
        int logo_width, logo_height;

        WINDOW* title;
        WINDOW* content;

        // =========================
        // | Function declarations |
        // =========================

        // Functions for controlling program flow
        void key_handler(); // Function handling keystrokes
        void next_item(); // Selects next item from the menu
        void prev_item(); // Selects previous item from the menu
        void setting_increment(); // Increments a value in Settings menu
        void setting_decrement(); // Decrements a value in Settings menu
        void set_parameters(); 
        /*   ^ sets parameters for drawing based i.e. line width,
               element spacing based on window size */

        // Functions for drawing
        void draw_logo(); // Draws "Connect Four" logo in the main menu
        void draw_content(); // Draws menu items and selection indicators
    public:
        Menu(); // Default constructor of Menu class
        GameParameters Start(); // Starts the main menu
};
