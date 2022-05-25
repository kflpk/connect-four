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
    uint16_t top_offset = 4;
    uint16_t left_offset = (width - 12)/2;

    wattron(content, COLOR_PAIR(PAIR_DEFAULT));
    wfill(content, ' ');
    wborder(content, 0 ,0 ,0 , 0, ACS_LTEE, ACS_RTEE, 0, 0);
    wattroff(content, COLOR_PAIR(PAIR_DEFAULT));

    wattron(content, COLOR_PAIR(PAIR_DEFAULT));
    if(state == menu) {
        for(int button = play; button != _last; button++) {
            wmove(content, top_offset + 2 * button, left_offset);
            wprintw(content, "[%c] %s", ((Buttons)button == current_button) ? 'x' : ' ',
            button_labels[(Buttons)button].c_str());
        }
    } else if(state == menu_settings) {
        for(int option = setting_rows; option != setting_end; option++) {
            wmove(content, top_offset + 2 * option, left_offset);
            wprintw(content, "[%c] %s", ((Settings)option == current_setting) ? 'x' : ' ',
            setting_labels[(Settings)option].c_str());
        }

    }
    wattroff(content, COLOR_PAIR(PAIR_DEFAULT));

    wrefresh(content);
}

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
    button_labels[options] = "Settings";
    button_labels[load_game] = "Load game";
    button_labels[quit] = "Quit game";

    setting_labels[setting_rows] = "Rows";
    setting_labels[setting_cols] = "Columns";
    setting_labels[setting_win]  = "Win condition";

    current_button = play;
    current_setting = setting_rows;
    state = menu;

    set_parameters();
}

void Menu::Start() {
    refresh();
    draw_logo();
    draw_content();

    while(state == menu) {
        key_handler();
        draw_content();
    }
}

void Menu::next_item() {
    uint8_t button = (uint8_t)current_button;
    if (current_button + 1 != (uint8_t)_last)
        button++;
    current_button = (Buttons)button;
}

void Menu::prev_item() {
    uint8_t button = (uint8_t)current_button;
    if (current_button != (uint8_t)play)
        button--;
    current_button = (Buttons)button;
}

void Menu::setting_increment() {

}

void Menu::setting_decrement() {

}

void Menu::key_handler() {
    int key;
    keypad(content, true);
    key = wgetch(content);
    
    switch(key) {
        case KEY_UP:
            prev_item();
            break;

        case KEY_DOWN:
            next_item();
            break;

        case KEY_RIGHT:
            setting_increment();
            break;

        case KEY_LEFT:
            setting_decrement();
            break;

        case '\n': //enter key (for some reason KEY_ENTER didn't work)
        case ' ': //spacebar
            switch(current_button) {
                case play:
                    state = active;
                    break;

                case load_game:
                    // TODO: load game
                    break;

                case options:
                    // TODO: options
                    break;

                case quit:
                    exit(0);
                    break;
            }
            break;

        case '\e':  //ESC key
            exit(0);
            break;
    }
}
