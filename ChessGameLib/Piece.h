#pragma once

namespace chess
{
    /*
    * https://en.wikipedia.org/wiki/List_of_Unicode_characters
    * 
    ♔ (White King): U+2654
    ♕ (White Queen): U+2655
    ♖ (White Rook): U+2656
    ♗ (White Bishop): U+2657
    ♘ (White Knight): U+2658
    ♙ (White Pawn): U+2659
    ♚ (Black King): U+265A
    ♛ (Black Queen): U+265B
    ♜ (Black Rook): U+265C
    ♝ (Black Bishop): U+265D
    ♞ (Black Knight): U+265E
    ♟ (Black Pawn): U+265F
    */

    constexpr wchar_t empty_square[] = L" \u2610 ";

    constexpr wchar_t white_king[]      = L" \u2654 ";
    constexpr wchar_t white_queen[]     = L" \u2655 ";
    constexpr wchar_t white_rook[]      = L" \u2656 ";
    constexpr wchar_t white_bishop[]    = L" \u2657 ";
    constexpr wchar_t white_knight[]    = L" \u2658 ";
    constexpr wchar_t white_pawn[]      = L" \u2659 ";
    constexpr wchar_t black_king[]      = L" \u265a ";
    constexpr wchar_t black_queen[]     = L" \u265b ";
    constexpr wchar_t black_rook[]      = L" \u265c ";
    constexpr wchar_t black_bishop[]    = L" \u265d ";
    constexpr wchar_t black_knight[]    = L" \u265e ";
    constexpr wchar_t black_pawn[]      = L" \u265f ";

    //
    // Class to represent a specific chess piece (type) of a specific color
    // in a specific location on the board.
    //
    struct Piece final
    {
        PieceType type{};
        Color color{};
        Position position{};

        bool has_moved{ false };

        void reset()
        {
            type = PieceType::Empty;
            color = Color::None;
            has_moved = false;
        }
    };
}