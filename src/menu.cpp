#include "screenBuffer.h"
#include <iostream>
#include <conio.h>

int main()
{
    try
    {
        // Create a screen buffer instance
        screenBuffer menu;

        // Create left and right boarder
        for (int i = 1; i < menu.getScreenHeight() - 1; i++)
        {
            menu.writeToScreen(0, i, "X", 0, 1);
            menu.writeToScreen(menu.getScreenWidth() - 1, i, "X", 0, 1);
        }

        // Create top and bottom boarder
        for (int i = 0; i < menu.getScreenWidth(); i++)
        {
            menu.writeToScreen(i, 0, "X", 0, 1);
            menu.writeToScreen(i, menu.getScreenHeight() - 1, "X", 0, 1);
        }

        // Set cursor invisible
        menu.setCursorVisibility(false);

        // Set the menu options
        std::string text[] = {"MINIGAME MADNESS", "1. Tic Tac Toa", "2. Hangman", "3. Rock Paper Scissors", "4. Exit", "Entre a number to select a game: "};

        for (size_t i = 0; i < 7; i++)
        {
            menu.writeToScreen(menu.getScreenWidth() / 2, menu.getScreenHeight() / 2 + i, text[i]);
        }

        // set menu to active
        SetConsoleActiveScreenBuffer(menu.getScreenHandle());

        // Wait for user input
        while (true)
        {
            if (_kbhit())
            {
                return _getch();
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