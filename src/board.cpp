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

uint8_t Board::check_victory() {
    uint16_t streak = 0;
    uint16_t prev = 0;

    for(uint16_t row = 0; row < this->rows; row++) {
        for(uint16_t col = 0; col < this->columns; col++) {
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

std::vector<uint8_t>::iterator Board::operator[] (int index) {
    return this->content.begin() + index * this->columns;
}
