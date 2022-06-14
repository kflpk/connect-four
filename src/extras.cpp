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

std::vector<std::string> word_wrap(std::string source, int line_length) {
    std::vector<std::string> lines;
    std::istringstream iss(source);

    std::string line;

    do
    {
        std::string word;
        iss >> word;

        if (line.length() + word.length() > (size_t)line_length)
        {
            lines.push_back(line);
            line.clear();
        }
        line += word + " ";

    } while (iss);

    if (!line.empty())
    {
        lines.push_back(line);
    }

    return lines;
}

void warning(std::string warning_content) {
    // return;
    WINDOW* warning_win;
    std::vector<std::string> lines;

    int window_width;
    int window_height;
    int warning_width = 38;
    int warning_height;

    getmaxyx(stdscr, window_height, window_width);

    lines = word_wrap(warning_content, warning_width - 4);
    warning_height = lines.size() + 6;

    int top_offset = (window_height - warning_height)/2;
    int left_offset = (window_width - warning_width)/2;

    // cleanup();
    // std::cout << "warning" << warning_height << "x" << warning_width << std::endl;
    // std::cout << "window" << window_height << "x" << window_width;
    // exit(0);

    warning_win = newwin(warning_height, warning_width, top_offset, left_offset);

    wattron(warning_win, COLOR_PAIR(PAIR_DEFAULT));
    wfill(warning_win, 0);
    box(warning_win, 0, 0);

    for(size_t i = 0; i < lines.size(); i++) {
        wmove(warning_win, 2 + i, 2);
        wprintw(warning_win, lines[i].c_str());
    }

    wmove(warning_win, lines.size() +  3, (warning_width - 29)/2);
    wprintw(warning_win, "Press any key to continue...");
    wattroff(warning_win, COLOR_PAIR(PAIR_DEFAULT));

    wrefresh(warning_win);
    getch();
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