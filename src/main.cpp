#include <iostream>
#include <ncurses.h>
#include "menu.h"
#include "game.h"
#include "color.h"
#include "extras.h"

int main() {
    std::atexit(cleanup); // closes ncurses at exit so that the terminal output 
                          // is not broken at after program exits
    startup();

    Menu menu;
    menu.Start();

    GameParameters params;

    Game game;
    game.set_parameters(params);
    game.Start();

    cleanup();
}
