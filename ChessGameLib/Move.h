#pragma once


namespace chess
{
    using namespace std::literals;

    namespace pgn 
    {
        //
        // Utility functions for processing PGN
        //

        [[nodiscard]] static constexpr bool is_file(char c)
        {
            return c >= 'a' && c <= 'h';
        }

        [[nodiscard]] static constexpr bool is_rank(char c)
        {
            return c >= '1' && c <= '8';
        }

        [[nodiscard]] static constexpr bool is_capture(std::string_view s)
        {
            return s.at(1) == 'x';
        }

        [[nodiscard]] static constexpr bool is_check(std::string_view s)
        {
            return s.ends_with('+');
        }

        [[nodiscard]] static constexpr bool is_check_mate(std::string_view s)
        {
            return s.ends_with('#');
        }

        [[nodiscard]] static constexpr bool is_kingside(std::string_view s)
        {
            return (s == "O-O"sv || s == "0-0"sv);
        }

        [[nodiscard]] static constexpr bool is_queenside(std::string_view s)
        {
            return (s == "O-O-O"sv || s == "0-0-0"sv);
        }

        [[nodiscard]] static constexpr PieceType from_char(std::string_view s)
        {
            PieceType type = (is_file(s.at(0))) ? PieceType::Pawn : static_cast<PieceType>(s.at(0));
            return type;
        }

        [[nodiscard]] static constexpr Position from_string(std::string_view s)
        {
            std::string_view spos = s.substr(s.size() - (is_check(s) || is_check_mate(s) ? 3 : 2), 2);

            return { spos.at(0), static_cast<unsigned short>(spos.at(1) - constants::ASCII_NUMBER_BASE) };
        }
    }


    //
    // The game board
    //
    using Board = std::array<chess::Piece, 64>;

    //
    // Class to transform a (short) PGN move specification 
    // into an actual move on a chess board
    //
    class Move final
    {
    public:
        explicit constexpr Move(Color c, std::string_view s)
            : color(c)
            , text(s)
        {
            check_mate = pgn::is_check_mate(s);
            check = pgn::is_check(s);
            capture = pgn::is_capture(s);
            kingside = pgn::is_kingside(s);
            queenside = pgn::is_queenside(s);

            const bool castling = kingside || queenside;

            if (!castling)
            {
                piece = pgn::from_char(s);
                destination = pgn::from_string(s);

                //
                // Determine if the pgn text contains a disambiguating file or rank once we have identified 
                // check (+), check mate (#) or capture (x)
                // Example: Rfe8+ (from game_of_the_century, move #17)
                //
                std::size_t remainder = s.length() - 
                    destination.to_string().length() - 
                    ((check || check_mate) ? 1 : 0) - 
                    (capture ? 1 : 0);

                if (remainder > 1)
                {
                    Position pos{};

                    char ch = s.at(1);
                    if (pgn::is_file(ch))
                    {
                        pos.set_file(ch);
                    }
                    else if (pgn::is_rank(ch))
                    {
                        pos.set_rank(ch - constants::ASCII_NUMBER_BASE);
                    }
                    else
                        throw std::invalid_argument("Cannot determine source.");

                    source = std::make_optional(pos);
                }
            }
        }

        void output() const
        {
            if (kingside || queenside)
            {
                std::cout
                    << text
                    << ": "
                    << to_string<Colors>(color)
                    << (kingside ? " kingside castling" : " queenside castling")
                    << '\n';
            }
            else
            {
                std::cout
                    << text
                    << ": "
                    << to_string<Colors>(color)
                    << " "
                    << to_string<PieceTypes>(piece)
                    << (capture ? " captures " : " to ")
                    << destination.to_string()
                    << (check ? " (check)" : (check_mate ? " (check mate)" : ""))
                    << '\n';
            }
        }

        [[nodiscard]] bool is_kingside() const { return kingside; }

        [[nodiscard]] bool is_queenside() const { return queenside; }

        [[nodiscard]] Color get_color() const { return color; }

        [[nodiscard]] bool is_capture() const { return capture; }

        [[nodiscard]] PieceType get_piece_type() const { return piece; }

        [[nodiscard]] Position get_destination() const { return destination; }
        
        [[nodiscard]] std::optional<Position> get_source() const { return source; }

    private:
        Color color{ Color::None };
        bool check_mate{ false };
        bool check{ false };
        bool capture{ false };
        bool kingside{ false };
        bool queenside{ false };

        PieceType piece{ PieceType::Empty };
        Position destination{};
        std::optional<Position> source{};
        
        std::string text;
    };

    [[nodiscard]] static constexpr Position from_index(unsigned short index)
    {
        const char file = constants::ASCII_LETTER_BASE + (index % constants::BOARD_SIZE);
        
        const unsigned short rank = constants::ROW_BASE - static_cast<short>(index / constants::BOARD_SIZE);

        return { file, rank };
    }

    [[nodiscard]] static constexpr bool is_empty(const Coord& move, const Board& board)
    {
        unsigned short index = move.to_index();
        
        const Piece& square = board.at(index);
        
        return (square.type == PieceType::Empty);
    }

    [[nodiscard]] static constexpr bool is_same_color(const Piece& piece, const Coord& move, const Board& board)
    {
        unsigned short index = move.to_index();

        const Piece& square = board.at(index);

        return (square.color == piece.color);
    }

    [[nodiscard]] static constexpr std::pair<bool, bool> is_legal_move(
        const Piece& piece, 
        const Coord& move, 
        const Coord& dest, 
        const Board& board,
        bool capture
    )
    {
        if (!move.is_in_bounds())
        {
            return { false, false };
        }

        if (!is_empty(move, board))
        {
            if (is_same_color(piece, move, board))
            {
                return { false, true };
            }
            else
            {
                if (move == dest)
                {
                    return { true, true };
                }
                else 
                {
                    if (capture)
                    {
                        return { true, true };
                    }
                    else
                    {
                        return { false, true };
                    }
                }
            }
        }

        return { true, false };
    }

    struct Offset
    {
        short off_y{};
        short off_x{};
    };

    static constexpr std::array<std::pair<PieceType, Offset>, 16> fixed_moves
    {
        std::make_pair(PieceType::King, Offset(-1,  0)),
        std::make_pair(PieceType::King, Offset(-1,  1)),
        std::make_pair(PieceType::King, Offset(0,  1)),
        std::make_pair(PieceType::King, Offset(1,  1)),
        std::make_pair(PieceType::King, Offset(1,  0)),
        std::make_pair(PieceType::King, Offset(1, -1)),
        std::make_pair(PieceType::King, Offset(0, -1)),
        std::make_pair(PieceType::King, Offset(-1, -1)),
        std::make_pair(PieceType::Knight, Offset(-2, -1)),
        std::make_pair(PieceType::Knight, Offset(-1, -2)),
        std::make_pair(PieceType::Knight, Offset(1, -2)),
        std::make_pair(PieceType::Knight, Offset(2, -1)),
        std::make_pair(PieceType::Knight, Offset(2,  1)),
        std::make_pair(PieceType::Knight, Offset(1,  2)),
        std::make_pair(PieceType::Knight, Offset(-1,  2)),
        std::make_pair(PieceType::Knight, Offset(-2,  1)),
    };

    static void get_diagonal_moves(
        const Piece& piece,
        const Coord& origin,
        const Coord& dest,
        const Board& board,
        bool capture,
        std::vector<Coord>& legal_moves
    )
    {
        const short sign = (piece.color == Color::Black) ? 1 : -1;

        for (unsigned short offset = 1; offset < 8; ++offset)
        {
            Coord move_to{ static_cast<unsigned short>(origin.col + offset), 
                           static_cast<unsigned short>(origin.row + (sign * offset)) };

            const auto& [legal, last] = is_legal_move(piece, move_to, dest, board, capture);

            if (!legal)
                break;

            legal_moves.emplace_back(move_to);

            if (last)
                break;
        }

        for (unsigned short offset = 1; offset < 8; ++offset)
        {
            Coord move_to{ static_cast<unsigned short>(origin.col - offset), 
                           static_cast<unsigned short>(origin.row + (sign * offset)) };

            const auto& [legal, last] = is_legal_move(piece, move_to, dest, board, capture);

            if (!legal)
                break;

            legal_moves.emplace_back(move_to);

            if (last)
                break;
        }

        for (unsigned short offset = 1; offset < 8; ++offset)
        {
            Coord move_to{ static_cast<unsigned short>(origin.col - offset), 
                           static_cast<unsigned short>(origin.row - (sign * offset)) };

            const auto& [legal, last] = is_legal_move(piece, move_to, dest, board, capture);

            if (!legal)
                break;

            legal_moves.emplace_back(move_to);

            if (last)
                break;
        }

        for (unsigned short offset = 1; offset < 8; ++offset)
        {
            Coord move_to{ static_cast<unsigned short>(origin.col + offset), 
                           static_cast<unsigned short>(origin.row - (sign * offset)) };

            const auto& [legal, last] = is_legal_move(piece, move_to, dest, board, capture);

            if (!legal)
                break;

            legal_moves.emplace_back(move_to);

            if (last)
                break;
        }
    }

    static void get_perpendicular_moves(
        const Piece& piece,
        const Coord& origin,
        const Coord& dest,
        const Board& board,
        bool capture,
        std::vector<Coord>& legal_moves
    )
    {
        const short sign = (piece.color == Color::Black) ? 1 : -1;

        for (unsigned short c = 1; c < 8; ++c)
        {
            Coord move_to{ static_cast<unsigned short>(origin.col - c), origin.row };

            const auto& [legal, last] = is_legal_move(piece, move_to, dest, board, capture);

            if (!legal)
                break;

            legal_moves.emplace_back(move_to);

            if (last)
                break;
        }

        for (unsigned short c = 1; c < 8; ++c)
        {
            Coord move_to{ static_cast<unsigned short>(origin.col + c), origin.row };

            const auto& [legal, last] = is_legal_move(piece, move_to, dest, board, capture);

            if (!legal)
                break;

            legal_moves.emplace_back(move_to);

            if (last)
                break;
        }

        for (unsigned short r = 1; r < 8; ++r)
        {
            Coord move_to{ origin.col, static_cast<unsigned short>(origin.row + (sign * r)) };

            const auto& [legal, last] = is_legal_move(piece, move_to, dest, board, capture);

            if (!legal)
                break;

            legal_moves.emplace_back(move_to);

            if (last)
                break;
        }

        for (unsigned short r = 1; r < 8; ++r)
        {
            Coord move_to{ origin.col, static_cast<unsigned short>(origin.row - (sign * r)) };

            const auto& [legal, last] = is_legal_move(piece, move_to, dest, board, capture);

            if (!legal)
                break;

            legal_moves.emplace_back(move_to);

            if (last)
                break;
        }
    }

    [[nodiscard]] static std::vector<Coord> get_moves(
        const Piece& piece, 
        const Coord& dest, 
        const Board& board,
        bool capture
    )
    {
        const short sign = (piece.color == Color::Black) ? 1 : -1;

        Coord origin = piece.position.to_coord();

        std::vector<Coord> legal_moves;

        if (piece.type == PieceType::Pawn)
        {
            if (capture)
            {
                if(origin.col + 1 == dest.col)
                {
                    Coord move_to{ static_cast<unsigned short>(origin.col + 1), 
                                   static_cast<unsigned short>(origin.row + (sign * 1)) };

                    const auto& [legal, last] = is_legal_move(piece, move_to, dest, board, capture);

                    if (legal)
                    {
                        legal_moves.emplace_back(move_to);
                    }
                }

                if (origin.col - 1 == dest.col)
                {
                    Coord move_to{ static_cast<unsigned short>(origin.col - 1), 
                                   static_cast<unsigned short>(origin.row + (sign * 1)) };

                    const auto& [legal, last] = is_legal_move(piece, move_to, dest, board, capture);

                    if (legal)
                    {
                        legal_moves.emplace_back(move_to);
                    }
                }
            }
            else
            {
                if(origin.col == dest.col)
                {
                    Coord m1{ origin.col, static_cast<unsigned short>(origin.row + (sign * 1)) };
                
                    const auto& [legal_m1, last_m1] = is_legal_move(piece, m1, dest, board, capture);

                    if (legal_m1)
                    {
                        legal_moves.emplace_back(m1);

                        if (!piece.has_moved)
                        {
                            Coord m2{ origin.col, static_cast<unsigned short>(origin.row + (sign * 2)) };

                            const auto& [legal_m2, last_m2] = is_legal_move(piece, m2, dest, board, capture);

                            if (legal_m2)
                            {
                                legal_moves.emplace_back(m2);
                            }
                        }
                    }
                }
            }
        }
        else if (piece.type == PieceType::Queen)
        {
            get_perpendicular_moves(piece, origin, dest, board, capture, legal_moves);
            get_diagonal_moves(piece, origin, dest, board, capture, legal_moves);
        }
        else if (piece.type == PieceType::Bishop)
        {
            get_diagonal_moves(piece, origin, dest, board, capture, legal_moves);
        }
        else if (piece.type == PieceType::Rook)
        {
            get_perpendicular_moves(piece, origin, dest, board, capture, legal_moves);
        }
        else
        {
            auto pred = [&](const std::pair<PieceType, Offset>& move) { return move.first == piece.type; };

            auto moves = fixed_moves | std::ranges::views::filter(pred);

            for (const auto& move : moves)
            {
                const auto& [off_y, off_x] = move.second;

                Coord move_to{ static_cast<unsigned short>(origin.col + off_y), 
                               static_cast<unsigned short>(origin.row + off_x) };

                const auto& [legal, last] = is_legal_move(piece, move_to, dest, board, capture);
                if (legal)
                {
                    legal_moves.emplace_back(move_to);
                }
            }
        }

        return legal_moves;
    }
}
