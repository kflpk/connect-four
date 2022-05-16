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
        uint8_t current_player;
        Board board;
        GameState state;
        Menu menu;
        uint16_t focused_column;
        Colors player_colors;
        WINDOW* indicators_win;
        WINDOW* board_win;

        uint32_t _ind_ver_off = 3;
        uint32_t _ind_hor_off = 5;


    public: 
        void draw_frame();
        void draw_board();
        void draw_tiles();
        void draw_indicators();
        void next_column();
        void prev_column();
        void key_handler();
        void set_parameters(GameParameters parameters);
    public:
        Game();
        void Start();
        void Loop();
};