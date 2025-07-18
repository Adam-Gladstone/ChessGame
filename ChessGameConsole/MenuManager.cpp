#include <iostream>
#include <algorithm>
#include <stdexcept>

#include "MenuManager.h"

namespace ChessGameConsole 
{
    //
    // Print out the main menu items
    //
	void MenuManager::PrintMainMenu() const
	{
        PrintMenu(m_mainMenu, "M A I N   M E N U\n");
    }

    //
    // Print out the sub menu items
    //
	void MenuManager::PrintSubMenu() const
	{
        PrintMenu(m_subMenu, "S U B     M E N U\n");
	}

    //
    // Print the specified menu with the heading
    //
    void MenuManager::PrintMenu(const MenuItems& menu, const std::string& heading) const
    {
        std::cout << "\n=================\n";
        std::cout << heading;
        std::cout << "=================\n\n";

        for (const auto& [key, item] : menu)
        {
            std::cout << key << ". " << item.text << '\n';
        }
    }

    //
    // Obtain and process the user input
    //
	bool MenuManager::ProcessMainMenuSelection() const
	{
        return ProcessMenuSelection(m_mainMenu);
	}

    //
    // Obtain and process the user input
    //
    bool MenuManager::ProcessSubMenuSelection() const
    {
        return ProcessMenuSelection(m_subMenu);
    }

    //
    // Process the user selection (input) for the specified menu
    //
    bool MenuManager::ProcessMenuSelection(const MenuItems& menu) const
    {
        bool retval = true;
        std::cout << "\nEnter Selection> ";

        std::string selection;
        if (getline(std::cin, selection))
        {
            if (!selection.empty())
            {
                std::transform(
                    selection.begin(),
                    selection.end(),
                    selection.begin(),
                    [](unsigned char c) { return static_cast<char>(std::toupper(c)); }
                );
                const auto& it = menu.find(selection);
                if (it != menu.end())
                {
                    try
                    {
                        const auto& item = it->second;
                        // call operator() on the action function 
                        retval = item.action(item.text);
                    }
                    catch (const std::exception& e)
                    {
                        std::cout << e.what() << '\n';
                        retval = true;
                    }
                }
                else
                {
                    std::cout << "Unrecognised input selection. Please try again.\n";
                    retval = true;
                }
            }
        }
        return retval;
    }
}
