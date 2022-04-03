#include <iostream>
#include <fstream>
#include <ncurses.h>
#include "menu.h"
#include "color.h"

void Menu::draw_logo() {
    std::string buffer{};
    std::ifstream logo_file;
    logo_file.open("assets/logo.txt");
    if(logo_file.is_open()) {
        while(!logo_file.eof()) {
            std::getline(logo_file, buffer);
            attron(COLOR_PAIR(PAIR_FRAME));
            printw(buffer.c_str());
            attroff(COLOR_PAIR(PAIR_FRAME));
        }
    }
}

bool Menu::is_frame(uint8_t row, uint8_t col) {
    if(row == 0 || row == height - 1 || 
       col == 0 || col == 1 || col == width -  2 || col == width  - 1 )
        return true;
    else
        return false;
}
void Menu::draw_frame() {

    for(uint8_t row = 0; row < height; row++) {
        for(uint8_t col = 0; col < width; col++) {
            if(is_frame(row, col)) {
                attron(COLOR_PAIR(PAIR_FRAME));
                printw(" ");
                attroff(COLOR_PAIR(PAIR_FRAME));
            } else {
                printw(" ");
            }
        }
        std::cout << std::endl;
    }
}
//void Menu::draw_buttons();
void Menu::set_parameters() {
    // TODO: rewrite to use ncurses instead of platform-dependent headers
    #if defined(_WIN32)
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
        width = (int)(csbi.srWindow.Right-csbi.srWindow.Left+1);
        height = (int)(csbi.srWindow.Bottom-csbi.srWindow.Top+1);
    #elif defined(__linux__)
        struct winsize w;
        ioctl(fileno(stdout), TIOCGWINSZ, &w);
        width = (int)(w.ws_col);
        height = (int)(w.ws_row);
    #endif

    

    /* color pairs for player tiles
    init_pair(1, COLOR_BLACK, COLOR_YELLOW);
    init_pair(2, COLOR_BLACK, COLOR_BLUE);
    */
}

Menu::Menu() {

    if(has_colors()) {
        
    }
    logo_offset.x = 0;
    logo_offset.y = 0;
    
    button_labels[play] = "Play";
    button_labels[options] = "Option";
    button_labels[quit] = "Quit game";

    current_button = play;

    set_parameters();
}

void Menu::Draw() {
    draw_frame();
    draw_logo();
}

void Menu::Update() {

} 

void Menu::Printsize() {
    std:: cout << "Width: " << width << "\nHeight: " << height << "\n";
} 


