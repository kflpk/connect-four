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
        // Current game state
        uint8_t current_player = 1;
        PauseButtons current_button;
        uint16_t focused_column;
        Colors player_colors;
        Board board;                  // game board
        GameState state;              // stores current game state (whether in menu or game screen)

        // Dimensions for drawing the game screen
        uint32_t width, height;
        uint32_t cell_width, cell_height;
        uint32_t border_width = 2, border_height = 1;
        uint32_t pause_width, pause_height;

        
        // Windows
        WINDOW* indicators_win; // window for indicators and game info
        WINDOW* board_win;      // window for rendering the board
        WINDOW* pause_win;      // window for pause menu

        // offsets for offsets in indicator window
        uint32_t _ind_ver_off = 3;
        uint32_t _ind_hor_off = 5;


        // =========================
        // | Function declarations |
        // =========================
        
        // Function for drawing
        void draw_frame();
        void draw_board();
        void draw_tile(uint16_t row, uint16_t col, uint16_t off_y, uint16_t off_x);
        void draw_indicators();
        void draw_pause();
        void display_win_screen(uint8_t player);

        // Functions for navigation
        void next_column();
        void prev_column();
        void next_option();
        void prev_option();
        void key_handler();
        
        // Other functions
        void switch_player();
        bool load_game(const std::string& path);
        bool validate_size();

    public:
        Game();
        void update_dimensions();                       // updates dimensions of internal windows according to the terminal size
        bool save_game(const std::string& path);        // saves the game to file passed as argument
        bool set_parameters(GameParameters parameters); // sets game parameters according to the argument passed
        void Start();                                   // starts the game loop
};