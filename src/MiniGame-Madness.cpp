#include "menu.h"

int main()
{	
	// Call the menu function
	Menu mainMenu;
	int output = Menu::RETURN_TO_MENU;

	do {
		output = mainMenu.displayMenu();
	} while (output == Menu::RETURN_TO_MENU);
	

	return 0;
}