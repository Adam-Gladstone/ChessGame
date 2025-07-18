#include "pch.h"

using namespace std::literals;

TEST(TestCastling, TestIsKingside)
{
	using namespace chess;

	// Arrange
	Move move(Color::White, "O-O"sv);

	// Assert
	EXPECT_EQ(move.is_queenside(), false);
	EXPECT_EQ(move.is_kingside(), true);
}

TEST(TestCastling, TestIsQueenside)
{
	using namespace chess;

	// Arrange
	Move move(Color::Black, "O-O-O"sv);

	// Assert
	EXPECT_EQ(move.is_queenside(), true);
	EXPECT_EQ(move.is_kingside(), false);
}

TEST(TestCastling, TestWhiteKingsideCastling)
{
	using namespace chess;

	// Arrange
	static constexpr std::array<Piece, 3> kingside_setup{
		Piece{ PieceType::Rook, Color::White, {'a', 1} },
		Piece{ PieceType::King, Color::White, {'e', 1} },
		Piece{ PieceType::Rook, Color::White, {'h', 1} },
	};

	Game game;
	game.initialize(kingside_setup);

	// Act
	Move move(Color::White, "O-O"sv);
	game.turn(move);

	// Assert
	const auto& board = game.get_board();

	const Piece& queenside_rook = board.at(Position{ 'a', 1 }.to_index());
	const Piece& kingside_rook = board.at(Position{ 'f', 1 }.to_index());
	const Piece& king = board.at(Position{ 'g', 1 }.to_index());

	EXPECT_EQ(queenside_rook.type, PieceType::Rook);
	EXPECT_EQ(kingside_rook.type, PieceType::Rook);
	EXPECT_EQ(king.type, PieceType::King);
}

TEST(TestCastling, TestBlackQueensideCastling)
{
	using namespace chess;

	// Arrange
	static constexpr std::array<Piece, 3> queenside_setup{
		Piece{ PieceType::Rook, Color::Black, {'a', 8} },
		Piece{ PieceType::King, Color::Black, {'e', 8} },
		Piece{ PieceType::Rook, Color::Black, {'h', 8} },
	};

	Game game;
	game.initialize(queenside_setup);

	// Act
	Move move(Color::Black, "O-O-O"sv);
	game.turn(move);

	// Assert
	const auto& board = game.get_board();

	const Piece& queenside_rook = board.at(Position{ 'd', 8 }.to_index());
	const Piece& kingside_rook = board.at(Position{ 'h', 8 }.to_index());
	const Piece& king = board.at(Position{ 'c', 8 }.to_index());

	EXPECT_EQ(queenside_rook.type, PieceType::Rook);
	EXPECT_EQ(kingside_rook.type, PieceType::Rook);
	EXPECT_EQ(king.type, PieceType::King);
}
