#pragma once

namespace chess 
{
    // 
    // Class to represent chess positions as per PGN and translate these
    // as required to 2D coordinates or an array (board) index.
    //
    class Position final
    {
    public:
        Position() = default;

        constexpr Position(char c, unsigned short r)
            : file((c >= 'a' && c <= 'h') ? c : throw std::out_of_range("Column must be between \'a\' and \'h\'."))
            , rank((r >= 1 && r <= 8) ? r : throw std::out_of_range("Row must be between 1 and 8."))
        {
        }

        constexpr void set_file(char c)
        {
            file = (c >= 'a' && c <= 'h') ? c : throw std::out_of_range("Column must be between \'a\' and \'h\'.");
        }

        constexpr void set_rank(unsigned short r)
        {
            rank = (r >= 1 && r <= 8) ? r : throw std::out_of_range("Row must be between 1 and 8.");
        }

        [[nodiscard]] constexpr char get_file() const { return file; }

        [[nodiscard]] constexpr unsigned short get_rank() const { return rank; }

        [[nodiscard]] constexpr Coord to_coord() const
        {
            const unsigned short col = static_cast<unsigned short>(file) - constants::ASCII_LETTER_BASE;

            const unsigned short row = constants::ROW_BASE - rank;

            return { col, row };
        }

        [[nodiscard]] constexpr unsigned short to_index() const
        {
            const unsigned short col = static_cast<unsigned short>(file) - constants::ASCII_LETTER_BASE;

            const unsigned short row = constants::ROW_BASE - rank;

            return row * constants::BOARD_SIZE + col;
        }

        [[nodiscard]] std::string to_string() const
        {
            std::string s{ file };
            s.push_back(static_cast<char>(constants::ASCII_NUMBER_BASE + rank));
            return s;
        }

    private:
        char file{};
        unsigned short rank{};
    };
}