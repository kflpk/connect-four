#include <inttypes.h>
#include <array>
#include <memory>

class Board {
    private:
        // uints so that the value can not be negative
        uint16_t rows;
        uint16_t columns;
        std::shared_ptr<uint8_t[]> content;

    public:
        // Constructor
        Board(uint8_t rows, uint8_t columns) {
            this->rows = rows;
            this->columns = columns;
            this->content = std::make_shared<uint8_t[]>(rows * columns);
            for(int i = 0; i < rows * columns; i++)
                this->content[i] = 0;
        }
        // getters
        uint16_t get_columns(void) { return columns; }
        uint16_t get_rows(void) { return rows; }
};