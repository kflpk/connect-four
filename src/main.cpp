#include <iostream>
#include <sys/ioctl.h>
#include <ncurses.h>
#include "menu.h"
#include "color.h"

void init_theme() {
    init_color(COLOR_ORANGE, 900, 600, 0);
    init_color(COLOR_FRAME, 750, 750, 750);
    init_color(COLOR_BACKGROUND, 150, 150, 150);

    init_pair(PAIR_BLUE, COLOR_BLUE, COLOR_BACKGROUND);
    init_pair(PAIR_ORANGE, COLOR_ORANGE, COLOR_BACKGROUND);
    init_pair(PAIR_FRAME, COLOR_FRAME, COLOR_FRAME);
    init_pair(PAIR_DEFAULT, COLOR_WHITE, COLOR_BACKGROUND);
    init_pair(PAIR_PLAYER1, COLOR_ORANGE, COLOR_BLUE);
    init_pair(PAIR_PLAYER2, COLOR_BLUE, COLOR_ORANGE);

    curs_set(0);
    //init_pair(PAIR_PLAYER1, COLOR_ORANGE)
}

int main() {

    initscr();

    
    start_color();
    
    init_theme();
    noecho();

    Menu menu;
    menu.Draw();
    
    
    getch();

    //noraw();
    //echo();
    //reset_shell_mode();
    endwin();
}