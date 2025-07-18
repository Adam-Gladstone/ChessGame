//
// ChessGameConsole.cpp
//

#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>

#include <vector>
#include <utility>
#include <numeric>

#include <Windows.h>
#include <wchar.h>

#include "MenuManager.h"

#include "ChessGame.h"


namespace ChessGameConsole
{
    //
    // Globals
    //

    // A default empty game
    chess::Game game;

    // Maintain a count of moves
    std::size_t move_count = 0;

    // Vector of game moves
    std::vector<chess::Move> moves;

    //
    // Get a move (in PGN form)
    //
    static std::string GetMove(const std::string& prompt)
    {
        std::cout << prompt << "> ";
        std::string text;
        std::getline(std::cin, text);
        return text;
    }

    //
    // Menu functions
    //

    //
    // Read a PGN file
    //
    bool OnReadFile(const std::string& /* prompt */)
    {
        std::cout << "Full filename> ";

        std::string filename;
        std::getline(std::cin, filename);

        if (filename.empty())
        {
            moves = chess::get_moves();
        }
        else
        {
            try
            {
                moves = chess::get_moves(filename);
            }
            catch (const std::exception& e)
            {
                std::cout << "Error: " << e.what() << '\n';
            }
        }

        return true;
    }

    //
    // Exit from the console application
    // 
    bool OnClose(const std::string& prompt)
    {
        std::cout << prompt << '\n';
        return false;
    }

    // Play through the file
    bool OnPlay(const std::string& prompt)
    {
        std::cout << prompt << '\n';

        move_count = 0;

        // Set the board to be empty, and initialize with all pieces in their usual places
        game.reset();
        game.initialize(chess::initial_setup);

        game.display();

        const MenuManager& theMenuManager = MenuManager::Instance();

        for (;;)
        {
            theMenuManager.PrintSubMenu();
            if (!theMenuManager.ProcessSubMenuSelection())
                break;
        }

        return true;
    }

    //
    // Play the next move
    //
    bool OnNextMove(const std::string& /*prompt*/)
    {
        try
        {
            chess::Color turn = (move_count % 2) ? chess::Color::Black : chess::Color::White;
            std::string prompt(to_string<chess::Colors>(turn));
            prompt += " Move (" + std::to_string(move_count + 1) + ")";

            if (moves.empty())
            {
                std::string text = GetMove(prompt);
                chess::Move move(turn, text);

                move.output();

                game.turn(move);
            }
            else
            {
                if (move_count >= moves.size())
                {
                    std::cout << "No more moves available in this game.\n";
                    return true;
                }

                std::cout << prompt << '\n';

                const chess::Move& move = moves.at(move_count);

                move.output();

                game.turn(move);
            }
            
            game.display();

            ++move_count;
        }
        catch (const std::exception& e)
        {
            std::cout << "Error: " << e.what() << '\n';
        }

        return true;
    }

    //
    // Play the previous move
    //
    bool OnPrevMove(const std::string& /* prompt */)
    {
        return true;
    }

    //
    // Display the list of captured pieces
    //
    bool OnShowCaptured(const std::string& /* prompt */)
    {
        game.show_captured();

        return true;
    }

    //
    // Stop playing moves
    //
    bool OnStop(const std::string& prompt)
    {
        std::cout << prompt << '\n';
        return false;
    }


    //
    // Initialize menu items
    //
    MenuItems mainMenu =
    {
        {"1", {"Read PGN File",	OnReadFile } },
        {"2", {"Play",		    OnPlay } },
        {"3", {"Quit",			OnClose } }
    };

    //
    // Initialize submenu items
    //
    MenuItems subMenu =
    {
        {"1", {"Next Move",		OnNextMove } },
        {"2", {"Previous Move",	OnPrevMove } },
        {"3", {"Show Captured",	OnShowCaptured } },
        {"4", {"Stop",			OnStop } }
    };
}

//
// Main entry point
//
int main()
{
    using namespace ChessGameConsole;

    // Support for unicode characters
    UINT oldcp = GetConsoleOutputCP();
    SetConsoleOutputCP(CP_UTF8);

    MenuManager& theMenuManager = MenuManager::Instance();

    theMenuManager.SetMainMenu(mainMenu);
    theMenuManager.SetSubMenu(subMenu);

    for (;;)
    {
        theMenuManager.PrintMainMenu();
        if (!theMenuManager.ProcessMainMenuSelection())
            break;
    }

    SetConsoleOutputCP(oldcp);

    return 0;
}
