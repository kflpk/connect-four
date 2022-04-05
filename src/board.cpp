#include <cinttypes>
#include <array>
#include <vector>
#include <memory>


class Board {
    private:
        // uints so that the value can not be negative
        std::uint16_t rows;
        uint16_t columns;
        std::vector<uint8_t> content;

    public:
        // Constructor
        Board(uint8_t board_rows, uint8_t board_columns)  {
            rows = board_rows;
            columns = board_columns;
            content.resize(rows * columns);
            for(int i = 0; i < rows * columns; i++)
                content[i] = 0;
        }
        Board() {
            this->rows = 5;
            this->columns = 7;
            this->content.resize(rows * columns);
            for(int i = 0; i < rows * columns; i++)
                this->content[i] = 0;
        }
        // getters
        uint16_t get_columns(void) { return columns; }
        uint16_t get_rows(void) { return rows; }
};