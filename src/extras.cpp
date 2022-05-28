#include <ncurses.h>
#include <sstream>
#include <iostream>
#include "extras.h"
#include "color.h"

void wfill(WINDOW* win, char c) {
    if(c == 0) //space is filled by default
        c = ' ';

    char str[2] = {c, 0}; // dummy string because printw functions only take char* type
    int width, height;
    getmaxyx(win, height, width);
    for(int row = 0; row < height; row++) {
        for(int col = 0; col < width; col++) {
            mvwprintw(win, row, col, str);
        }
    }
}

std::vector<std::string> word_wrap(std::string source, int line_length) { // doesn't work yet
    std::stringstream splitter(source);
    std::string buffer;
    std::vector<std::string> content;
    std::vector<std::string> lines;

    size_t bufsize;

    while(splitter >> buffer) // splits the source string to strings with individual words
        content.push_back(buffer);

    for(size_t start = 0; start < content.size(); start++) {
        buffer = content[start];
        for(size_t word = start + 1; word < content.size(); word++) {
            bufsize = buffer.size() + 1 + content[word].size();
            if(bufsize < line_length) {
                buffer += (" " + content[word]);
            }
            else {
                start = word - 1;
                lines.push_back(buffer);
                break;
            }
            if(word == content.size() - 1) {
                lines.push_back(buffer);
                return lines;
                break;
            }
        }
    }

    return lines;
    
}

void warning(std::string warning_content) {

}

void init_theme() {
    init_color(COLOR_ORANGE,     900, 600,   0);
    init_color(COLOR_FRAME,      350, 350, 350);
    init_color(COLOR_BACKGROUND, 150, 150, 150);

    init_pair(PAIR_BLUE,    COLOR_BLUE,   COLOR_BACKGROUND);
    init_pair(PAIR_ORANGE,  COLOR_ORANGE, COLOR_BACKGROUND);
    init_pair(PAIR_FRAME,   COLOR_FRAME,  COLOR_FRAME);
    init_pair(PAIR_DEFAULT, COLOR_WHITE,  COLOR_BACKGROUND);
    init_pair(PAIR_PLAYER1, COLOR_ORANGE, COLOR_BLUE);
    init_pair(PAIR_PLAYER2, COLOR_BLUE,   COLOR_ORANGE);

    curs_set(0);
    //init_pair(PAIR_PLAYER1, COLOR_ORANGE)
}

void startup() {
    initscr();
    start_color();
    init_theme();
    noecho();
}

void cleanup() {
    noraw();
    echo();
    reset_shell_mode();
    endwin();
}