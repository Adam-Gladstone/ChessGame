# Issues

# Wishlist

## ChessGameConsole
- instead of a console application for the display add a WinUI interface

## ChessGameLib
- improve underlying number representations: unsigned short = 0 - 65535 seems excessive for 64 cell locations etc: std::byte? unsigned char?
- improve the storage for the pgn text in Move: can it be a string view? or a smaller vector/array of char?
- extend the PGN file processing to parse comments (delimited by ; or {})
- handle en passant and promotion: https://en.wikipedia.org/wiki/Rules_of_chess
- add some processing of strategies

## ChessGameTest
- extend the test set to include more situations.



# Changes
## 18/07/2025
Initial checkin

