#pragma once

#include <cinttypes>
#include <ncurses.h>
#include <string>
#include "board.h"
#include "menu.h"
#include "extras.h"

struct Colors {
    int player1 = 0;
    int player2 = 0;
};

enum PauseButtons : uint8_t {
    pause_resume,
    pause_save,
    pause_quit,
    pause_last
};

class Game {
    private:
        Board board;
        GameState state;

        uint32_t width, height;
        uint32_t pause_width, pause_height;
        uint8_t current_player = 1;

        PauseButtons current_button;
        uint16_t focused_column;
        Colors player_colors;
        
        // Windows
        WINDOW* indicators_win;
        WINDOW* board_win;
        WINDOW* pause_win;

        uint32_t _ind_ver_off = 3;
        uint32_t _ind_hor_off = 5;

        // Functions
        void draw_frame();
        void draw_board();
        void draw_tile(uint16_t row, uint16_t col, 
                       uint16_t ch,  uint16_t cw,
                       uint16_t off_y, uint16_t off_x);
        void draw_indicators();
        void draw_pause();
        void next_column();
        void prev_column();
        void next_option();
        void prev_option();
        void key_handler();
        void switch_player();
        void display_victory_screen(uint8_t player);
        bool save_game(const std::string& path);
    public:
        Game();
        void set_parameters(GameParameters parameters);
        void Start();
};