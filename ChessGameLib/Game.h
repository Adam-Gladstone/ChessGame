#pragma once

namespace chess
{
    //
    // Initial setup of the pieces: https://en.wikipedia.org/wiki/Rules_of_chess
    //
    static constexpr std::array<Piece, 32> initial_setup
    {
        Piece{ PieceType::King, Color::White, {'e', 1} },
        Piece{ PieceType::Queen, Color::White,  {'d', 1} },
        Piece{ PieceType::Bishop, Color::White, {'c', 1} },
        Piece{ PieceType::Bishop, Color::White, {'f', 1} },
        Piece{ PieceType::Knight, Color::White, {'b', 1} },
        Piece{ PieceType::Knight, Color::White, {'g', 1} },
        Piece{ PieceType::Rook, Color::White, {'a', 1} },
        Piece{ PieceType::Rook, Color::White, {'h', 1} },
        Piece{ PieceType::Pawn, Color::White, {'a', 2} },
        Piece{ PieceType::Pawn, Color::White, {'b', 2} },
        Piece{ PieceType::Pawn, Color::White, {'c', 2} },
        Piece{ PieceType::Pawn, Color::White, {'d', 2} },
        Piece{ PieceType::Pawn, Color::White, {'e', 2} },
        Piece{ PieceType::Pawn, Color::White, {'f', 2} },
        Piece{ PieceType::Pawn, Color::White, {'g', 2} },
        Piece{ PieceType::Pawn, Color::White, {'h', 2} },
        Piece{ PieceType::King, Color::Black, {'e', 8} },
        Piece{ PieceType::Queen, Color::Black,  {'d', 8} },
        Piece{ PieceType::Bishop, Color::Black, {'c', 8} },
        Piece{ PieceType::Bishop, Color::Black, {'f', 8} },
        Piece{ PieceType::Knight, Color::Black, {'b', 8} },
        Piece{ PieceType::Knight, Color::Black, {'g', 8} },
        Piece{ PieceType::Rook, Color::Black, {'a', 8} },
        Piece{ PieceType::Rook, Color::Black, {'h', 8} },
        Piece{ PieceType::Pawn, Color::Black, {'a', 7} },
        Piece{ PieceType::Pawn, Color::Black, {'b', 7} },
        Piece{ PieceType::Pawn, Color::Black, {'c', 7} },
        Piece{ PieceType::Pawn, Color::Black, {'d', 7} },
        Piece{ PieceType::Pawn, Color::Black, {'e', 7} },
        Piece{ PieceType::Pawn, Color::Black, {'f', 7} },
        Piece{ PieceType::Pawn, Color::Black, {'g', 7} },
        Piece{ PieceType::Pawn, Color::Black, {'h', 7} }
    };

    class Game final 
    {
    public:
        Game() = default;

        //
        // Initialize the chess board to a specific state
        //
        void initialize(const auto& pieces)
        {
            captured.clear();

            for (const auto& piece : pieces)
            {
                Coord coord = piece.position.to_coord();

                const std::size_t index = static_cast<std::size_t>(coord.row * constants::BOARD_SIZE + coord.col);

                board.at(index) = piece;
            }
        }

        //
        // Reset the board to an empty state
        //
        void reset()
        {
            std::generate(
                board.begin(),
                board.end(),
                [n = static_cast<unsigned short>(0)]() mutable { return Piece{ PieceType::Empty, Color::None, from_index(n++)}; }
            );
        }

        //
        // Carry out a move
        //
        void turn(const Move& m)
        {
            if (m.is_kingside() || m.is_queenside())
            {
                Piece& king = find_king(m.get_color());
                Piece& rook = find_rook(m.get_color(), m.is_queenside());

                if (king.has_moved == false && rook.has_moved == false)
                {
                    if (has_clear_path(rook, king))
                    {
                        Position destination = rook.position;

                        // Move the king next to the rook
                        destination.set_file((m.is_queenside()) ? 'c' : 'g');

                        Piece& target_king = board.at(destination.to_index());

                        move_piece(king, target_king, m.is_capture());

                        // Move rook to the other side of the king, adjacent to it
                        destination = target_king.position;
                        destination.set_file((m.is_queenside()) ? 'd' : 'f');

                        Piece& target_rook = board.at(destination.to_index());

                        move_piece(rook, target_rook, m.is_capture());
                    }
                }
            }
            else
            {
                Piece& destination = board.at(m.get_destination().to_index());

                Piece& source = (m.get_source() == std::nullopt) ? find(m) : board.at(find_position(m).to_index());

                move_piece(source, destination, m.is_capture());
            }
        }

        //
        // Find a piece that satisfies the color and type, and which can legally move
        // to the specified destination
        //
        [[nodiscard]] Piece& find(const Move& m)
        {
            auto pred = [&](const auto& piece) 
            { 
                return piece.color == m.get_color() && piece.type == m.get_piece_type(); 
            };

            auto pieces = board | std::ranges::views::filter(pred);

            Coord dest = m.get_destination().to_coord();

            for (const auto& piece : pieces)
            {
                std::vector<Coord> moves = get_moves(piece, dest, board, m.is_capture());

                if (std::find(std::begin(moves), std::end(moves), dest) != std::end(moves))
                {
                    return board.at(piece.position.to_index());
                }
            }

            std::stringstream message;

            message << "Error: unable to find a "
                << to_string<Colors>(m.get_color())
                << " "
                << to_string<PieceTypes>(m.get_piece_type())
                << " that can move to "
                << m.get_destination().to_string();

            throw std::out_of_range(message.str());
        }


        //
        // Display the current state of the chess board
        // 
        void display()
        {
            [[maybe_unused]] HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

            std::cout << "\n------------------------------\n";

            for (unsigned short r = 0; r < constants::BOARD_SIZE; ++r)
            {
                for (unsigned short c = 0; c < constants::BOARD_SIZE; ++c)
                {
                    const std::size_t index = static_cast<std::size_t>(r * constants::BOARD_SIZE + c);

                    const auto& piece = board.at(index);

                    if (piece.type == PieceType::Empty)
                    {
                        std::cout << ". ";
                    }
                    else
                    {
                        /*
                        const wchar_t* symbol = get_symbol(piece.color, piece.type);
                        [[maybe_unused]] DWORD charsWritten;
                        WriteConsoleW(hConsole, symbol, static_cast<DWORD>(wcslen(symbol)), &charsWritten, NULL);
                        */

                        std::cout << static_cast<char>(piece.type) << " ";
                    }
                }
                std::cout << '\n';
            }

            std::cout << "\n------------------------------\n";
        }

        //
        // Display a list of captured pieces
        //
        void show_captured()
        {
            std::cout << "\n------------------------------\n";

            auto output = [](const auto& piece)
                {
                    std::cout << to_string<Colors>(piece.color) << " "
                        << to_string<PieceTypes>(piece.type) << " at: ["
                        << piece.position.to_string() << "]\n";
                };

            std::cout << "Captured Pieces: " << captured.size() << '\n';

            if (captured.size())
                std::ranges::for_each(std::begin(captured), std::end(captured), output);

            std::cout << "\n------------------------------\n";
        }

        const Board& get_board() const { return board; }

    private:

        //
        // Retrieve the unicode symbol for the specified piece
        //
        const wchar_t* get_symbol(Color color, PieceType type) const
        {
            if (color == Color::White)
            {
                switch (type)
                {
                case PieceType::King:
                    return chess::white_king;
                case PieceType::Queen:
                    return chess::white_queen;
                case PieceType::Rook:
                    return chess::white_rook;
                case PieceType::Bishop:
                    return chess::white_bishop;
                case PieceType::Knight:
                    return chess::white_knight;
                case PieceType::Pawn:
                    return chess::white_pawn;
                }
            }
            else
            {
                switch (type)
                {
                case PieceType::King:
                    return chess::black_king;
                case PieceType::Queen:
                    return chess::black_queen;
                case PieceType::Rook:
                    return chess::black_rook;
                case PieceType::Bishop:
                    return chess::black_bishop;
                case PieceType::Knight:
                    return chess::black_knight;
                case PieceType::Pawn:
                    return chess::black_pawn;
                }
            }

            return empty_square;
        }

        //
        // An empty board
        //
        Board board
        {
            Piece{ PieceType::Empty, Color::None, {'a', 8} },
            Piece{ PieceType::Empty, Color::None, {'b', 8} },
            Piece{ PieceType::Empty, Color::None, {'c', 8} },
            Piece{ PieceType::Empty, Color::None, {'d', 8} },
            Piece{ PieceType::Empty, Color::None, {'e', 8} },
            Piece{ PieceType::Empty, Color::None, {'f', 8} },
            Piece{ PieceType::Empty, Color::None, {'g', 8} },
            Piece{ PieceType::Empty, Color::None, {'h', 8} },
            Piece{ PieceType::Empty, Color::None, {'a', 7} },
            Piece{ PieceType::Empty, Color::None, {'b', 7} },
            Piece{ PieceType::Empty, Color::None, {'c', 7} },
            Piece{ PieceType::Empty, Color::None, {'d', 7} },
            Piece{ PieceType::Empty, Color::None, {'e', 7} },
            Piece{ PieceType::Empty, Color::None, {'f', 7} },
            Piece{ PieceType::Empty, Color::None, {'g', 7} },
            Piece{ PieceType::Empty, Color::None, {'h', 7} },
            Piece{ PieceType::Empty, Color::None, {'a', 6} },
            Piece{ PieceType::Empty, Color::None, {'b', 6} },
            Piece{ PieceType::Empty, Color::None, {'c', 6} },
            Piece{ PieceType::Empty, Color::None, {'d', 6} },
            Piece{ PieceType::Empty, Color::None, {'e', 6} },
            Piece{ PieceType::Empty, Color::None, {'f', 6} },
            Piece{ PieceType::Empty, Color::None, {'g', 6} },
            Piece{ PieceType::Empty, Color::None, {'h', 6} },
            Piece{ PieceType::Empty, Color::None, {'a', 5} },
            Piece{ PieceType::Empty, Color::None, {'b', 5} },
            Piece{ PieceType::Empty, Color::None, {'c', 5} },
            Piece{ PieceType::Empty, Color::None, {'d', 5} },
            Piece{ PieceType::Empty, Color::None, {'e', 5} },
            Piece{ PieceType::Empty, Color::None, {'f', 5} },
            Piece{ PieceType::Empty, Color::None, {'g', 5} },
            Piece{ PieceType::Empty, Color::None, {'h', 5} },
            Piece{ PieceType::Empty, Color::None, {'a', 4} },
            Piece{ PieceType::Empty, Color::None, {'b', 4} },
            Piece{ PieceType::Empty, Color::None, {'c', 4} },
            Piece{ PieceType::Empty, Color::None, {'d', 4} },
            Piece{ PieceType::Empty, Color::None, {'e', 4} },
            Piece{ PieceType::Empty, Color::None, {'f', 4} },
            Piece{ PieceType::Empty, Color::None, {'g', 4} },
            Piece{ PieceType::Empty, Color::None, {'h', 4} },
            Piece{ PieceType::Empty, Color::None, {'a', 3} },
            Piece{ PieceType::Empty, Color::None, {'b', 3} },
            Piece{ PieceType::Empty, Color::None, {'c', 3} },
            Piece{ PieceType::Empty, Color::None, {'d', 3} },
            Piece{ PieceType::Empty, Color::None, {'e', 3} },
            Piece{ PieceType::Empty, Color::None, {'f', 3} },
            Piece{ PieceType::Empty, Color::None, {'g', 3} },
            Piece{ PieceType::Empty, Color::None, {'h', 3} },
            Piece{ PieceType::Empty, Color::None, {'a', 2} },
            Piece{ PieceType::Empty, Color::None, {'b', 2} },
            Piece{ PieceType::Empty, Color::None, {'c', 2} },
            Piece{ PieceType::Empty, Color::None, {'d', 2} },
            Piece{ PieceType::Empty, Color::None, {'e', 2} },
            Piece{ PieceType::Empty, Color::None, {'f', 2} },
            Piece{ PieceType::Empty, Color::None, {'g', 2} },
            Piece{ PieceType::Empty, Color::None, {'h', 2} },
            Piece{ PieceType::Empty, Color::None, {'a', 1} },
            Piece{ PieceType::Empty, Color::None, {'b', 1} },
            Piece{ PieceType::Empty, Color::None, {'c', 1} },
            Piece{ PieceType::Empty, Color::None, {'d', 1} },
            Piece{ PieceType::Empty, Color::None, {'e', 1} },
            Piece{ PieceType::Empty, Color::None, {'f', 1} },
            Piece{ PieceType::Empty, Color::None, {'g', 1} },
            Piece{ PieceType::Empty, Color::None, {'h', 1} },
        };

        [[nodiscard]] Piece& find_king(Color color)
        {
            auto pred = [&](const auto& piece) 
            { 
                return piece.color == color && piece.type == PieceType::King; 
            };

            auto pieces = board | std::ranges::views::filter(pred);

            if (!pieces.empty())
            {
                const auto& piece = pieces.front();
                return board.at(piece.position.to_index());
            }
            else
            {
                throw std::out_of_range("Unable to find the King.");
            }
        }

        [[nodiscard]]
        bool is_empty(const Position& position) const
        {
            return board.at(position.to_index()).type == PieceType::Empty;
        }

        [[nodiscard]]
        bool has_clear_path(const Piece& rook, const Piece& king) const
        {
            Position position = rook.position;

            if (rook.position.get_file() == 'a')
            {
                for (char c = 'b'; c < king.position.get_file(); ++c)
                {
                    position.set_file(c);
                    if (!is_empty(position))
                        return false;
                }
                return true;
            }
            else
            {
                for (char c = 'g'; c > king.position.get_file(); --c)
                {
                    position.set_file(c);
                    if (!is_empty(position))
                        return false;
                }
                return true;
            }
        }

        [[nodiscard]] Piece& find_rook(Color color, bool queenside)
        {
            auto pred = [&](const auto& piece)
            { 
                return piece.color == color && piece.type == PieceType::Rook; 
            };

            auto rooks = board | std::ranges::views::filter(pred);

            for (const auto& rook : rooks)
            {
                if (queenside)
                {
                    if (rook.position.get_file() == 'a')
                        return board.at(rook.position.to_index());
                }
                else
                {
                    if (rook.position.get_file() == 'h')
                        return board.at(rook.position.to_index());
                }
            }

            throw std::out_of_range("Unable to find a unique Rook.");
        }

        [[nodiscard]] Position find_position(const Move& m)
        {
            auto pred = [&](const auto& piece) 
            { 
                    return piece.color == m.get_color() && piece.type == m.get_piece_type();
            };
            
            auto pieces = board | std::ranges::views::filter(pred);

            Position partial = m.get_source().value();

            if (pgn::is_file(partial.get_file()))
            {
                for (const auto& piece : pieces)
                {
                    if (piece.position.get_file() == partial.get_file())
                        return piece.position;
                }
            }
            else
            {
                for (const auto& piece : pieces)
                {
                    if (piece.position.get_rank() == partial.get_rank())
                        return piece.position;
                }
            }

            return Position{};
        }

        void move_piece(Piece& source, Piece& destination, bool capture)
        {
            if (capture)
            {
                captured.push_back(destination);
            }

            destination.type = source.type;
            destination.color = source.color;
            destination.has_moved = true;

            source.reset();
        }

    private:
        // 
        // Vector of captured pieces
        //
        std::vector<Piece> captured;
    };
}
