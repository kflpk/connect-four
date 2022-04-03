#include <ncurses.h>

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