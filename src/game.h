#pragma once

#include <cinttypes>
#include <ncurses.h>
#include "board.h"
#include "menu.h"
#include "extras.h"

struct Colors {
    int player1 = 0;
    int player2 = 0;
};

class Game {
    private:
        uint16_t width, height;
        uint8_t current_player = 1;
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
        void draw_tile(uint16_t row, uint16_t col, 
                       uint16_t ch,  uint16_t cw,
                       uint16_t off_y, uint16_t off_x);
        void draw_indicators();
        void next_column();
        void prev_column();
        void key_handler();
        void set_parameters(GameParameters parameters);
        void switch_player();
        void display_victory_screen(uint8_t player);
    public:
        Game();
        void Start();
        void Loop();
};