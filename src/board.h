#include <inttypes.h>
#include <memory>

class Board {
    private:
        uint16_t rows;
        uint16_t columns;
        std::shared_ptr<uint8_t[]> content;

    public:
        Board(uint8_t rows, uint8_t columns);
        uint16_t get_columns(void);
        uint16_t get_rows(void);

};