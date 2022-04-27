
#include "color.h"
#include "game.h"
#include "extras.h"

Game::Game() {
    getmaxyx(stdscr, height, width);
}

void Game::set_parameters(GameParameters parameters) {

    uint16_t _ind_height = 6;

    indicators_win = newwin(_ind_height, width, 0, 0);
    board_win = newwin(height - _ind_height + 1, width, _ind_height - 1, 0);

    player_colors.player1 = parameters.player1_color;
    player_colors.player2 = parameters.player2_color;

}

void Game::draw_frame() {

    wattron(indicators_win, COLOR_PAIR(PAIR_DEFAULT));
    wfill(indicators_win, ' ');
    box(indicators_win, 0 ,0);
    wattroff(indicators_win, COLOR_PAIR(PAIR_DEFAULT));

    wattron(board_win, COLOR_PAIR(PAIR_DEFAULT));
    wfill(board_win, ' ');
    wborder(board_win, 0 ,0 ,0 , 0, ACS_LTEE, ACS_RTEE, 0, 0);
    wattroff(board_win, COLOR_PAIR(PAIR_DEFAULT));

    wrefresh(indicators_win);
    wrefresh(board_win);
}

void Game::draw_board() {
    uint16_t board_win_width;
    uint16_t board_win_height;

    getmaxyx(board_win, board_win_height, board_win_width);

    uint16_t cell_width  = (board_win_width  - 3) / board.get_columns() - 1;
    uint16_t cell_height = (board_win_height - 3) / board.get_rows() - 1;

    cell_height = cell_width > (2 * cell_height) ? cell_height : cell_width;
    cell_width = 2 * cell_height;

    uint16_t board_width  = board.get_columns() * (cell_width + 1);
    uint16_t board_height = board.get_rows() * (cell_height + 1);

    uint16_t horizontal_offset = (board_win_width  - board_width ) / 2;
    uint16_t vertical_offset   = (board_win_height - board_height) / 2;

    for(uint32_t row = vertical_offset; row < vertical_offset + board_height; row++) {
        for(uint32_t col = horizontal_offset; col < horizontal_offset + board_width; col++) {
            wmove(board_win, row, col);
            wattron(board_win, COLOR_PAIR(PAIR_DEFAULT));
            wprintw(board_win, "x");
            wattroff(board_win, COLOR_PAIR(PAIR_DEFAULT));
        }
    }

    wrefresh(board_win);
}

void Game::draw_tiles() {

}

void Game::key_handler() {

}

void Game::Loop() {

}