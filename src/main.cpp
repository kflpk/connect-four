#include <iostream>
#include <sys/ioctl.h>
#include <ncurses.h>
#include "menu.h"
#include "color.h"
#include "extras.h"

int main() {

    std::atexit(cleanup); // closes ncurses at exit so that the terminal output 
                          // is not broken at after program exits

    startup();

    Menu menu;
    menu.Start();

    // while (c != '\f') {
    //     menu.Draw();
    //     c = getch();

    //     if(c == 'j')
    //         menu.next_option();
    //     else if(c == 'k')
    //         menu.prev_option();
    //     else if(c == '\e')
    //         exit(0);
    // }

    cleanup();
}
