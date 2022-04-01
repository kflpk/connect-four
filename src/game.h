#pragma once
#include "board.h"

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

};