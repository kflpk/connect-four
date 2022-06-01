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
        for(int setting = setting_rows; setting != setting_end; setting++) {
            wmove(content, top_offset + 2 * setting, left_offset);
            if(setting < setting_done) {
                wprintw(content, "%s ", setting_labels[(Settings)setting].c_str());
                waddch(content, current_setting == (Settings)setting ? ACS_LARROW : ' ');
                switch((Settings)setting) {
                    case setting_rows:
                        wprintw(content, "%02d", temp_perameters.rows);
                        break;
                    case setting_cols:
                        wprintw(content, "%02d", temp_perameters.columns);
                        break;
                    case setting_win:
                        wprintw(content, "%02d", temp_perameters.victory_condition);
                        break;
                    default:
                        break;
                }
                waddch(content, current_setting == (Settings)setting ? ACS_RARROW : ' ');
            }
            else {
                wprintw(content, "[%c] %s ", ((Settings)setting == current_setting) ? 'x' : ' ',
                setting_labels[(Settings)setting].c_str());
            }
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

    setting_labels[setting_rows]  = "Rows         ";
    setting_labels[setting_cols]  = "Columns      ";
    setting_labels[setting_win]   = "Win condition";
    setting_labels[setting_done] = "Done";
    setting_labels[setting_back]  = "Back";

    current_button = play;
    current_setting = setting_rows;
    state = menu;

    set_parameters();
}

GameParameters Menu::Start() {
    state = menu;
    refresh();
    draw_logo();
    draw_content();

    while(state == menu || state == menu_settings) {
        key_handler();
        draw_content();
    }

    return parameters;
}

void Menu::next_item() {
    if(state == menu) {
        uint8_t button = (uint8_t)current_button;
        if (current_button + 1 != (uint8_t)_last)
            button++;
        current_button = (Buttons)button;
    } else if(state == menu_settings) {
        uint8_t setting = (uint8_t)current_setting;
        if (current_setting + 1 != (uint8_t)setting_end)
            setting++;
        current_setting = (Settings)setting;
    }
}

void Menu::prev_item() {
    if(state == menu) {
        uint8_t button = (uint8_t)current_button;
        if (current_button != (uint8_t)play)
            button--;
        current_button = (Buttons)button;
    } else if(state == menu_settings) {
        uint8_t setting = (uint8_t)current_setting;
        if (current_setting != (uint8_t)setting_rows)
            setting--;
        current_setting = (Settings)setting;
    }
}

void Menu::setting_increment() {
    switch(current_setting) {
        case setting_rows:
            if(temp_perameters.rows < 100)
                temp_perameters.rows++;
            break;

        case setting_cols:
            if(temp_perameters.columns < 100)
                temp_perameters.columns++;
            break;

        case setting_win:
            if(temp_perameters.victory_condition < 100)
                temp_perameters.victory_condition++;
            break;
        
        default: 
            break;
    }
}

void Menu::setting_decrement() {
    switch(current_setting) {
        case setting_rows:
            if(temp_perameters.rows > 1)
                temp_perameters.rows--;
            break;

        case setting_cols:
            if(temp_perameters.columns > 1)
                temp_perameters.columns--;
            break;

        case setting_win:
            if(temp_perameters.victory_condition > 2)
                temp_perameters.victory_condition--;
            break;
        
        default: 
            break;
    }

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
            if(state == menu) 
                switch(current_button) {
                    case play:
                        // warning("The window is too small to draw a board of that dimensions. Please resize the terminal window or decrease the font size and restart the game");
                        state = active;
                        break;

                    case load_game:
                        parameters.load_save = true;
                        parameters.save_path = "save.bin";
                        state = active;
                        break;

                    case options:
                        temp_perameters = parameters;
                        state = menu_settings;
                        break;

                    case quit:
                        exit(0);
                        break;

                    default:
                        break;
                }

            else if(state == menu_settings) 
                switch(current_setting) {

                    case setting_done:
                        parameters = temp_perameters;
                        state = menu;
                        break;

                    case setting_back:
                        state = menu;
                        break;

                    default:
                        break;
                }
            break;

        case 27:  //ESC key
            if(state == menu_settings)
                state = menu;
            else
                exit(0);
            break;
        case KEY_BACKSPACE:
            if(state == menu_settings)
                state = menu;
            break;
    }
}
