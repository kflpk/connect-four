#pragma once

#include <cinttypes>
#include <ncurses.h>
#include "board.h"
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

struct Colors {
    int player1 = 0;
    int player2 = 0;
};

class Game {
    private:
        uint16_t width, height;

        Board board;
        GameState state;
        Menu menu;
        uint16_t focused_column;
        Colors player_colors;
        WINDOW* indicators_win;
        WINDOW* board_win;

    public: 
        void draw_frame();
        void draw_board();
        void draw_tiles();
        void key_handler();
        void set_parameters(GameParameters parameters);
    public:
        Game();
        void Start();
        void Loop();
};