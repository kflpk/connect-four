#pragma once

#include <string>
#include <map>
#include <iostream>
#include <iomanip>
#include <inttypes.h>

#if defined(__linux__)
#include <sys/ioctl.h>
#elif defined(_WIN32)
#include <Widnows.h>
#define WIN32_LEAN_AND_MEAN
#define VC_EXTRALEAN 
#endif

enum FocusedButton {
    play,
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

        // functions for drawing
        void parse_logo(std::string& buffer);
        bool is_frame(uint8_t row, uint8_t col);
        void draw_logo();
        void draw_frame();
        void draw_buttons();
        void set_parameters(); 
        //   ^ sets parameters for drawing based i.e. line width,
        //     element spacing based on window size

    public:
        Menu();
        void Draw();
        void Update();
        void Printsize();
};
