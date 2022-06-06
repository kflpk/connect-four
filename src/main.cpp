#include <iostream>
#include <ncurses.h>
#include <csignal>
#include "menu.h"
#include "game.h"
#include "color.h"
#include "extras.h"
#include <filesystem>

static Menu* menu_ptr;
static Game* game_ptr;

static void handle_term(int sig) {
    game_ptr->save_game(".autosave.bin");
    cleanup();
    std::cout << "SIGTERM received, game state has been saved to '.autosave.bin'." << std::endl;
    exit(sig);
}

int main() {
    std::atexit(cleanup); // closes ncurses at exit so that the terminal output 
                          // is not broken at after program exits
    startup();

    Menu menu;
    Game game;

    menu_ptr = &menu;
    game_ptr = &game;

    signal(SIGTERM,  handle_term);

    while(true) {
        GameParameters params;
        
        if(std::filesystem::exists(".autosave.bin")) {
            params.load_save = true;
            params.save_path = ".autosave.bin";
        } else {
            params = menu.Start();
        }

        if(game.set_parameters(params))
            game.Start();
    }

    cleanup();
}
