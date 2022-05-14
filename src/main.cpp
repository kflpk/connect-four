#include <iostream>
#include <sys/ioctl.h>
#include <ncurses.h>
#include "menu.h"
#include "game.h"
#include "color.h"
#include "extras.h"

int main() {
    /*
    std::atexit(cleanup); // closes ncurses at exit so that the terminal output 
                          // is not broken at after program exits
    startup();

    // Menu menu;
    // menu.Start();
    
    GameParameters params;

    Game game;
    game.set_parameters(params);
    game.draw_frame();
    game.draw_board();

    getch();

    cleanup();
    */

    Board brd(5, 7);
    for(uint16_t i = 0; i < brd.get_rows(); i++) {
        for(uint16_t j = 0; j < brd.get_columns(); j++) {
            std::cout << (int)brd[i][j] << " ";
        }
        std::cout << std::endl;
    }

    bool flag;
    uint8_t winner;
    for(uint16_t i = 0; (flag = brd.drop_chip(i, 1)); i++){
        if(flag)
            std::cout << "wrzucono rzeton\n";
    
        for(uint16_t i = 0; i < brd.get_rows(); i++) {
            for(uint16_t j = 0; j < brd.get_columns(); j++) {
                std::cout << (int)brd[i][j] << " ";
            }
            std::cout << std::endl;
        }

        std::cout << std::endl;
        if( (winner = brd.check_victory()) ) {
            std::cout << "zwyciezyl gracz " << (int)winner << std::endl;
            return 0;
        }
    }
    if(flag == false)
       std::cout<<"not enough room\n" ;
}
