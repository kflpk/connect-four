#pragma once
#include "board.h"
#include <cinttypes>
#include "menu.h"

enum GameState {
    active,
    paused,
    menu
};

enum PlayerTurn {
    player1,
    player2
};

class Game {
    private:
        Board board;
        // game state
        GameState state;
        Menu menu;
        uint16_t focused_column;
    public:
        Game() {
            board = Board(5, 7);
            state = active; 
        }
        void Loop();
};