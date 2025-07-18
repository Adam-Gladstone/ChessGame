#include "pch.h"

using namespace std::literals;

TEST(TestEnums, TestColors) 
{
	using namespace chess;
	
	// Arrange
	constexpr std::string_view black = to_string<Colors>(Color::Black);
	constexpr std::string_view white = to_string<Colors>(Color::White);
	constexpr std::string_view none = to_string<Colors>(Color::None);

	// Assert
	EXPECT_EQ(black, std::string_view{ "Black"sv });
	EXPECT_EQ(white, std::string_view{ "White"sv });
	EXPECT_EQ(none, std::string_view{ "None"sv });
}

TEST(TestEnums, TestPieces)
{
	using namespace chess;

	// Arrange/Act
	constexpr std::string_view king = to_string<PieceTypes>(PieceType::King);
	constexpr std::string_view queen = to_string<PieceTypes>(PieceType::Queen);
	constexpr std::string_view bishop = to_string<PieceTypes>(PieceType::Bishop);
	constexpr std::string_view knight = to_string<PieceTypes>(PieceType::Knight);
	constexpr std::string_view rook = to_string<PieceTypes>(PieceType::Rook);
	constexpr std::string_view pawn = to_string<PieceTypes>(PieceType::Pawn);
	constexpr std::string_view empty = to_string<PieceTypes>(PieceType::Empty);

	// Assert
	EXPECT_EQ(king, std::string_view{ "King"sv });
	EXPECT_EQ(queen, std::string_view{ "Queen"sv });
	EXPECT_EQ(bishop, std::string_view{ "Bishop"sv });
	EXPECT_EQ(knight, std::string_view{ "Knight"sv });
	EXPECT_EQ(rook, std::string_view{ "Rook"sv });
	EXPECT_EQ(pawn, std::string_view{ "Pawn"sv });
	EXPECT_EQ(empty, std::string_view{ "Empty"sv });
}

TEST(TestEnums, TestOutcomes)
{
	using namespace chess;

	// Arrange/Act
	constexpr std::string_view draw = to_string<Outcomes>(Outcome::Draw);
	constexpr std::string_view checkmate = to_string<Outcomes>(Outcome::Checkmate);
	constexpr std::string_view resign = to_string<Outcomes>(Outcome::Resign);

	// Assert
	EXPECT_EQ(draw, std::string_view{ "Draw"sv });
	EXPECT_EQ(checkmate, std::string_view{ "Checkmate"sv });
	EXPECT_EQ(resign, std::string_view{ "Resign"sv });
}

