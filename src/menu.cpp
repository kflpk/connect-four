#include <iostream>
#include <fstream>
#include <ncurses.h>
#include "menu.h"
#include "color.h"
#include "extras.h"

void Menu::draw_logo() {
    // TODO: Refactor the hell out of it, because it's ugly
    // TODO: Make the code logo-size-independent

    int row{}, col{};
    std::string buffer{};
    std::ifstream logo_file;

    wattron(title, COLOR_PAIR(PAIR_DEFAULT));
    wfill(title, ' ');
    wattroff(title, COLOR_PAIR(PAIR_DEFAULT));

    logo_file.open("assets/logo1.txt");

    if(logo_file.is_open()) { //print "Connect" on screen
        while(!logo_file.eof()) {
            std::getline(logo_file, buffer);
            wmove(title, logo_offset.y + row, logo_offset.x + col);

            wattron(title, COLOR_PAIR(PAIR_BLUE));
            wprintw(title ,"%s", buffer.c_str());
            wattroff(title, COLOR_PAIR(PAIR_BLUE));

            row++;
        } 
    }

    logo_file.close();
    logo_file.open("assets/logo2.txt");

    col = 41; // width of first word plus a few characters of space
    row = 0; // reset the row

    if(logo_file.is_open()) { //print "Four" on screen
        while(!logo_file.eof()) {
            std::getline(logo_file, buffer);

            wmove(title, logo_offset.y + row, logo_offset.x + col);
            wattron(title, COLOR_PAIR(PAIR_ORANGE));
            wprintw(title, "%s", buffer.c_str());
            wattroff(title, COLOR_PAIR(PAIR_ORANGE));

            row++;
        } 
    }
    wattron(title, COLOR_PAIR(PAIR_DEFAULT));
    box(title, 0, 0);
    wattroff(title, COLOR_PAIR(PAIR_DEFAULT));
    wrefresh(title);
}

void Menu::draw_content() {
    wattron(content, COLOR_PAIR(PAIR_DEFAULT));
    //box(content, ACS_HLINE , 0);
    wfill(content, ' ');
    wborder(content, 0 ,0 ,0 , 0, ACS_LTEE, ACS_RTEE, 0, 0);
    wattroff(content, COLOR_PAIR(PAIR_DEFAULT));
    wrefresh(content);
}

bool Menu::is_frame(uint8_t row, uint8_t col) {
    if(row == 0 || row == height - 1 || 
       col == 0 || col == 1 || col == width -  2 || col == width  - 1 )
        return true;
    else
        return false;
}
void Menu::draw_frame() {

    for(uint8_t row = 0; row < height; row++) { // draw game frame in one color light gray, and background in dark grey
        for(uint8_t col = 0; col < width; col++) {
            if(is_frame(row, col)) {
                attron(COLOR_PAIR(PAIR_FRAME));
                printw(" ");
                attroff(COLOR_PAIR(PAIR_FRAME));
            } else {
                attron(COLOR_PAIR(PAIR_DEFAULT));
                printw(" ");
                attroff(COLOR_PAIR(PAIR_DEFAULT));
            }
        }
        std::cout << std::endl;
    }
}
//void Menu::draw_buttons();
void Menu::set_parameters() {
    getmaxyx(stdscr, height, width);
    logo_offset.y = 2;
    logo_width = 64;
    logo_height = 5;
    logo_offset.x = (width - logo_width)/2;
    

    title = newwin(logo_height + 4, width, 0, 0); // creates new window for title 
    content = newwin(height - (logo_height + 3), width, logo_height + 3, 0); //creates new window for main content of the menu screen
    refresh();
    //title = stdscr;
}

Menu::Menu() {
    button_labels[play] = "Play";
    button_labels[options] = "Option";
    button_labels[load_game] = "Load game";
    button_labels[quit] = "Quit game";

    current_button = play;

    set_parameters();
}

void Menu::Draw() {
    // TODO: Split the menu into 2 windows; title and content
    draw_frame();
    refresh();
    draw_logo();
    draw_content();
}

void Menu::Update() {

} 


