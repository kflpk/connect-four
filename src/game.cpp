
#include <map>
#include <filesystem>
#include <cstdlib>
#include <fstream>
#include "color.h"
#include "game.h"
#include "extras.h"

Game::Game() {
    getmaxyx(stdscr, height, width);
}

void Game::update_dimensions() {
    getmaxyx(stdscr, height, width);

    // indicator window dimensions
    uint16_t _ind_height = 7;

    // pause window dimensions
    pause_width = 17;
    pause_height = 10;

    uint32_t pause_horizontal_offset = (width - pause_width) / 2;
    uint32_t pause_vertical_offset = (height - pause_height) / 2;

    // cell sizes in characters for board drawing
    cell_width  = 7;
    cell_height = 3;

    // window initializations
    indicators_win = newwin(_ind_height, width, 0, 0);
    board_win = newwin(height - _ind_height + 1, width, _ind_height - 1, 0);
    pause_win = newwin(pause_height, pause_width, pause_vertical_offset, pause_horizontal_offset);
}

bool Game::set_parameters(GameParameters parameters) {
    update_dimensions();

    if(parameters.load_save) {
        if(load_game(parameters.save_path) == false) {
            warning("Error: file not found");
            return false;
        }
        if(parameters.save_path == ".autosave.bin")
            std::filesystem::remove(".autosave.bin");
    }
    else {
        if(parameters.rows != 0 && parameters.columns != 0) 
            board.set_dimensions(parameters.rows, parameters.columns);

        if(parameters.victory_condition != 0)
            board.set_victory_condition(parameters.victory_condition);
    }

    player_colors.player1 = parameters.player1_color;
    player_colors.player2 = parameters.player2_color;

    focused_column = board.get_columns() / 2;
    state = active;
    return true;
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

    uint32_t board_width  = board.get_columns() * (cell_width + border_width) + border_width;
    // uint32_t board_height = board.get_rows() * (cell_height + 1);

    uint32_t horizontal_offset = (board_win_width  - board_width ) / 2;
    uint32_t vertical_offset = 3;

    // Placing color-rendered rectangles on the board according to player
    for(uint32_t row = 0; row < board.get_rows(); row++)
        for(uint32_t col = 0; col < board.get_columns(); col++)
            draw_tile(row, col, vertical_offset, horizontal_offset);

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

void Game::draw_tile(uint16_t row, uint16_t col, uint16_t off_y, uint16_t off_x) {
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

    uint16_t indicators_win_width;
    uint16_t indicators_win_height;

    getmaxyx(indicators_win, indicators_win_height, indicators_win_width);

    uint32_t board_width  = board.get_columns() * (cell_width + border_width) + border_width;

    uint32_t horizontal_offset = (indicators_win_width  - board_width ) / 2;

    _ind_hor_off = horizontal_offset + 2;

    // TODO: Add spacing vars
    for(uint32_t col = 0; col < board.get_columns(); col++) {
        wmove(indicators_win, _ind_ver_off, _ind_hor_off + 9 * col);
        wprintw(indicators_win, "[%c]", col == focused_column ? 'v' : ' ');
    }

    mvwprintw(indicators_win, _ind_ver_off + 2, (indicators_win_width - 22) / 2, "Current player: ");

    wattroff(indicators_win, COLOR_PAIR(PAIR_DEFAULT));

    if(current_player == 1) {
        wattron(indicators_win, COLOR_PAIR(PAIR_BLUE));
        mvwprintw(indicators_win, _ind_ver_off + 2, (indicators_win_width - 22) / 2 + 16, "Blue");
    }
    else if(current_player == 2) {
        wattron(indicators_win, COLOR_PAIR(PAIR_ORANGE));
        mvwprintw(indicators_win, _ind_ver_off + 2, (indicators_win_width - 22) / 2 + 16, "Orange");
    }
}

void Game::draw_pause() {
    std::map<PauseButtons, std::string> labels;

    labels[pause_resume] = "Resume";
    labels[pause_save]   = "Save game";
    labels[pause_quit]   = "Main menu";

    uint32_t left_offset = 2;
    uint32_t top_offset  = 3;

    wattron(pause_win, COLOR_PAIR(PAIR_DEFAULT));
    wfill(pause_win, 0);
    box(pause_win, 0, 0);
    wmove(pause_win, 1, 3);
    wprintw(pause_win, "Game paused");


    for(int button = play; button != pause_last; button++) {
        wmove(pause_win, top_offset + 2 * button, left_offset);
        wprintw(pause_win, "[%c] %s", ((PauseButtons)button == current_button) ? 'x' : ' ',
        labels[(PauseButtons)button].c_str());
    }

    wattroff(pause_win, COLOR_PAIR(PAIR_DEFAULT));


    wrefresh(indicators_win); // ugly bug-fix, because indicators window would disappear in the pause menu
    wrefresh(pause_win);
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

bool Game::validate_size() {
    uint32_t board_char_height = cell_height * board.get_rows() + (board.get_rows() + 1) * border_height;
    uint32_t board_char_width = cell_width * board.get_columns() + (board.get_columns() + 1) * border_width;

    uint32_t board_win_height;
    uint32_t board_win_width;

    getmaxyx(board_win, board_win_height, board_win_width);

    if(board_win_height - 4 < board_char_height || board_win_width - 2 < board_char_width)
        return false;

    return true;
}

void Game::display_victory_screen(uint8_t player) {
    //cleanup();
    uint32_t win_width = 25;
    uint32_t win_height = 8;

    WINDOW* win_screen = newwin(win_height, win_width, (height - win_height) / 2, (width - win_width) / 2);
    wattron(win_screen, COLOR_PAIR(PAIR_DEFAULT));

    wfill(win_screen, 0);
    box(win_screen, 0, 0);
    wmove(win_screen, 2, 4);
    wprintw(win_screen, "Player ");

    if(player == 1) {
        wattron(win_screen, COLOR_PAIR(PAIR_BLUE));
        wprintw(win_screen, "Blue");
        wattroff(win_screen, COLOR_PAIR(PAIR_BLUE));
    } else if(player == 2) {
        wattron(win_screen, COLOR_PAIR(PAIR_ORANGE));
        wprintw(win_screen, "Orange");
        wattroff(win_screen, COLOR_PAIR(PAIR_ORANGE));
    }
    wattron(win_screen, COLOR_PAIR(PAIR_DEFAULT));
    wprintw(win_screen, " won!");
    
    wmove(win_screen, 4, 6);
    wprintw(win_screen, "Press any key");
    wmove(win_screen, 5, 6);
    wprintw(win_screen, "to continue...");
    wattroff(win_screen, COLOR_PAIR(PAIR_DEFAULT));

    wrefresh(win_screen);

    getch();
}

void Game::next_option() {
    uint8_t button = (uint8_t)current_button;
    if (current_button + 1 != (uint8_t)pause_last)
        button++;
    current_button = (PauseButtons)button;
}

void Game::prev_option() {
    uint8_t button = (uint8_t)current_button;
    if (current_button != (uint8_t)pause_resume)
        button--;
    current_button = (PauseButtons)button;
}

void Game::key_handler() {
    int key;

    if(state == active) {
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
                    switch_player();
                }
                break;

            case 27:  //ESC key
            case  'p':
                state = paused;
                current_button = pause_resume;
                break;
        }
    } else if(state == paused) {
        keypad(pause_win, true);
        key = wgetch(pause_win);

        switch(key) {
            case KEY_LEFT:
            case KEY_UP:
            case 'k':
                prev_option();
                break;

            case KEY_RIGHT:
            case KEY_DOWN:
            case 'j':
                next_option();
                break;

            case '\n': //enter key (for some reason KEY_ENTER didn't work)
            case ' ': //spacebar
                switch(current_button) {
                    case pause_resume:
                        state = active;
                        break;

                    case pause_save:
                        save_game("save.bin");
                        warning("Game state saved to 'save.bin'");
                        break;

                    case pause_quit:
                        state = menu;
                        break;
                    case pause_last:
                    break;
                }
                break;

            case 27:  //ESC key
            case  'p':
                state = active;
                break;
        }
    }
}

void Game::Start() {
    while(true) {
        update_dimensions();
        draw_frame();
        draw_indicators();
        draw_board();

        if(!validate_size()) {
            warning("Error: The terminal window is too small to render the board of this size. Please change the board dimensions or resize the terminal.");
            break;
        }

        if (state == paused) {
            draw_pause();
        } else if(state == menu) {
            break;
        }

        key_handler();

        if(uint8_t winner = board.check_victory()) {
            draw_board();
            display_victory_screen(winner);
            break;
        }
    }
}

bool Game::save_game(const std::string& path) {
    
    // Prepare the binary contents;
    size_t file_size = 8 + board.get_columns() * board.get_rows();
    std::vector<char> data(file_size, 0);
    // std::shared_ptr<char[]> data = std::make_shared<char[]>(new char[file_size]);
    // ^ I tried using shared_ptr and pass data.get() to write but it kept on segfaulting


    data[0] = 1;
    data[1] = current_player;
    data[2] = board.get_rows();
    data[3] = board.get_rows() >> 8;
    data[4] = board.get_columns();
    data[5] = board.get_columns() >> 8;
    data[6] = board.get_win_condition();
    data[7] = board.get_win_condition() >> 8;


    size_t i = 8;
    for(int row = 0; row < board.get_rows(); row++) {
        for(int col = 0; col < board.get_columns(); col++) {
            data[i + 0] = board[row][col];
            i++;
        }
    }

    std::ofstream file(path, std::ios::binary);

    try {
        if(file.good()) {
            file.write(&data[0], file_size);
        }
    }
    catch(std::exception ex) {
        std::cout << ex.what();
    }

    file.close();
    return true;
}

bool Game::load_game(const std::string& path) {
    std::vector<char> preambule(8, 0);
    std::ifstream file(path, std::ios::binary);

    if(!file.is_open())
        return false;

    file.read(&preambule[0], 8);

    current_player = preambule[1];

    uint8_t rows = preambule[2] | (preambule[3] << 8);
    uint8_t cols = preambule[4] | (preambule[5] << 8);
    uint8_t win_condition = preambule[6] | (preambule[7] << 8);

    board.set_dimensions(rows, cols);
    board.set_victory_condition(win_condition);

    std::vector<char> board_content(rows * cols);

    try {
        file.read(&board_content[0], cols * rows);
    } catch(std::exception ex) {
        std::cout << ex.what();
    }
    
    for(size_t row = 0; row < rows; row++) {
        for(size_t col = 0; col < cols; col++) {
            board[row][col] = board_content[row * board.get_columns() + col];
        }
    }
    return true; 
}
