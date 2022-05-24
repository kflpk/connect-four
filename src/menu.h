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

enum Options : uint8_t {
    option_rows,
    option_cols,
    option_win,
    option_end,
    option_color1,
    option_color2,
};


class Menu {
    private:
        std::map<Buttons, std::string> button_labels;
        std::map<Options, std::string> option_labels;
        Buttons current_button;
        Options current_option;
        GameState state;

        int width, height;
        struct {
            uint16_t x;
            uint16_t y;
        } logo_offset;
        int logo_width, logo_height;

        WINDOW* title;
        WINDOW* content;


        // functions for drawing
        //bool is_frame(uint16_t row, uint16_t col);
        void fill_screen();
        void draw_logo();
        void draw_frame();
        void draw_content();
        void set_parameters();
        //   ^ sets parameters for drawing based i.e. line width,
        //     element spacing based on window size

    public:
        Menu();
        void Draw();
        void Update();
        void Start();
        void key_handler();
        void next_option();
        void prev_option();
};
