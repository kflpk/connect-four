
#include "color.h"
#include "game.h"
#include "extras.h"

Game::Game() {
    getmaxyx(stdscr, height, width);
}

void Game::set_parameters(GameParameters parameters) {
    uint16_t _ind_height = 7;

    indicators_win = newwin(_ind_height, width, 0, 0);
    board_win = newwin(height - _ind_height + 1, width, _ind_height - 1, 0);

    player_colors.player1 = parameters.player1_color;
    player_colors.player2 = parameters.player2_color;

    focused_column = 0;
}

void Game::switch_player() {
    if(current_player == 1)
        current_player = 2;
    else
        current_player = 1;
}

void Game::draw_frame() {
    wattron(indicators_win, COLOR_PAIR(PAIR_DEFAULT));
    wfill(indicators_win, ' ');
    wattroff(indicators_win, COLOR_PAIR(PAIR_DEFAULT));

    wrefresh(indicators_win);
    wrefresh(board_win);
}

void Game::draw_board() {
    wattron(board_win, COLOR_PAIR(PAIR_DEFAULT));
    wfill(board_win, ' ');
    wborder(board_win, 0, 0, 0, 0, ACS_LTEE, ACS_RTEE, 0, 0);
    wattroff(board_win, COLOR_PAIR(PAIR_DEFAULT));


    uint16_t board_win_width;
    uint16_t board_win_height;

    getmaxyx(board_win, board_win_height, board_win_width);

    uint32_t cell_width  = 7;
    uint32_t cell_height = 3;

    uint32_t board_width  = board.get_columns() * (cell_width + 1);
    uint32_t board_height = board.get_rows() * (cell_height + 1);

    uint32_t horizontal_offset = (board_win_width  - board_width ) / 2;
    uint32_t vertical_offset   = (board_win_height - board_height) / 2;

    // Placing color-rendered rectangles on the board according to player
    for(uint32_t row = 0; row < board.get_rows(); row++)
        for(uint32_t col = 0; col < board.get_columns(); col++)
            draw_tile(row, col, cell_height, cell_width, vertical_offset, horizontal_offset);

    // Drawing the frame around the tokens
    // TODO: add variables for spacing between chips, now they are hard coded an the code is hard to read
    for(uint32_t y = 0; y <= board.get_rows() * (cell_height + 1); y++) {
        for(uint32_t x = 0; x < board.get_columns() * (cell_width + 2) + 2; x++) {
            if(y % (cell_height + 1) == 0 || x % (cell_width + 2) == 0 || x % (cell_width + 2) == 1) {
                wmove(board_win, y + vertical_offset - 1, x + horizontal_offset - 2);
                wattron(board_win, COLOR_PAIR(PAIR_FRAME));
                wprintw(board_win, "x");
                wattroff(board_win, COLOR_PAIR(PAIR_FRAME));
            }
        }
    }

    wrefresh(board_win);
}

void Game::draw_tile(uint16_t row, uint16_t col, uint16_t cell_height, uint16_t cell_width, 
uint16_t off_y, uint16_t off_x) {
    for(uint16_t y = 0; y < cell_height; y++) {
        for(uint16_t x = 0; x < cell_width; x++) {
            wmove(board_win, (row * (cell_height + 1)) + off_y + y, (col * (cell_width + 2)) + off_x + x);

            if(board[row][col] == 1) {
                wattron(board_win, COLOR_PAIR(PAIR_PLAYER1));
                wprintw(board_win, " ");
                wattroff(board_win, COLOR_PAIR(PAIR_PLAYER1));
            } else if (board[row][col] == 2) {
                wattron(board_win, COLOR_PAIR(PAIR_PLAYER2));
                wprintw(board_win, " ");
                wattroff(board_win, COLOR_PAIR(PAIR_PLAYER2));
            } else {
                wattron(board_win, COLOR_PAIR(PAIR_DEFAULT));
                wprintw(board_win, " ");
                wattroff(board_win, COLOR_PAIR(PAIR_DEFAULT));
            }
        }
    }
}

void Game::draw_indicators() {
    wattron(indicators_win, COLOR_PAIR(PAIR_DEFAULT));
    wfill(indicators_win, 0);
    wborder(indicators_win, 0, 0, 0, 0, 0, 0, ACS_LTEE, ACS_RTEE);
    wmove(indicators_win, 1, 1);
    wprintw(indicators_win, "Columns: %i", focused_column);



    uint16_t indicators_win_width;
    uint16_t indicators_win_height;

    getmaxyx(indicators_win, indicators_win_height, indicators_win_width);

    uint32_t cell_width  = 7;

    uint32_t board_width  = board.get_columns() * (cell_width + 1);

    uint32_t horizontal_offset = (indicators_win_width  - board_width ) / 2;

    _ind_hor_off = horizontal_offset + 2;

    // TODO: Add spacing vars
    for(uint32_t col = 0; col < board.get_columns(); col++) {
        wmove(indicators_win, _ind_ver_off, _ind_hor_off + 9 * col);
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

void Game::display_victory_screen(uint8_t player) {
    //cleanup();
    uint32_t win_width = 25;
    uint32_t win_height = 8;

    WINDOW* win_screen = newwin(win_height, win_width, (height - win_height) / 2, (width - win_width) / 2);
    wattron(win_screen, COLOR_PAIR(PAIR_DEFAULT));

    wfill(win_screen, 0);
    box(win_screen, 0, 0);
    wmove(win_screen, 1, 6);
    wprintw(win_screen, "Player %d won!", (int)player);
    
    wmove(win_screen, 4, 6);
    wprintw(win_screen, "Press any key");
    wmove(win_screen, 5, 6);
    wprintw(win_screen, "to continue...");
    wattroff(win_screen, COLOR_PAIR(PAIR_DEFAULT));

    wrefresh(win_screen);

    getch();
    exit(0);
    //exit(0);
}

void Game::key_handler() {
    int key;
    keypad(indicators_win, true);
    key = wgetch(indicators_win);
    uint8_t winner;
    
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
                switch_player();
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
        if(uint8_t winner = board.check_victory()) {
            draw_board();
            display_victory_screen(winner);
        }
    }
}
