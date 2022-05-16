
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

    focused_column = 0;
}

void Game::draw_frame() {

    wattron(indicators_win, COLOR_PAIR(PAIR_DEFAULT));
    wfill(indicators_win, ' ');
    // box(indicators_win, 0 ,0);
    wattroff(indicators_win, COLOR_PAIR(PAIR_DEFAULT));

    // wattron(board_win, COLOR_PAIR(PAIR_DEFAULT));
    // wfill(board_win, ' ');
    // wborder(board_win, 0 ,0 ,0 , 0, ACS_LTEE, ACS_RTEE, 0, 0);
    // wattroff(board_win, COLOR_PAIR(PAIR_DEFAULT));

    wrefresh(indicators_win);
    // wrefresh(board_win);
}

void Game::draw_board() {
    wattron(board_win, COLOR_PAIR(PAIR_DEFAULT));
    wfill(board_win, ' ');
    // wborder(board_win, 'x','x','x', 'x', ACS_LTEE, ACS_RTEE, 0, 0);
    wborder(board_win, 0, 0, 0, 0, ACS_LTEE, ACS_RTEE, 0, 0);
    wattroff(board_win, COLOR_PAIR(PAIR_DEFAULT));


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

void Game::draw_indicators() {
    wattron(indicators_win, COLOR_PAIR(PAIR_DEFAULT));
    wfill(indicators_win, 0);
    // box(indicators_win, 0, 0);
    wborder(indicators_win, 0, 0, 0, 0, 0, 0, ACS_LTEE, ACS_RTEE);
    // wmove(indicators_win, 2, 2);
    // wprintw(indicators_win, "Columns: %i", focused_column);

    for(uint32_t col = 0; col < board.get_columns(); col++) {
        wmove(indicators_win, _ind_ver_off, _ind_hor_off + 5 * col);
        wprintw(indicators_win, "[%c]", col == focused_column ? 'v' : ' ');
    }

    wattroff(indicators_win, COLOR_PAIR(PAIR_DEFAULT));
}

void Game::next_column() {
    if(focused_column < board.get_columns() - 1) {
        focused_column++;
    }
}

void Game::prev_column() {
    if(focused_column > 0) {
        focused_column--;
    }
}

void Game::key_handler() {
    int key;
    keypad(indicators_win, true);
    key = wgetch(indicators_win);
    
    switch(key) {
        case KEY_LEFT:
        case KEY_UP:
        case 'k':
        case 'h':
            prev_column();
            break;

        case KEY_RIGHT:
        case KEY_DOWN:
        case 'j':
        case 'l':
            next_column();
            break;

        case '\n': //enter key (for some reason KEY_ENTER didn't work)
        case ' ': //spacebar
            if(board.drop_chip(focused_column, current_player)) {

            }
            break;

        case '\e':  //ESC key
            exit(0);
            break;
    }
}

void Game::Loop() {
    while(true) {
        draw_frame();
        draw_indicators();
        draw_board();
        key_handler();
    }
}