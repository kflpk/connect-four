#include "board.h"

#include <iostream>
#include <cinttypes>
#include <array>
#include <vector>
#include <memory>


Board::Board(uint8_t board_rows, uint8_t board_columns)  {
    win_condition = 4;
    rows = board_rows;
    columns = board_columns;
    content.resize(rows * columns);

    for(int i = 0; i < rows * columns; i++)
        content[i] = 0;
}

Board::Board() {
    win_condition = 4;
    rows = 5;
    columns = 7;
    content.resize(rows * columns);
 
    for(int i = 0; i < rows * columns; i++)
        content[i] = 0;
}

// getters
uint16_t Board::get_columns(void) { return columns; }
uint16_t Board::get_rows(void) { return rows; }
uint16_t Board::get_win_condition() { return win_condition; }

// setters
void Board::set_dimensions(uint16_t r, uint16_t c) {
    columns = c;
    rows = r;

    content.resize(rows * columns);

    (*this).clear();
}

void Board::set_win_condition(uint16_t condition) {
    win_condition = condition;
}

bool Board::drop_chip(uint16_t col, uint8_t player) {
    if(col > columns)
        return false;

    for(uint16_t row = rows - 1; row < rows; row--) {
        if((*this)[row][col] == 0) {
            (*this)[row][col] = player;
            return true;
        }
    }

    return false;
}

void Board::clear() {
    for(uint16_t i = 0; i < rows * columns; i++)
        content[i] = 0;
}

bool Board::diagonal_check(uint8_t player) {
    // Diagonal line detection, returns if 'player' has a correct number of chips in line

    uint16_t streak = 0;

    // top-left to bottom-right diagonal detection
    for(uint16_t row_start = 0; row_start <= rows - win_condition; row_start++) {
        for(uint16_t col_start = 0; col_start <= columns - win_condition; col_start++) {
            streak = 0;
            for(uint16_t diag = 0; diag < win_condition; diag++) {
                if( (*this)[row_start + diag][col_start + diag] == player )
                    streak++;
                if(streak == win_condition)
                    return (*this)[row_start][col_start];
            }
        }
    }

    // top-right to bottom-left diagonal detection
    for(uint16_t row_start = 0; row_start <= rows - win_condition; row_start++) {
        for(uint16_t col_start = columns - 1; col_start >= win_condition - 1; col_start--) {
            streak = 0;
            for(uint16_t diag = 0; diag < win_condition; diag++) {
                if( (*this)[row_start + diag][col_start - diag] == player )
                    streak++;
                if(streak == win_condition)
                    return (*this)[row_start][col_start];
            }
        }
    }

    return 0;
}

uint8_t Board::check_victory() { 
    uint16_t streak = 0;
    uint16_t prev = 0;

    if(diagonal_check(1))
        return 1;
    else if(diagonal_check(2))        
        return 2;

    // Horizontal line detection
    for(uint16_t row = 0; row < rows; row++) {
        for(uint16_t col = 0; col < columns; col++) {
            if(prev == (*this)[row][col] && (*this)[row][col] != 0)  {
                streak++;
            }
            else {
                prev = (*this)[row][col];
                streak = 1;
            }

            if(streak == win_condition) {
                return prev;
            }
        }
        prev = 0;
        streak = 0;
    }

    // Vertical line detection
    for(uint16_t col = 0; col < columns; col++) {
        for(uint16_t row = 0; row < rows; row++) {
            if(prev == (*this)[row][col] && (*this)[row][col] != 0)  {
                streak++;
            }
            else {
                prev = (*this)[row][col];
                streak = 1;
            }

            if(streak == win_condition)
                return prev;

        }
        prev = 0;
        streak = 0;
    }

    return 0;
}

// A function for debbuging purposes printing board content in plain text to stdout
// void Board::printbrd() {
//     for(uint16_t i = 0; i < rows; i++) {
//         for(uint16_t j = 0; j < columns; j++) {
//             if((*this)[i][j])
//                 std::cout << (int)(*this)[i][j] << " ";
//             else
//                 std::cout << "  ";
//         }
//         std::cout << std::endl;
//     }
// }

std::vector<uint8_t>::iterator Board::operator[] (int index) {
    return content.begin() + index * columns;
}
