#pragma once

#include <string>
#include <unordered_map>
#include <functional>


namespace ChessGameConsole
{
	// A simple menu item: text and a function
	struct MenuItem
	{
		std::string text;

		std::function<bool(const std::string& prompt)> action;
	};

	// A collection of menu items
	using MenuItems = std::unordered_map<std::string, MenuItem>;

	// A class to manage the menu and submenu items
	class MenuManager
	{
	public:
		// Destructor
		~MenuManager() = default;

		// Move constructor
		MenuManager(MenuManager&& other) noexcept = delete;

		// Move assignment
		MenuManager& operator=(MenuManager&& other) noexcept = delete;

		// Copy constructor
		MenuManager(const MenuManager& other) = delete;

		// Copy assignment
		MenuManager& operator=(const MenuManager& other) = delete;

		// Creator
		static MenuManager& Instance() 
		{
			static MenuManager single;
			return single;
		}

		// Set the main menu items
		void SetMainMenu(const MenuItems& menu) { m_mainMenu = menu; }

		// Set the sub menu items
		void SetSubMenu(const MenuItems& menu) 	{ m_subMenu = menu; }

		// Print the menu
		void PrintMainMenu() const;

		// Print the sub menu
		void PrintSubMenu() const;

		// Process the user selection (input)
		bool ProcessMainMenuSelection() const;

		// Process the user selection (input)
		bool ProcessSubMenuSelection() const;

	private:
		// Constructor
		MenuManager() = default;

		// Process the user selection (input)
		bool ProcessMenuSelection(const MenuItems& menu) const;

		// Print the specified menu with the heading
		void PrintMenu(const MenuItems& menu, const std::string& heading) const;

		// A collection of top-level menu items
		MenuItems m_mainMenu;

		// A collection of sub menus
		MenuItems m_subMenu;
	};
}
