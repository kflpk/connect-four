#pragma once

#include <cinttypes>
#include <memory>
#include <vector>

using std::uint8_t;
using std::uint16_t;

class Board {
    private:
        uint16_t rows;
        uint16_t columns;
        uint16_t victory_condition;
        std::vector<uint8_t> content;
        bool diagonal_check(uint8_t player);

    public:
        Board(uint8_t board_rows, uint8_t board_columns);
        Board();
        uint16_t get_columns(void);
        uint16_t get_rows(void);
        std::vector<uint8_t>::iterator operator[] (int index);
        bool drop_chip(uint16_t col, uint8_t player);
        uint8_t check_victory();
        void clear();
        void printbrd();

};