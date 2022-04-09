#include <iostream>
#include <fstream>
#include <ncurses.h>
#include "menu.h"
#include "color.h"
#include "extras.h"

// TODO: Make a key-hadling method for Menu

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
    uint16_t top_offset = 4;
    uint16_t left_offset = (width - 12)/2;

    wattron(content, COLOR_PAIR(PAIR_DEFAULT));
    wfill(content, ' ');
    wborder(content, 0 ,0 ,0 , 0, ACS_LTEE, ACS_RTEE, 0, 0);
    wattroff(content, COLOR_PAIR(PAIR_DEFAULT));

    wattron(content, COLOR_PAIR(PAIR_DEFAULT));
    for(int button = play; button != _last; button++) {
        wmove(content, top_offset + 2 * button, left_offset);
        wprintw(content, "[%c] %s", ((FocusedButton)button == current_button) ? 'x' : ' ',
        button_labels[(FocusedButton)button].c_str());
    }
    wattroff(content, COLOR_PAIR(PAIR_DEFAULT));

    wrefresh(content);
}

bool Menu::is_frame(uint16_t row, uint16_t col) {
    if(row == 0 || row == height - 1 || 
       col == 0 || col == 1 || col == width -  2 || col == width  - 1 )
        return true;
    else
        return false;
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
}

Menu::Menu() {
    button_labels[play] = "Play";
    button_labels[options] = "Options";
    button_labels[load_game] = "Load game";
    button_labels[quit] = "Quit game";

    current_button = play;

    set_parameters();
}

void Menu::Start() {
    refresh();
    draw_logo();
    draw_content();

    Loop();
}

void Menu::next_option() {
    switch(current_button) {
        case play:
            current_button = load_game;
        break;
        case load_game:
            current_button = options;
        break;
        case options:
            current_button = quit;
        break;

        case quit:
        case _last:
        default:
        break;
    }
}

void Menu::prev_option() {
    switch(current_button) {
        case quit:
            current_button = options;
        break;
        case options:
            current_button = load_game;
        break;
        case load_game:
            current_button = play;
        break;
        case play:
        case _last:
        default:
        break;
    }
}
void Menu::key_handler() {
    int key;
    keypad(content, true);
    key = wgetch(content);
    
    switch(key) {
        case KEY_LEFT:
        case KEY_UP:
        case 'k':
            prev_option();
        break;

        case KEY_RIGHT:
        case KEY_DOWN:
        case 'j':
            next_option();
        break;

        case KEY_ENTER:
        case ' ':
            exit(1);
        break;

        case '\e':  //ESC key
            exit(0);
        break;
        
    }
}

void Menu::Loop() {
    while(true) {
        key_handler();
        draw_content();
    }
}