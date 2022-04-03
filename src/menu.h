#pragma once

#include <string>
#include <map>
#include <iostream>
#include <iomanip>
#include <inttypes.h>
#include <ncurses.h>

enum FocusedButton {
    play,
    load_game,
    options,
    quit
};

class Menu {
    private:
        std::map<FocusedButton, std::string> button_labels;
        FocusedButton current_button;
        std::string logo{};
        int width, height;
        struct {
            uint8_t x;
            uint8_t y;
        } logo_offset;
        int logo_width, logo_height;
        WINDOW* title;
        WINDOW* content;

        // functions for drawing
        void parse_logo(std::string& buffer);
        bool is_frame(uint8_t row, uint8_t col);
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
};
