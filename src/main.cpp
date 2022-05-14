#include <iostream>
#include <sys/ioctl.h>
#include <ncurses.h>
#include "menu.h"
#include "game.h"
#include "color.h"
#include "extras.h"

int main() {
    #ifdef TESTING
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

    #else

    Board brd(30, 100);
    int x = 0;
    
    // brd.drop_chip(x, 7);
    // brd.drop_chip(x + 1, 7);
    // brd.drop_chip(x + 2, 7);
    // brd.drop_chip(x + 3, 8);

    // brd.drop_chip(x + 3, 1);
    
    // brd.drop_chip(x + 2, 2);
    // brd.drop_chip(x+ 2, 1);
    
    // brd.drop_chip(x + 1, 2);
    // brd.drop_chip(x + 1, 2);
    // brd.drop_chip(x + 1, 1);

    // brd.drop_chip(x + 0, 2);
    // brd.drop_chip(x + 0, 2);
    // brd.drop_chip(x + 0, 2);
    // brd.drop_chip(x + 0, 1);
    brd[15][5]  = 2;
    brd[16][6]  = 2;
    brd[17][7]  = 2;
    brd[18][8]  = 2;
    brd[19][9]  = 2;
    brd[20][10] = 2;
    brd[21][11] = 2;
    brd[22][12] = 2;
    brd[23][13] = 1;
    brd[24][14] = 1;
    brd[25][15] = 1;


    bool flag;
    uint8_t winner;
    
    for(uint16_t i = 0; i < brd.get_rows(); i++) {
        for(uint16_t j = 0; j < brd.get_columns(); j++) {
            if(brd[i][j])
                std::cout << (int)brd[i][j] << " ";
            else
                std::cout << "  ";
        }
        std::cout << std::endl;
    }

    for(uint16_t i = 0; i < brd.get_columns(); i++)
        std::cout << "| ";

    std::cout << std::endl;
    if( (winner = brd.check_victory()) ) {
        std::cout << "zwyciezyl gracz " << (int)winner << std::endl;
        return 0;
    }

    #endif
}
