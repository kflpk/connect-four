#include <iostream>
#include <ncurses.h>
#include "menu.h"
#include "game.h"
#include "color.h"
#include "extras.h"

int main() {
    // std::atexit(cleanup); // closes ncurses at exit so that the terminal output 
    //                       // is not broken at after program exits
    // startup();

    std::string lorem = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Aenean vel tincidunt dui. Sed a pulvinar mi, ut ultricies risus. Integer interdum nibh non elit suscipit, vel mollis mi facilisis. Donec eget ultricies velit. Pellentesque a suscipit magna. Phasellus bibendum massa sit amet felis dignissim, eget pulvinar felis consequat. Nullam bibendum dictum neque vitae ornare. Donec vel nisl nec neque dapibus mattis non quis urna. Quisque molestie quam eget lacus euismod, a semper sem viverra. Curabitur feugiat vestibulum urna, tristique finibus lectus feugiat quis. Nulla neque ante, bibendum et neque sed, accumsan ornare metus. Nullam iaculis viverra dolor, vehicula mollis lectus.";
    std::vector<std::string> lines = word_wrap(lorem, 20);

    for(auto line : lines) {
        std::cout << line << std::endl;
    }
    exit(0);

    // Menu menu;
    // Game game;

    // while(true) {
    //     GameParameters params = menu.Start();

    //     game.set_parameters(params);
    //     game.Start();
    // }

    // cleanup();
}
