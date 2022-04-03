#pragma once

#include <inttypes.h>
#include <memory>
#include <vector>

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

};