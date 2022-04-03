#include <iostream>
#include <sys/ioctl.h>
#include <ncurses.h>
#include "menu.h"
#include "color.h"

int main() {

    initscr();


    start_color();
    
    init_pair(PAIR_FRAME, COLOR_BLUE, COLOR_BLUE);
    noecho();

    Menu menu;
    menu.Draw();
    
    getch();

    endwin();
}