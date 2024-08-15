#include "menu.h"
#include <iostream>
#include <windows.h>

int main()
{
	std::cout << "Welcome to MiniGame Madness!" << std::endl;

	Sleep(1000); // Sleep for 1 second
	// Call the menu function
	menu();	

	return 0;
}