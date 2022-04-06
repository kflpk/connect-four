#pragma once

#include <string>
#include <map>
#include <iostream>
#include <iomanip>
#include <cinttypes>
#include <ncurses.h>

enum FocusedButton : uint8_t {
    play,
    load_game,
    options,
    quit,
    _last
};

class Menu {
    private:
        std::map<FocusedButton, std::string> button_labels;
        FocusedButton current_button;
        std::string logo{};
        int width, height;
        struct {
            uint16_t x;
            uint16_t y;
        } logo_offset;
        int logo_width, logo_height;
        WINDOW* title;
        WINDOW* content;

        // functions for drawing
        void parse_logo(std::string& buffer);
        bool is_frame(uint16_t row, uint16_t col);
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

        void next_option();
        void prev_option();
};
