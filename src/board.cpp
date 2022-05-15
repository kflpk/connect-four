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

void Board::clear() {
    for(uint16_t i = 0; i < rows * columns; i++)
        content[i] = 0;
}

bool Board::diagonal_check(uint8_t player) {
    uint16_t streak;

    for(uint16_t rowStart = 0; rowStart < columns - 1 - victory_condition; rowStart++){
        streak = 0;
        int row, col;
        for( row = rowStart, col = 0; row < rows - 1 && col < columns - 1; row++, col++ ){
            if((*this)[row][col] == player){
                streak++;
                if(streak >= victory_condition) return 1;
            }
            else {
                streak = 0;
            }
        }
    }

    return 0;
}

uint8_t Board::check_victory() { 
    // TODO: add diagonal victory reckognition
    // TODO: save coordinates of the winning chips
    uint16_t streak = 0;
    uint16_t prev = 0;

    for(uint16_t row = 0; row < this->rows; row++) { // Detecting horizontal lines
        for(uint16_t col = 0; col < this->columns; col++) {
            if(prev == (*this)[row][col] && (*this)[row][col] != 0)  {
                streak++;
            }
            else {
                prev = (*this)[row][col];
                streak = 1;
            }

            if(streak == victory_condition) {
                // TODO: save winning tokens' coordinates to a vector for drawing
                return prev;
            }
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

    if(diagonal_check(1))
        return 1;
    else if(diagonal_check(2))        
        return 2;

    return 0;
}

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
