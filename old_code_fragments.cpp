// code fragments

// https://en.wikipedia.org/wiki/Rules_of_chess
// https://en.wikipedia.org/wiki/Chess_notation
// https://en.wikipedia.org/wiki/Algebraic_notation_(chess)
//
// see: https://www.codeproject.com/Articles/1214018/Chess-Console-Game-in-Cplusplus



auto print_elem = [](const auto& piece) 
	{ std::cout << to_string<Colors>(piece.color) << " " 
				<< to_string<PieceTypes>(piece.type) << " at: [" 
				<< piece.position.file << "," << piece.position.rank << "]\n"; };

  std::ranges::for_each(result.begin(), result.end(), print_elem);

	unsigned int find(Color color, PieceType type, Position position)
	{
		for (unsigned int r = 0; r < BOARD_SIZE; ++r)
		{
			for (unsigned int c = 0; c < BOARD_SIZE; ++c)
			{
				const auto& piece = board[to_index(c, r)];

				if (piece.color == color && piece.type == type)
				{
					if (piece.type == PieceType::Pawn)
					{
						if(piece.position.file == position.file)
							return to_index(piece.position);
					}
				}
			}
		}
	}


static constexpr std::array<Piece, 16> whitePieces{
    Piece{ PieceType::King, Color::White, {'e', 1}, 'K' },
    Piece{ PieceType::Queen, Color::White,  {'d', 1}, 'Q' },
    Piece{ PieceType::Bishop, Color::White, {'c', 1}, 'B' },
    Piece{ PieceType::Bishop, Color::White, {'f', 1}, 'B' },
    Piece{ PieceType::Knight, Color::White, {'b', 1}, 'N' },
    Piece{ PieceType::Knight, Color::White, {'g', 1}, 'N' },
    Piece{ PieceType::Rook, Color::White, {'a', 1}, 'R' },
    Piece{ PieceType::Rook, Color::White, {'h', 1}, 'R' },
    Piece{ PieceType::Pawn, Color::White, {'a', 2}, 'p' },
    Piece{ PieceType::Pawn, Color::White, {'b', 2}, 'p' },
    Piece{ PieceType::Pawn, Color::White, {'c', 2}, 'p' },
    Piece{ PieceType::Pawn, Color::White, {'d', 2}, 'p' },
    Piece{ PieceType::Pawn, Color::White, {'e', 2}, 'p' },
    Piece{ PieceType::Pawn, Color::White, {'f', 2}, 'p' },
    Piece{ PieceType::Pawn, Color::White, {'g', 2}, 'p' },
    Piece{ PieceType::Pawn, Color::White, {'h', 2}, 'p' },
};

static constexpr std::array<Piece, 16> blackPieces{
    Piece{ PieceType::King, Color::Black, {'e', 8}, 'K' },
    Piece{ PieceType::Queen, Color::Black,  {'d', 8}, 'Q' },
    Piece{ PieceType::Bishop, Color::Black, {'c', 8}, 'B' },
    Piece{ PieceType::Bishop, Color::Black, {'f', 8}, 'B' },
    Piece{ PieceType::Knight, Color::Black, {'b', 8}, 'K' },
    Piece{ PieceType::Knight, Color::Black, {'g', 8}, 'K' },
    Piece{ PieceType::Rook, Color::Black, {'a', 8}, 'R' },
    Piece{ PieceType::Rook, Color::Black, {'h', 8}, 'R' },
    Piece{ PieceType::Pawn, Color::Black, {'a', 7}, 'p' },
    Piece{ PieceType::Pawn, Color::Black, {'b', 7}, 'p' },
    Piece{ PieceType::Pawn, Color::Black, {'c', 7}, 'p' },
    Piece{ PieceType::Pawn, Color::Black, {'d', 7}, 'p' },
    Piece{ PieceType::Pawn, Color::Black, {'e', 7}, 'p' },
    Piece{ PieceType::Pawn, Color::Black, {'f', 7}, 'p' },
    Piece{ PieceType::Pawn, Color::Black, {'g', 7}, 'p' },
    Piece{ PieceType::Pawn, Color::Black, {'h', 7}, 'p' }
};

    void set_piece(const Piece& piece)
    {
        const Position& initial_pos = piece.position;
        auto coord = to_coord(initial_pos);
        //board[coord.row][coord.col] = piece;
    }

    /*
    void initialise(const std::array<Piece, 16>& whitePieces, const std::array<Piece, 16>& blackPieces)
    {
        for(const auto& piece : whitePieces)
        {
            set_piece(piece);
        }
    }
    */

    constexpr static std::array<std::array<Cell, 8>, 8> board
    {
        Cell{ /* cell 0, 0 */ {'a', 8}, { PieceType::Rook, Color::Black, {'a', 8} } },
        Cell{ /* cell 0, 1 */ {'b', 8}, { PieceType::Knight, Color::Black, {'b', 8} } },
        Cell{ /* cell 0, 2 */ {'c', 8}, { PieceType::Bishop, Color::Black, {'c', 8} } },
        Cell{ /* cell 0, 3 */ {'d', 8}, { PieceType::Queen, Color::Black, {'d', 8} } },
        Cell{ /* cell 0, 4 */ {'e', 8}, { PieceType::King, Color::Black, {'e', 8} } },
        Cell{ /* cell 0, 5 */ {'f', 8}, { PieceType::Bishop, Color::Black, {'f', 8} } },
        Cell{ /* cell 0, 6 */ {'g', 8}, { PieceType::Knight, Color::Black, {'g', 8} } },
        Cell{ /* cell 0, 7 */ {'h', 8}, { PieceType::Rook, Color::Black, {'h', 8} } },

        Cell{ /* cell 1, 0 */ {'a', 7}, { PieceType::Pawn, Color::Black, {'a', 7} } },
        Cell{ /* cell 1, 1 */ {'b', 7}, { PieceType::Pawn, Color::Black, {'b', 7} } },
        Cell{ /* cell 1, 2 */ {'c', 7}, { PieceType::Pawn, Color::Black, {'c', 7} } },
        Cell{ /* cell 1, 3 */ {'d', 7}, { PieceType::Pawn, Color::Black, {'d', 7} } },
        Cell{ /* cell 1, 4 */ {'e', 7}, { PieceType::Pawn, Color::Black, {'e', 7} } },
        Cell{ /* cell 1, 5 */ {'f', 7}, { PieceType::Pawn, Color::Black, {'f', 7} } },
        Cell{ /* cell 1, 6 */ {'g', 7}, { PieceType::Pawn, Color::Black, {'g', 7} } },
        Cell{ /* cell 1, 7 */ {'h', 7}, { PieceType::Pawn, Color::Black, {'h', 7} } },

        Cell{ /* cell 2, 0 */ {'a', 6}, { PieceType::Empty, Color::None, {'a', 6} } },
        Cell{ /* cell 2, 1 */ {'b', 6}, { PieceType::Empty, Color::None, {'b', 6} } },
        Cell{ /* cell 2, 2 */ {'c', 6}, { PieceType::Empty, Color::None, {'c', 6} } },
        Cell{ /* cell 2, 3 */ {'d', 6}, { PieceType::Empty, Color::None, {'d', 6} } },
        Cell{ /* cell 2, 4 */ {'e', 6}, { PieceType::Empty, Color::None, {'e', 6} } },
        Cell{ /* cell 2, 5 */ {'f', 6}, { PieceType::Empty, Color::None, {'f', 6} } },
        Cell{ /* cell 2, 6 */ {'g', 6}, { PieceType::Empty, Color::None, {'g', 6} } },
        Cell{ /* cell 2, 7 */ {'h', 6}, { PieceType::Empty, Color::None, {'h', 6} } },
        Cell{ /* cell 3, 0 */ {'a', 5}, { PieceType::Empty, Color::None, {'a', 5} } },
        Cell{ /* cell 3, 1 */ {'b', 5}, { PieceType::Empty, Color::None, {'b', 5} } },
        Cell{ /* cell 3, 2 */ {'c', 5}, { PieceType::Empty, Color::None, {'c', 5} } },
        Cell{ /* cell 3, 3 */ {'d', 5}, { PieceType::Empty, Color::None, {'d', 5} } },
        Cell{ /* cell 3, 4 */ {'e', 5}, { PieceType::Empty, Color::None, {'e', 5} } },
        Cell{ /* cell 3, 5 */ {'f', 5}, { PieceType::Empty, Color::None, {'f', 5} } },
        Cell{ /* cell 3, 6 */ {'g', 5}, { PieceType::Empty, Color::None, {'g', 5} } },
        Cell{ /* cell 3, 7 */ {'h', 5}, { PieceType::Empty, Color::None, {'h', 5} } },
        Cell{ /* cell 4, 0 */ {'a', 4}, { PieceType::Empty, Color::None, {'a', 4} } },
        Cell{ /* cell 4, 1 */ {'b', 4}, { PieceType::Empty, Color::None, {'b', 4} } },
        Cell{ /* cell 4, 2 */ {'c', 4}, { PieceType::Empty, Color::None, {'c', 4} } },
        Cell{ /* cell 4, 3 */ {'d', 4}, { PieceType::Empty, Color::None, {'d', 4} } },
        Cell{ /* cell 4, 4 */ {'e', 4}, { PieceType::Empty, Color::None, {'e', 4} } },
        Cell{ /* cell 4, 5 */ {'f', 4}, { PieceType::Empty, Color::None, {'f', 4} } },
        Cell{ /* cell 4, 6 */ {'g', 4}, { PieceType::Empty, Color::None, {'g', 4} } },
        Cell{ /* cell 4, 7 */ {'h', 4}, { PieceType::Empty, Color::None, {'h', 4} } },
        Cell{ /* cell 5, 0 */ {'a', 3}, { PieceType::Empty, Color::None, {'a', 3} } },
        Cell{ /* cell 5, 1 */ {'b', 3}, { PieceType::Empty, Color::None, {'b', 3} } },
        Cell{ /* cell 5, 2 */ {'c', 3}, { PieceType::Empty, Color::None, {'c', 3} } },
        Cell{ /* cell 5, 3 */ {'d', 3}, { PieceType::Empty, Color::None, {'d', 3} } },
        Cell{ /* cell 5, 4 */ {'e', 3}, { PieceType::Empty, Color::None, {'e', 3} } },
        Cell{ /* cell 5, 5 */ {'f', 3}, { PieceType::Empty, Color::None, {'f', 3} } },
        Cell{ /* cell 5, 6 */ {'g', 3}, { PieceType::Empty, Color::None, {'g', 3} } },
        Cell{ /* cell 5, 7 */ {'h', 3}, { PieceType::Empty, Color::None, {'h', 3} } },

        Cell{ /* cell 6, 0 */ {'a', 2}, { PieceType::Pawn, Color::White, {'a', 2} } },
        Cell{ /* cell 6, 1 */ {'b', 2}, { PieceType::Pawn, Color::White, {'b', 2} } },
        Cell{ /* cell 6, 2 */ {'c', 2}, { PieceType::Pawn, Color::White, {'c', 2} } },
        Cell{ /* cell 6, 3 */ {'d', 2}, { PieceType::Pawn, Color::White, {'d', 2} } },
        Cell{ /* cell 6, 4 */ {'e', 2}, { PieceType::Pawn, Color::White, {'e', 2} } },
        Cell{ /* cell 6, 5 */ {'f', 2}, { PieceType::Pawn, Color::White, {'f', 2} } },
        Cell{ /* cell 6, 6 */ {'g', 2}, { PieceType::Pawn, Color::White, {'g', 2} } },
        Cell{ /* cell 6, 7 */ {'h', 2}, { PieceType::Pawn, Color::White, {'h', 2} } },

        Cell{ /* cell 7, 0 */ {'a', 1}, { PieceType::Rook, Color::White, {'a', 1} } },
        Cell{ /* cell 7, 1 */ {'b', 1}, { PieceType::Knight, Color::White, {'b', 1} } },
        Cell{ /* cell 7, 2 */ {'c', 1}, { PieceType::Bishop, Color::White, {'c', 1} } },
        Cell{ /* cell 7, 3 */ {'d', 1}, { PieceType::Queen, Color::White, {'d', 1} } },
        Cell{ /* cell 7, 4 */ {'e', 1}, { PieceType::King, Color::White, {'e', 1} } },
        Cell{ /* cell 7, 5 */ {'f', 1}, { PieceType::Bishop, Color::White, {'f', 1} } },
        Cell{ /* cell 7, 6 */ {'g', 1}, { PieceType::Knight, Color::White, {'g', 1} } },
        Cell{ /* cell 7, 7 */ {'h', 1}, { PieceType::Rook, Color::White, {'h', 1} } },
    };

    void initialise(const std::array<Piece, 16>& whitePieces, const std::array<Piece, 16>& blackPieces)
    {
        for (const auto& piece : blackPieces)
        {
            set_piece(piece);
        }

        for (const auto& piece : whitePieces)
        {
            set_piece(piece);
        }
    }

    void set_piece(const Piece& piece)
    {
        const Position& pos = piece.position;

        const Coord& coord = to_coord(pos);

        board[coord.row * BOARD_SIZE + coord.col] = piece;
    }



struct Cell {
    Position position;
    Piece piece;

    friend void swap(Cell& lhs, Cell& rhs)
    {
        std::cout << "swap(" << lhs << ", " << rhs << ")\n";
        std::swap(lhs.piece, rhs.piece);
    }

    friend std::ostream& operator<<(std::ostream& os, Cell& cell)
    {
        return os << "Cell [" <<
            cell.position.file << "," <<
            cell.position.rank << "] " <<
            to_string(cell.piece.color) << " " <<
            to_string(cell.piece.type) << '\n';
    }
};



constexpr std::string_view to_string(Color c)
{
    return (c == Color::None ? "" : (c == Color::Black ? "Black" : "White"));
}

constexpr std::string_view to_string(PieceType type)
{
    switch (type)
    {
    case PieceType::Empty:
        return "(Empty)";
    case PieceType::King:
        return "King";
    case PieceType::Queen:
        return "Queen";
    case PieceType::Bishop:
        return "Bishop";
    case PieceType::Knight:
        return "Knight";
    case PieceType::Rook:
        return "Rook";
    case PieceType::Pawn:
        return "Pawn";
    default:
        return "(Empty)";
    }
}


    if (piece.type == PieceType::King)
    {
        auto piece_moves = moves | std::ranges::views::filter(pred);

        for (const auto& move : piece_moves)
        {
            const auto& [off_y, off_x] = move.second;

            Coord move_to{ origin.col + off_y, origin.row + off_x };

            if (is_in_bounds(move_to) && is_empty(move_to, game))
            {
                legal_moves.emplace_back(move_to);
            }
        }
    }

    if (piece.type == PieceType::Knight)
    {
        auto piece_moves = moves | std::ranges::views::filter(pred);

        for (const auto& move : piece_moves)
        {
            const auto& [off_y, off_x] = move.second;

            if (is_in_bounds(origin.col + off_y, origin.row + off_x))
            {
                legal_moves.emplace_back(Coord{ origin.col + off_y, origin.row + off_x });
            }
        }

        /*
        if (is_in_bounds(origin.col - 2, origin.row - 1))
            legal_moves.emplace_back(Coord{ origin.col - 2, origin.row - 1 });

        if (is_in_bounds(origin.col - 1, origin.row - 2))
            legal_moves.emplace_back(Coord{ origin.col - 1, origin.row - 2 });

        if (is_in_bounds(origin.col + 1, origin.row - 2))
            legal_moves.emplace_back(Coord{ origin.col + 1, origin.row - 2 });

        if (is_in_bounds(origin.col + 2, origin.row - 1))
            legal_moves.emplace_back(Coord{ origin.col + 2, origin.row - 1 });

        if (is_in_bounds(origin.col + 2, origin.row + 1))
            legal_moves.emplace_back(Coord{ origin.col + 2, origin.row + 1 });

        if (is_in_bounds(origin.col + 1, origin.row + 2))
            legal_moves.emplace_back(Coord{ origin.col + 1, origin.row + 2 });

        if (is_in_bounds(origin.col - 1, origin.row + 2))
            legal_moves.emplace_back(Coord{ origin.col - 1, origin.row + 2 });

        if (is_in_bounds(origin.col - 2, origin.row + 1))
            legal_moves.emplace_back(Coord{ origin.col - 2, origin.row + 1 });
            */
    }

    if (piece.type == PieceType::Bishop)
    {
        auto piece_moves = moves | std::ranges::views::filter(pred);

        for (const auto& move : piece_moves)
        {
            const auto& [off_y, off_x] = move.second;

            if (is_in_bounds(origin.col + off_y, origin.row + off_x))
            {
                legal_moves.emplace_back(Coord{ origin.col + off_y, origin.row + off_x });
            }
        }

        /*
        if (is_in_bounds(origin.col - 1, origin.row - 1))
            legal_moves.emplace_back(Coord{ origin.col - 1, origin.row - 1 });
        if (is_in_bounds(origin.col + 1, origin.row - 1))
            legal_moves.emplace_back(Coord{ origin.col + 1, origin.row - 1 });
        if (is_in_bounds(origin.col + 1, origin.row + 1))
            legal_moves.emplace_back(Coord{ origin.col + 1, origin.row + 1 });
        if (is_in_bounds(origin.col - 1, origin.row + 1))
            legal_moves.emplace_back(Coord{ origin.col - 1, origin.row + 1 });

        if (is_in_bounds(origin.col - 2, origin.row - 2))
            legal_moves.emplace_back(Coord{ origin.col - 2, origin.row - 2 });
        if (is_in_bounds(origin.col + 2, origin.row - 2))
            legal_moves.emplace_back(Coord{ origin.col + 2, origin.row - 2 });
        if (is_in_bounds(origin.col + 2, origin.row + 2))
            legal_moves.emplace_back(Coord{ origin.col + 2, origin.row + 2 });
        if (is_in_bounds(origin.col - 2, origin.row + 2))
            legal_moves.emplace_back(Coord{ origin.col - 2, origin.row + 2 });

        if (is_in_bounds(origin.col - 3, origin.row - 3))
            legal_moves.emplace_back(Coord{ origin.col - 3, origin.row - 3 });
        if (is_in_bounds(origin.col + 3, origin.row - 3))
            legal_moves.emplace_back(Coord{ origin.col + 3, origin.row - 3 });
        if (is_in_bounds(origin.col + 3, origin.row + 3))
            legal_moves.emplace_back(Coord{ origin.col + 3, origin.row + 3 });
        if (is_in_bounds(origin.col - 3, origin.row + 3))
            legal_moves.emplace_back(Coord{ origin.col - 3, origin.row + 3 });

        if (is_in_bounds(origin.col - 4, origin.row - 4))
            legal_moves.emplace_back(Coord{ origin.col - 4, origin.row - 4 });
        if (is_in_bounds(origin.col + 4, origin.row - 4))
            legal_moves.emplace_back(Coord{ origin.col + 4, origin.row - 4 });
        if (is_in_bounds(origin.col + 4, origin.row + 4))
            legal_moves.emplace_back(Coord{ origin.col + 4, origin.row + 4 });
        if (is_in_bounds(origin.col - 4, origin.row + 4))
            legal_moves.emplace_back(Coord{ origin.col - 4, origin.row + 4 });

        if (is_in_bounds(origin.col - 5, origin.row - 5))
            legal_moves.emplace_back(Coord{ origin.col - 5, origin.row - 5 });
        if (is_in_bounds(origin.col + 5, origin.row - 5))
            legal_moves.emplace_back(Coord{ origin.col + 5, origin.row - 5 });
        if (is_in_bounds(origin.col + 5, origin.row + 5))
            legal_moves.emplace_back(Coord{ origin.col + 5, origin.row + 5 });
        if (is_in_bounds(origin.col - 5, origin.row + 5))
            legal_moves.emplace_back(Coord{ origin.col - 5, origin.row + 5 });

        if (is_in_bounds(origin.col - 6, origin.row - 6))
            legal_moves.emplace_back(Coord{ origin.col - 6, origin.row - 6 });
        if (is_in_bounds(origin.col + 6, origin.row - 6))
            legal_moves.emplace_back(Coord{ origin.col + 6, origin.row - 6 });
        if (is_in_bounds(origin.col + 6, origin.row + 6))
            legal_moves.emplace_back(Coord{ origin.col + 6, origin.row + 6 });
        if (is_in_bounds(origin.col - 6, origin.row + 6))
            legal_moves.emplace_back(Coord{ origin.col - 6, origin.row + 6 });

        if (is_in_bounds(origin.col - 7, origin.row - 7))
            legal_moves.emplace_back(Coord{ origin.col - 7, origin.row - 7 });
        if (is_in_bounds(origin.col + 7, origin.row - 7))
            legal_moves.emplace_back(Coord{ origin.col + 7, origin.row - 7 });
        if (is_in_bounds(origin.col + 7, origin.row + 7))
            legal_moves.emplace_back(Coord{ origin.col + 7, origin.row + 7 });
        if (is_in_bounds(origin.col - 7, origin.row + 7))
            legal_moves.emplace_back(Coord{ origin.col - 7, origin.row + 7 });

        if (is_in_bounds(origin.col - 8, origin.row - 8))
            legal_moves.emplace_back(Coord{ origin.col - 8, origin.row - 8 });
        if (is_in_bounds(origin.col + 8, origin.row - 8))
            legal_moves.emplace_back(Coord{ origin.col + 8, origin.row - 8 });
        if (is_in_bounds(origin.col + 8, origin.row + 8))
            legal_moves.emplace_back(Coord{ origin.col + 8, origin.row + 8 });
        if (is_in_bounds(origin.col - 8, origin.row + 8))
            legal_moves.emplace_back(Coord{ origin.col - 8, origin.row + 8 });

        */
    }

    if (piece.type == PieceType::Pawn)
    {
        auto piece_moves = moves | std::ranges::views::filter(pred);

        for (const auto& move : piece_moves)
        {
            const auto& [off_y, off_x] = move.second;

            if (is_in_bounds(origin.col + off_y, origin.row + (sign * off_x)))
            {
                legal_moves.emplace_back(Coord{ origin.col + off_y, origin.row + (sign * off_x) });
            }
        }

        /*
        // if it is a first move ...
        legal_moves.emplace_back(Coord{ origin.col, origin.row + (sign * 1) });
        legal_moves.emplace_back(Coord{ origin.col, origin.row + (sign * 2) });

        // if the square up and to the left or right is not empty, then an attacking diagonal move is legal
        */
    }



        if (piece.type == PieceType::Pawn)
        {
            if (piece.number_moves >= 1)
            {
                if (capture)
                {
                    move_to = Coord{ origin.col + off_y, origin.row + (sign * 1) };
                }
                else
                {
                    // After the first move, pawn can only move forward one square
                    move_to = Coord{ origin.col + off_y, origin.row + (sign * 1) };
                }
            }
            else
            {
                if (capture)
                {
                    move_to = Coord{ origin.col + (sign * 1), origin.row + (sign * 1) };
                }
                else
                {
                    move_to = Coord{ origin.col + off_y, origin.row + (sign * off_x) };
                }
            }
        }


    friend void swap(Piece& lhs, Piece& rhs)
    {
        std::cout << "swap(" << lhs << ", " << rhs << ")\n";
        std::swap(lhs, rhs);
    }

    friend std::ostream& operator<<(std::ostream& os, Piece& piece)
    {
        return os << to_string<Colors>(piece.color) << " " 
                  << to_string<PieceTypes>(piece.type) << " at: [" 
                  << piece.position.file << "," << piece.position.rank << "]";
    }



Origin: col 2, row 7

-1,0
-2,0
0,-1
0,-2

Moves
1,7
0,7
2,6
2,5

Bb5
Origin: col 2, row 7
3, 6
1, 6
1, 8
3, 8

Origin: col 5, row 7
6, 6
4, 6





std::vector<Coord> get_moves(const Piece& piece, const std::array<Piece, 64>& board, bool capture)
{
    const int sign = (piece.color == Color::Black) ? 1 : -1;
	
    std::vector<Coord> legal_moves;

    Coord origin = to_coord(piece.position);

	if(piece.type == PieceType::Rook)
	{
		for(int c = 1; c < 8; ++c)
		{
			Coord move_to{origin.col - c, origin.row}
			if(!is_in_bounds(move_to))
				break;
			if(!is_empty(move_to, board))
				break;
			legal_moves.emplace_back(move_to);
		}
	
		for(int c = 1; c < 8; ++c)
		{
			Coord move_to{origin.col + c, origin.row}
			if(!is_in_bounds(move_to))
				break;
			if(!is_empty(move_to, board))
				break;
			legal_moves.emplace_back(move_to);
		}
	
		for(int r = 1; r < 8; ++r)
		{
			Coord move_to{origin.col, origin.row + (sign * r)}
			if(!is_in_bounds(move_to))
				break;
			if(!is_empty(move_to, board))
				break;
			legal_moves.emplace_back(move_to);
		}
	
		for(int r = 1; r < 8; ++r)
		{
			Coord move_to{origin.col, origin.row - (sign * r)}
			if(!is_in_bounds(move_to))
				break;
			if(!is_empty(move_to, board))
				break;
			legal_moves.emplace_back(move_to);
		}
	}
	
	return legal_moves;


/*
// Check which pieces are available
auto output = [](const auto& piece)
	{ std::cout << to_string<Colors>(piece.color) << " "
	<< to_string<PieceTypes>(piece.type) << " at: ["
	<< piece.position.file << "," << piece.position.rank << "]\n"; };
std::ranges::for_each(std::begin(pieces), std::end(pieces), output);
*/

