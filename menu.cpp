#include "screenBuffer.h"
#include <iostream>

int main()
{
    try
    {
        // Create a screen buffer instance
        screenBuffer sb1;

        // Check if the screen buffer is active
        if (sb1.isActive())
        {
            std::cout << "Screen buffer is active." << std::endl;
        }
        else
        {
            std::cout << "Screen buffer is not active." << std::endl;
        }

        // Set the screen size
        // sb1.setScreenSize(138, 74);

        // Clear the screen
        sb1.clearScreen();

        // Set cursor position and write text
        sb1.setCursorPosition(10, 5);
        sb1.setCursorVisibility(false);

        // set sb1 to active
        SetConsoleActiveScreenBuffer(sb1.getScreenHandle());

        sb1.setScreenText(11, 5, "Hello, ScreenBuffer!", FOREGROUND_RED, BACKGROUND_BLUE); // White text on black background

        // Get and display the text from screen
        std::string text = sb1.getScreenText(0, 0, 20);
        std::cout << "Text read from screen: " << text << std::endl;

        // Wait for 10 seconds
        Sleep(10000);

        sb1.~screenBuffer();
    }
    catch (const std::exception &e)
    {
        std::cerr << "Exception: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}