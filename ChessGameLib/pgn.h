#pragma once

namespace chess
{
    //
    // Retrieve a list of PGN moves from a file
    //
    std::vector<Move> get_moves(const std::string& filename)
    {
        // Game data
        std::unordered_map<std::string, std::string> data;

        // Vector of game moves
        std::vector<Move> moves;

        std::ifstream file(filename, std::ios::in);
        std::stringstream buffer;
        buffer << file.rdbuf();

        std::string text;

        while (std::getline(buffer, text, '\n'))    // EOL removed 
        {
            if (text.starts_with('[') && text.ends_with(']'))
            {
                std::size_t pos_begin = text.find_first_of('[');
                std::size_t pos_end = text.find_first_of(']');

                std::size_t pos = text.find_first_of(' ');

                std::string key = text.substr(pos_begin + 1, pos - pos_begin - 1);
                std::string value = text.substr(pos + 2, pos_end - pos - 3);

                data[key] = value;
            }
            else if (text.starts_with('\n') || text.empty())
            {
                continue;
            }
            else
            {
                const std::string& result = data["Result"];

                std::vector<std::string> parts;
                std::string error;
                if (Utilities::String::ParseDelimited(parts, text, " ", error))
                {
                    Color color = Color::White;
                    std::string move;

                    for (const auto& part : parts)
                    {
                        std::size_t pos = part.find_first_of('.');
                        if (pos != std::string::npos)
                        {
                            move = Utilities::String::Right(part, part.size() - 1 - pos);
                        }
                        else if (part.compare(result) == 0)
                        {
                            break;
                        }
                        else if (part.empty())
                        {
                            break;
                        }
                        else
                        {
                            move = part;
                        }

                        moves.emplace_back(Move(color, move));

                        color = (color == Color::White) ? Color::Black : Color::White;
                    }
                }
                else
                {
                    std::cout << "Unable to parse string: " << error << '\n';
                }
            }
        }

        std::cout << "\n=================\n";
        std::cout << "G A M E   D A T A\n";
        std::cout << "=================\n";

        for (const auto& [key, value] : data)
        {
            std::cout << std::setw(12) << key << ": " << value << '\n';
        }

        std::cout << "=================\n\n";

        return moves;
    }

    std::vector<Move> get_moves()
    {
        // https://old.chesstempo.com/pgn-examples.html#agame1
        std::vector<Move> moves{

            Move(Color::White, "e4"sv),     // 1
            Move(Color::Black, "e5"sv),     // 2

            Move(Color::White, "Nf3"sv),    // 3
            Move(Color::Black, "Nc6"sv),    // 4

            Move(Color::White, "Bb5"sv),    // 5
            Move(Color::Black, "a6"sv),     // 6

            Move(Color::White, "Ba4"sv),    // 7
            Move(Color::Black, "Nf6"sv),    // 8

            Move(Color::White, "d3"sv),     // 9
            Move(Color::Black, "d6"sv),     // 10

            Move(Color::White, "c3"sv),     // 11
            Move(Color::Black, "Be7"sv),    // 12

            Move(Color::White, "Nbd2"sv),   // 13
            Move(Color::Black, "O-O"sv),    // 14

            Move(Color::White, "Nf1"sv),    // 15
            Move(Color::Black, "b5"sv),     // 16

            Move(Color::White, "Bc2"sv),    // 17
            Move(Color::Black, "d5"sv),     // 18

            Move(Color::White, "Qe2"sv),    // 19
            Move(Color::Black, "dxe4"sv),   // 20

            Move(Color::White, "dxe4"sv),   // 21
            Move(Color::Black, "Bc5"sv),    // 22

            Move(Color::White, "Bg5"sv),    // 23
            Move(Color::Black, "Be6"sv),    // 24

            Move(Color::White, "Ne3"sv),    // 25
            Move(Color::Black, "Re8"sv),    // 26

            Move(Color::White, "O-O"sv),    // 27
            Move(Color::Black, "Qe7"sv),    // 28

            Move(Color::White, "Nd5"sv),    // 29
            Move(Color::Black, "Bxd5"sv),   // 30

            Move(Color::White, "exd5"sv),   // 31
            Move(Color::Black, "Nb8"sv),    // 32

            Move(Color::White, "a4"sv),     // 33
            Move(Color::Black, "b4"sv),     // 34

            Move(Color::White, "cxb4"sv),   // 35
            Move(Color::Black, "Bxb4"sv),   // 36

            Move(Color::White, "Bxf6"sv),   // 37
            Move(Color::Black, "Qxf6"sv),   // 38

            Move(Color::White, "Qe4"sv),    // 39
            Move(Color::Black, "Bd6"sv),    // 40

            Move(Color::White, "Qxh7+"sv),  // 41
            Move(Color::Black, "Kf8"sv),    // 42

            Move(Color::White, "Nh4"sv),    // 43
            Move(Color::Black, "Qh6"sv),    // 44

            Move(Color::White, "Qxh6"sv),   // 45
            Move(Color::Black, "gxh6"sv),   // 46

            Move(Color::White, "Nf5"sv),    // 47
            Move(Color::Black, "h5"sv),     // 48

            Move(Color::White, "Bd1"sv),    // 49
            Move(Color::Black, "Nd7"sv),    // 50

            Move(Color::White, "Bxh5"sv),   // 51
            Move(Color::Black, "Nf6"sv),    // 52

            Move(Color::White, "Be2"sv),    // 53
            Move(Color::Black, "Nxd5"sv),   // 54

            Move(Color::White, "Rfd1"sv),   // 55
            Move(Color::Black, "Nf4"sv),    // 56

            Move(Color::White, "Bc4"sv),    // 57
            Move(Color::Black, "Red8"sv),   // 58

            Move(Color::White, "h4"sv),     // 59
            Move(Color::Black, "a5"sv),     // 60

            Move(Color::White, "g3"sv),     // 61
            Move(Color::Black, "Ne6"sv),    // 62

            Move(Color::White, "Bxe6"sv),   // 63
            Move(Color::Black, "fxe6"sv),   // 64

            Move(Color::White, "Ne3"sv),    // 65
            Move(Color::Black, "Rdb8"sv),   // 66

            Move(Color::White, "Nc4"sv),    // 67
            Move(Color::Black, "Ke7"sv),    // 68

            Move(Color::White, "Rac1"sv),   // 69
            Move(Color::Black, "Ra7"sv),    // 70

            Move(Color::White, "Re1"sv),    // 71
            Move(Color::Black, "Kf6"sv),    // 72

            Move(Color::White, "Re4"sv),    // 73
            Move(Color::Black, "Rb4"sv),    // 74

            Move(Color::White, "g4"sv),     // 75
            Move(Color::Black, "Ra6"sv),    // 76

            Move(Color::White, "Rc3"sv),    // 77
            Move(Color::Black, "Bc5"sv),    // 78

            Move(Color::White, "Rf3+"sv),   // 79
            Move(Color::Black, "Kg7"sv),    // 80

            Move(Color::White, "b3"sv),     // 81
            Move(Color::Black, "Bd4"sv),    // 82

            Move(Color::White, "Kg2"sv),    // 83
            Move(Color::Black, "Ra8"sv),    // 84

            Move(Color::White, "g5"sv),     // 85
            Move(Color::Black, "Ra6"sv),    // 86

            Move(Color::White, "h5"sv),     // 87
            Move(Color::Black, "Rxc4"sv),   // 88

            Move(Color::White, "bxc4"sv),   // 89
            Move(Color::Black, "Rc6"sv),    // 90

            Move(Color::White, "g6"sv),     // 91
        };

        return moves;
    }
}
