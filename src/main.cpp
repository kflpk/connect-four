#include <iostream>
#include <sys/ioctl.h>
#include <ncurses.h>
#include "menu.h"

int main() {
    //Menu menu;
    //menu.Draw();

    initscr();

    getch();

    endwin();
}