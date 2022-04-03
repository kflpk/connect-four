#include <ncurses.h>
#include "menu.h"

bool Menu::frame_condition(uint8_t row, uint8_t col) {
    if(row == 0 || row == height - 1 || 
       col == 0 || col == 1 || col == width -  2 || col == width  - 1 )
        return true;
    else
        return false;
}
void Menu::draw_frame() {

    for(uint8_t row = 0; row < height; row++) {
        for(uint8_t col = 0; col < width; col++) {
            if(frame_condition(row, col)) {
                std::cout << "█";
            } else {
                std::cout << " ";
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
}

Menu::Menu() {
    if(has_colors()) {
        
    }
    button_labels[play] = "Play";
    button_labels[options] = "Option";
    button_labels[quit] = "Quit game";

    current_button = play;

    set_parameters();
}

void Menu::Draw() {
    draw_frame();
}

void Menu::Update() {

} 

void Menu::Printsize() {
    std:: cout << "Width: " << width << "\nHeight: " << height << "\n";
} 


