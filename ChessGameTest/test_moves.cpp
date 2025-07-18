#include "pch.h"

using namespace std::literals;

using namespace chess;

//
// https://en.wikipedia.org/wiki/Rules_of_chess#Basic_moves
//

//
// Utility function to check whether a move is valid without changing the board state
// 
static bool check_valid_move(const Move& move, Game& game, bool capture)
{
	try
	{
		const auto& board = game.get_board();

		Piece& piece = game.find(move);

		Coord dest = move.get_destination().to_coord();

		auto moves = get_moves(piece, dest, board, capture);

		return std::find(std::begin(moves), std::end(moves), dest) != std::end(moves);
	}
	catch ([[maybe_unused]] const std::exception& e)
	{
		// std::cout << e.what() << '\n';
		return false;
	}
}

TEST(TestMoves, TestValidKingMoves)
{
	constexpr Color white = Color::White;
	constexpr PieceType king = PieceType::King;

	// Arrange
	static constexpr std::array<Piece, 1> setup{ Piece{ king, white, {'f', 5} } };

	Game game;
	game.initialize(setup);

	// Act
	const bool valid_move1 = check_valid_move(Move(white, "Kg6"sv), game, false);
	const bool valid_move2 = check_valid_move(Move(white, "Kf6"sv), game, false);
	const bool valid_move3 = check_valid_move(Move(white, "Ke6"sv), game, false);
	const bool valid_move4 = check_valid_move(Move(white, "Ke5"sv), game, false);
	const bool valid_move5 = check_valid_move(Move(white, "Ke4"sv), game, false);
	const bool valid_move6 = check_valid_move(Move(white, "Kf4"sv), game, false);
	const bool valid_move7 = check_valid_move(Move(white, "Kg4"sv), game, false);
	const bool valid_move8 = check_valid_move(Move(white, "Kg5"sv), game, false);

	// Assert
	EXPECT_EQ(valid_move1, true);
	EXPECT_EQ(valid_move2, true);
	EXPECT_EQ(valid_move3, true);
	EXPECT_EQ(valid_move4, true);
	EXPECT_EQ(valid_move5, true);
	EXPECT_EQ(valid_move6, true);
	EXPECT_EQ(valid_move7, true);
	EXPECT_EQ(valid_move8, true);
}

TEST(TestMoves, TestInvalidKingMoves)
{
	constexpr Color white = Color::White;
	constexpr PieceType king = PieceType::King;

	// Arrange
	static constexpr std::array<Piece, 1> setup{ Piece{ king, white, {'e', 1} } };

	Game game;
	game.initialize(setup);

	// Act
	const bool valid_move = check_valid_move(Move(white, "Ke3"sv), game, false);

	// Assert
	EXPECT_EQ(!valid_move, true);
}

TEST(TestMoves, TestValidRookMoves)
{
	constexpr Color white = Color::White;
	constexpr PieceType rook = PieceType::Rook;

	// Arrange
	static constexpr std::array<Piece, 1> setup{ Piece{ rook, white, {'d', 5} } };

	Game game;
	game.initialize(setup);

	// Act
	const bool valid_move1 = check_valid_move(Move(white, "Rd1"sv), game, false);
	const bool valid_move2 = check_valid_move(Move(white, "Rh5"sv), game, false);
	const bool valid_move3 = check_valid_move(Move(white, "Rd8"sv), game, false);
	const bool valid_move4 = check_valid_move(Move(white, "Ra5"sv), game, false);

	// Assert
	EXPECT_EQ(valid_move1, true);
	EXPECT_EQ(valid_move2, true);
	EXPECT_EQ(valid_move3, true);
	EXPECT_EQ(valid_move4, true);
}

TEST(TestMoves, TestInvalidRookMoves)
{
	constexpr Color white = Color::White;
	constexpr PieceType rook = PieceType::Rook;

	// Arrange
	static constexpr std::array<Piece, 1> setup{ Piece{ rook, white, {'d', 5} } };

	Game game;
	game.initialize(setup);

	// Act
	const bool valid_move1 = check_valid_move(Move(white, "Rh1"sv), game, false);
	const bool valid_move2 = check_valid_move(Move(white, "Rh8"sv), game, false);
	const bool valid_move3 = check_valid_move(Move(white, "Ra1"sv), game, false);
	const bool valid_move4 = check_valid_move(Move(white, "Ra8"sv), game, false);

	// Assert
	EXPECT_EQ(!valid_move1, true);
	EXPECT_EQ(!valid_move2, true);
	EXPECT_EQ(!valid_move3, true);
	EXPECT_EQ(!valid_move4, true);
}

TEST(TestMoves, TestValidBishopMoves)
{
	constexpr Color white = Color::White;
	constexpr PieceType bishop = PieceType::Bishop;

	// Arrange
	static constexpr std::array<Piece, 1> setup{ Piece{ bishop, white, {'d', 5} } };

	Game game;
	game.initialize(setup);

	// Act
	const bool valid_move1 = check_valid_move(Move(white, "Ba2"sv), game, false);
	const bool valid_move2 = check_valid_move(Move(white, "Bg8"sv), game, false);
	const bool valid_move3 = check_valid_move(Move(white, "Ba8"sv), game, false);
	const bool valid_move4 = check_valid_move(Move(white, "Bh1"sv), game, false);

	// Assert
	EXPECT_EQ(valid_move1, true);
	EXPECT_EQ(valid_move2, true);
	EXPECT_EQ(valid_move3, true);
	EXPECT_EQ(valid_move4, true);
}

TEST(TestMoves, TestInvalidBishopMoves)
{
	constexpr Color white = Color::White;
	constexpr PieceType bishop = PieceType::Bishop;

	// Arrange
	static constexpr std::array<Piece, 1> setup{ Piece{ bishop, white, {'d', 5} } };

	Game game;
	game.initialize(setup);

	// Act
	const bool valid_move1 = check_valid_move(Move(white, "Bd1"sv), game, false);
	const bool valid_move2 = check_valid_move(Move(white, "Bh5"sv), game, false);
	const bool valid_move3 = check_valid_move(Move(white, "Bd8"sv), game, false);
	const bool valid_move4 = check_valid_move(Move(white, "Ba5"sv), game, false);

	// Assert
	EXPECT_EQ(!valid_move1, true);
	EXPECT_EQ(!valid_move2, true);
	EXPECT_EQ(!valid_move3, true);
	EXPECT_EQ(!valid_move4, true);
}

TEST(TestMoves, TestValidQueenMoves)
{
	constexpr Color white = Color::White;
	constexpr PieceType queen = PieceType::Queen;

	// Arrange
	static constexpr std::array<Piece, 1> setup{ Piece{ queen, white, {'d', 4} } };

	Game game;
	game.initialize(setup);

	// Act
	const bool valid_move1 = check_valid_move(Move(white, "Qd8"sv), game, false);
	const bool valid_move2 = check_valid_move(Move(white, "Qh8"sv), game, false);
	const bool valid_move3 = check_valid_move(Move(white, "Qh4"sv), game, false);
	const bool valid_move4 = check_valid_move(Move(white, "Qg1"sv), game, false);
	const bool valid_move5 = check_valid_move(Move(white, "Qd1"sv), game, false);
	const bool valid_move6 = check_valid_move(Move(white, "Qa1"sv), game, false);
	const bool valid_move7 = check_valid_move(Move(white, "Qa4"sv), game, false);
	const bool valid_move8 = check_valid_move(Move(white, "Qa7"sv), game, false);

	// Assert
	EXPECT_EQ(valid_move1, true);
	EXPECT_EQ(valid_move2, true);
	EXPECT_EQ(valid_move3, true);
	EXPECT_EQ(valid_move4, true);
	EXPECT_EQ(valid_move5, true);
	EXPECT_EQ(valid_move6, true);
	EXPECT_EQ(valid_move7, true);
	EXPECT_EQ(valid_move8, true);
}

TEST(TestMoves, TestInvalidQueenMoves)
{
	constexpr Color white = Color::White;
	constexpr PieceType queen = PieceType::Queen;

	// Arrange
	static constexpr std::array<Piece, 1> setup{ Piece{ queen, white, {'d', 4} } };

	Game game;
	game.initialize(setup);

	// Act
	const bool valid_move1 = check_valid_move(Move(white, "Qb5"sv), game, false);
	const bool valid_move2 = check_valid_move(Move(white, "Qc6"sv), game, false);
	const bool valid_move3 = check_valid_move(Move(white, "Qe6"sv), game, false);
	const bool valid_move4 = check_valid_move(Move(white, "Qf5"sv), game, false);
	const bool valid_move5 = check_valid_move(Move(white, "Qf3"sv), game, false);
	const bool valid_move6 = check_valid_move(Move(white, "Qe2"sv), game, false);
	const bool valid_move7 = check_valid_move(Move(white, "Qc2"sv), game, false);
	const bool valid_move8 = check_valid_move(Move(white, "Qb3"sv), game, false);

	// Assert
	EXPECT_EQ(!valid_move1, true);
	EXPECT_EQ(!valid_move2, true);
	EXPECT_EQ(!valid_move3, true);
	EXPECT_EQ(!valid_move4, true);
	EXPECT_EQ(!valid_move5, true);
	EXPECT_EQ(!valid_move6, true);
	EXPECT_EQ(!valid_move7, true);
	EXPECT_EQ(!valid_move8, true);
}

TEST(TestMoves, TestValidKnightMoves)
{
	constexpr Color white = Color::White;
	constexpr PieceType knight = PieceType::Knight;

	// Arrange
	static constexpr std::array<Piece, 1> setup{ Piece{ knight, white, {'d', 4} } };

	Game game;
	game.initialize(setup);

	// Act
	const bool valid_move1 = check_valid_move(Move(white, "Nb5"sv), game, false);
	const bool valid_move2 = check_valid_move(Move(white, "Nc6"sv), game, false);
	const bool valid_move3 = check_valid_move(Move(white, "Ne6"sv), game, false);
	const bool valid_move4 = check_valid_move(Move(white, "Nf5"sv), game, false);
	const bool valid_move5 = check_valid_move(Move(white, "Nf3"sv), game, false);
	const bool valid_move6 = check_valid_move(Move(white, "Ne2"sv), game, false);
	const bool valid_move7 = check_valid_move(Move(white, "Nc2"sv), game, false);
	const bool valid_move8 = check_valid_move(Move(white, "Nb3"sv), game, false);

	// Assert
	EXPECT_EQ(valid_move1, true);
	EXPECT_EQ(valid_move2, true);
	EXPECT_EQ(valid_move3, true);
	EXPECT_EQ(valid_move4, true);
	EXPECT_EQ(valid_move5, true);
	EXPECT_EQ(valid_move6, true);
	EXPECT_EQ(valid_move7, true);
	EXPECT_EQ(valid_move8, true);
}

TEST(TestMoves, TestValidPawnMovesNonAttacking)
{
	constexpr Color white = Color::White;
	constexpr PieceType pawn = PieceType::Pawn;

	// Arrange
	static constexpr std::array<Piece, 1> setup{ Piece{ pawn, white, {'e', 2} } };

	Game game;
	game.initialize(setup);

	// Act
	const bool valid_move1 = check_valid_move(Move(white, "e3"sv), game, false);
	const bool valid_move2 = check_valid_move(Move(white, "e4"sv), game, false);

	const bool valid_move3 = check_valid_move(Move(white, "e5"sv), game, false);

	// Assert
	EXPECT_EQ(valid_move1, true);
	EXPECT_EQ(valid_move2, true);
	EXPECT_EQ(!valid_move3, true);
}

TEST(TestMoves, TestValidPawnMovesAttacking)
{
	constexpr Color white = Color::White;
	constexpr PieceType pawn = PieceType::Pawn;

	// Arrange
	static constexpr std::array<Piece, 3> setup
	{ 
		Piece{ pawn, white, {'c', 6} },
		Piece{ PieceType::Rook, Color::Black, {'b', 7} },
		Piece{ PieceType::Rook, Color::Black, {'d', 7} },
	};

	Game game;
	game.initialize(setup);

	// Act
	const bool valid_move1 = check_valid_move(Move(white, "c7"sv), game, false);
	const bool valid_move2 = check_valid_move(Move(white, "cxb7"sv), game, true);
	const bool valid_move3 = check_valid_move(Move(white, "cxd7"sv), game, true);

	// Assert
	EXPECT_EQ(valid_move1, true);
	EXPECT_EQ(valid_move2, true);
	EXPECT_EQ(valid_move3, true);
}
