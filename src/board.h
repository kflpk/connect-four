#pragma once

#include <cinttypes>
#include <memory>
#include <vector>

using std::uint8_t;
using std::uint16_t;
using std::uint32_t;

class Board {
    private:
        uint16_t rows;
        uint16_t columns;
        uint16_t win_condition;
        std::vector<uint8_t> content;
        bool diagonal_check(uint8_t player);

    public:
        // Constructors
        Board(uint8_t board_rows, uint8_t board_columns);
        Board();

        // Getters
        uint16_t get_columns(void);
        uint16_t get_rows(void);
        uint16_t get_win_condition();

        // Setters
        void set_dimensions(uint16_t rows, uint16_t columns);
        void set_win_condition(uint16_t condition);
        std::vector<uint8_t>::iterator operator[] (int index);

        // Other functions
        bool drop_chip(uint16_t col, uint8_t player);
        uint8_t check_victory();
        void clear();

};