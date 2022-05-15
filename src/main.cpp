#include <iostream>
#include <sys/ioctl.h>
#include <ncurses.h>
#include "menu.h"
#include "game.h"
#include "color.h"
#include "extras.h"

int main() {
    std::atexit(cleanup); // closes ncurses at exit so that the terminal output 
                          // is not broken at after program exits
    startup();

    // Menu menu;
    // menu.Start();
    
    GameParameters params;

    Game game;
    game.set_parameters(params);
    // game.draw_frame();
    // game.draw_board();
    game.Loop();

    getch();

    cleanup();


    // Board brd(30, 100);
    
    // uint8_t winner;
    

    // for(uint16_t i = 0; i < brd.get_columns(); i++)
    //     std::cout << "| ";

    // std::cout << std::endl;
    // if( (winner = brd.check_victory()) ) {
    //     std::cout << "zwyciezyl gracz " << (int)winner << std::endl;
    //     return 0;
    // }
}
