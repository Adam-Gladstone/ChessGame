#pragma once

namespace chess
{
    using namespace std::literals;

    //
    // Colors
    //
    enum class Color : unsigned char { Black, White, None };

    //
    // Color values
    //
    struct Colors
    {
        static constexpr std::array<std::pair<Color, std::string_view>, 3> values
        {
            std::make_pair(Color::Black, "Black"sv),
            std::make_pair(Color::White, "White"sv),
            std::make_pair(Color::None, "None"sv),
        };
    };

    //
    // Outcomes
    //
    enum class Outcome : unsigned char { Draw, Checkmate, Resign };

    //
    // Outcome values
    //
    struct Outcomes
    {
        static constexpr std::array<std::pair<Outcome, std::string_view>, 3> values
        {
            std::make_pair(Outcome::Draw, "Draw"sv),
            std::make_pair(Outcome::Checkmate, "Checkmate"sv),
            std::make_pair(Outcome::Resign, "Resign"sv),
        };
    };

    //
    // PieceTypes
    // 
    enum class PieceType : unsigned char
    {
        Empty = '\0',
        King = 'K',
        Queen = 'Q',
        Bishop = 'B',
        Knight = 'N',
        Rook = 'R',
        Pawn = 'p'
    };

    //
    // PieceType values
    //
    struct PieceTypes
    {
        static constexpr std::array<std::pair<PieceType, std::string_view>, 7> values
        {
            std::make_pair(PieceType::Empty, "Empty"sv),
            std::make_pair(PieceType::King, "King"sv),
            std::make_pair(PieceType::Queen, "Queen"sv),
            std::make_pair(PieceType::Bishop, "Bishop"sv),
            std::make_pair(PieceType::Knight, "Knight"sv),
            std::make_pair(PieceType::Rook, "Rook"sv),
            std::make_pair(PieceType::Pawn, "Pawn"sv),
        };
    };

    //
    // Retrieve a string representation of the specified type from the collection of values
    //
    template <typename Values, typename Type>
    constexpr std::string_view to_string(Type type)
    {
        for (const auto& value : Values::values)
        {
            if (value.first == type)
            {
                return value.second;
            }
        }
        return {};
    }
}
