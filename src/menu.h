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
    _last // used to recognise when the last item is focused
};

enum Settings : uint8_t {
    setting_rows,
    setting_cols,
    setting_win,
    setting_done,
    setting_back,
    setting_end,     // used to recognise when the last item is focused
    setting_color1, 
    setting_color2,  // colors currently unused, may be implemented later
};


class Menu {
    private:
        std::map<Buttons, std::string> button_labels;   // stores button labels for items in main menu
        std::map<Settings, std::string> setting_labels; // stores button labels for items in settings menu
        Buttons current_button;                         // stores currently focused main menu button
        Settings current_setting;                       // stores currently focused item in settings menu
        GameState state;                                // stores current game state
        GameParameters parameters;                      // stores game parameters to be passed to a Game instance
        GameParameters temp_perameters;                 // temporarily stores game parameters in setting menu

        int width, height;            // main window dimensions
        struct {
            uint16_t x;
            uint16_t y;
        } logo_offset;                // logo offset
        int logo_width, logo_height;  // logo dimensions

        WINDOW* title;   // window for the program title
        WINDOW* content; // window for the main menu content (buttons)

        // =========================
        // | Function declarations |
        // =========================

        // Functions for controlling the program flow
        void key_handler();         // Function handling keystrokes
        void next_item();           // Selects next item from the menu
        void prev_item();           // Selects previous item from the menu
        void setting_increment();   // Increments a value in Settings menu
        void setting_decrement();   // Decrements a value in Settings menu
        void set_parameters();      /* sets parameters for drawing based i.e. line width,
                                       element spacing based on window size */

        // Functions for drawing
        void draw_logo();           // Draws "Connect Four" logo in the main menu
        void draw_content();        // Draws menu items and selection indicators
    public:
        Menu();                     // Default constructor of Menu class
        GameParameters Start();     // Starts the main menu
        void update_dimensions();
};
