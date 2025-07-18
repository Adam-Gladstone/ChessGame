#pragma once

namespace chess 
{
	namespace constants
	{
		//
		// The ASCII code for the lowercase letter "a" is 97.
		//
		static constexpr unsigned short ASCII_LETTER_BASE = 97;

		//
		// The ASCII code for the symbol "0" is 48.
		//
		static constexpr unsigned short ASCII_NUMBER_BASE = 48;

		//
		// Offset used to calculate the rank
		//
		static constexpr unsigned short ROW_BASE = 8;
		
		//
		// Standard board size
		//
		static constexpr unsigned short BOARD_SIZE = 8;
	}
}
