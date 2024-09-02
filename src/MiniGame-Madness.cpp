#include "menu.h"

int main()
{	
	// Call the menu function
	Menu mainMenu;

	do {
		mainMenu.displayMenu();

		// Get user input
		// Get user input
		char inputText = _getch();

		// Check if the input is a number
		if (isdigit(inputText))
		{
			// Convert the input to an integer
			int number = inputText - '0';
			mainMenu.startGame(number);
		}
		else
		{
			std::cerr << "Invalid input! Please select a valid option." << std::endl;
		}

	} while (true);


	return 0;
}