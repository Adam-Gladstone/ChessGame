#pragma once

#include <string>

namespace ChessGameConsole
{
	// Read a PGN file
	bool OnReadFile(const std::string& prompt);

	// Play through the file
	bool OnPlay(const std::string& prompt);

	// Close the console application
	bool OnClose(const std::string& prompt);

	// Play the next move
	bool OnNextMove(const std::string& prompt);

	// Play the previous move
	bool OnPrevMove(const std::string& prompt);

	// Display the list of captured pieces
	bool OnShowCaptured(const std::string& prompt);

	// Stop playing moves
	bool OnStop(const std::string& prompt);
}
