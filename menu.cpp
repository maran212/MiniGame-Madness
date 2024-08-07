#include "screenBuffer.h"
#include <iostream>
#include <conio.h>

int main()
{
    try
    {
        // Create a screen buffer instance
        screenBuffer menu;

        // Set the screen size
        menu.setScreenSize(138, 74);

        // Clear the screen
        menu.clearScreen();

        // Set cursor invisible
        menu.setCursorVisibility(false);

        // Write text to the screen
        menu.setScreenText(11, 5, "Hello, ScreenBuffer!", FOREGROUND_RED, BACKGROUND_BLUE);

        // set menu to active
        SetConsoleActiveScreenBuffer(menu.getScreenHandle());

        // Wait for user input
        char input = ' ';
        
        while (input == ' ')
        {
            if (_kbhit())
            {
                input = _getch();
                std::cout << input << std::endl;
            }
        }

        menu.~screenBuffer();
    }
    catch (const std::exception &e)
    {
        std::cerr << "Exception: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}