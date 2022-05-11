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
        std::vector<uint8_t> content;

    public:
        Board(uint8_t rows, uint8_t columns);
        Board();
        uint16_t get_columns(void);
        uint16_t get_rows(void);
        std::vector<uint8_t>::iterator operator[] (int index);
        bool drop_chip(uint16_t col, uint8_t player);

};