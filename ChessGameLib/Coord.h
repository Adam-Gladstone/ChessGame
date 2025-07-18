#pragma once

namespace chess
{
    //
    // Represent piece locations in 2D space.
    // 0, 0 is top, left; 7, 7 is bottom, right.
    // 
    struct Coord final
    {
        unsigned short col{};
        unsigned short row{};

        [[nodiscard]] constexpr bool operator<(const Coord& rhs) const 
        { 
            return row < rhs.row && col < rhs.col; 
        }

        [[nodiscard]] constexpr bool operator==(const Coord& rhs) const 
        { 
            return row == rhs.row && col == rhs.col; 
        }

        [[nodiscard]] constexpr unsigned short to_index() const
        {
            return row * constants::BOARD_SIZE + col;
        }

        [[nodiscard]] constexpr bool is_in_bounds() const
        {
            return (col >= 0 && col <= 7) && (row >= 0 && row <= 7);
        }
    };
}