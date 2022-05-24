#include "board.h"

#include <iostream>
#include <cinttypes>
#include <array>
#include <vector>
#include <memory>


Board::Board(uint8_t board_rows, uint8_t board_columns)  {
    this->victory_condition = 4;
    rows = board_rows;
    columns = board_columns;
    content.resize(rows * columns);

    for(int i = 0; i < rows * columns; i++)
        content[i] = 0;
}

Board::Board() {
    this->victory_condition = 4;
    this->rows = 5;
    this->columns = 7;
    this->content.resize(rows * columns);
 
    for(int i = 0; i < rows * columns; i++)
        this->content[i] = 0;
}

// getters
uint16_t Board::get_columns(void) { return columns; }
uint16_t Board::get_rows(void) { return rows; }

// setters
void Board::set_dimensions(uint16_t rows, uint16_t columns) {
    this->columns = columns;
    this->rows = rows;

    content.resize(rows * columns);

    (*this).clear();
}

void Board::set_victory_condition(uint16_t condition) {
    this->victory_condition = condition;
}

bool Board::drop_chip(uint16_t col, uint8_t player) {
    if(col > this->columns)
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
    for(uint16_t row_start = 0; row_start <= rows - victory_condition; row_start++) {
        for(uint16_t col_start = 0; col_start <= columns - victory_condition; col_start++) {
            streak = 0;
            for(uint16_t diag = 0; diag < victory_condition; diag++) {
                if( (*this)[row_start + diag][col_start + diag] == player )
                    streak++;
                if(streak == victory_condition)
                    return (*this)[row_start][col_start];
            }
        }
    }

    // top-right to bottom-left diagonal detection
    for(uint16_t row_start = 0; row_start <= rows - victory_condition; row_start++) {
        for(uint16_t col_start = columns - 1; col_start >= victory_condition - 1; col_start--) {
            streak = 0;
            for(uint16_t diag = 0; diag < victory_condition; diag++) {
                if( (*this)[row_start + diag][col_start - diag] == player )
                    streak++;
                if(streak == victory_condition)
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
    for(uint16_t row = 0; row < this->rows; row++) {
        for(uint16_t col = 0; col < this->columns; col++) {
            if(prev == (*this)[row][col] && (*this)[row][col] != 0)  {
                streak++;
            }
            else {
                prev = (*this)[row][col];
                streak = 1;
            }

            if(streak == victory_condition) {
                return prev;
            }
        }
        prev = 0;
        streak = 0;
    }

    // Vertical line detection
    for(uint16_t col = 0; col < this->columns; col++) {
        for(uint16_t row = 0; row < this->rows; row++) {
            if(prev == (*this)[row][col] && (*this)[row][col] != 0)  {
                streak++;
            }
            else {
                prev = (*this)[row][col];
                streak = 1;
            }

            if(streak == victory_condition)
                return prev;

        }
        prev = 0;
        streak = 0;
    }

    return 0;
}

// A function for debbuging purposes printing board content in plain text to stdout
void Board::printbrd() {
    for(uint16_t i = 0; i < rows; i++) {
        for(uint16_t j = 0; j < columns; j++) {
            if((*this)[i][j])
                std::cout << (int)(*this)[i][j] << " ";
            else
                std::cout << "  ";
        }
        std::cout << std::endl;
    }
}

std::vector<uint8_t>::iterator Board::operator[] (int index) {
    return this->content.begin() + index * this->columns;
}
