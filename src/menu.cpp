#include "menu.h"
#include "screenBuffer.h" 
#include "hangman.h"
#include "con4.h"
#include "maze.h"
#include <iostream>
#include <conio.h>

/**
* Input function to start each game
* @param input - The input from the user
* @return void
*/
void input(int input)
{
    switch (input)
    {
    case 1:
        // Call function to start Hangman
        hangman();
        break;
    case 2:
        // Call function to start Connect 4
        connect4();
        break;
    case 3:
        // Call function to start Maze
        mazeGame();
        break;
    case 4:
        // Call function to start Naughts and Crosses
        break;
    case 5:
        // Call function to start Checkers
        break;
    case 6:
        // Call function to start Hnefatafl
        break;
    case 7:
        // Call function to start Sudoku
        break;
    case 8:
        // Call function to start Word Scramble
        break;
    case 9:
        // Call function to start Battleship
        break;
    case 10:
        // Call function to start Minesweeper
        break;
    case 11:
        // Call function to start Multiplayer Chess
        break;
    case 13:
        // Exit the program
        exit(0);
        break;
    default:
        std::cerr << "Invalid input! Please select a valid option." << std::endl;
        break;
    }
}

/**
* Menu function for MiniGame Madness
* @return void
*/
void menu()
{
    try
    {
        // Create a screen buffer instance
        screenBuffer menu;

        // Create left and right borders
        for (int i = 1; i < menu.getScreenHeight() - 1; i++)
        {
            menu.writeToScreen(0, i, "X", 0, 1);
            menu.writeToScreen(menu.getScreenWidth() - 1, i, "X", 0, 1);
        }

        // Create top and bottom borders
        for (int i = 0; i < menu.getScreenWidth(); i++)
        {
            menu.writeToScreen(i, 0, "X", 0, 1);
            menu.writeToScreen(i, menu.getScreenHeight() - 1, "X", 0, 1);
        }

        // Set cursor visibility to false
        menu.setCursorVisibility(false);

        // Set the menu options
        std::string text[] = {
            "MINIGAME MADNESS",
            "1. Hangman",
            "2. Connect 4",
            "3. Maze",
            "4. Naughts and Crosses",
            "5. Checkers",
            "6. Hnefatafl",
            "7. Sudoku",
            "8. Word Scramble",
            "9. Battleship",
            "10. Minesweeper",
            "11. Multiplayer Chess",
            "13. Exit",
            "Enter a number to select a game: "
        };

        for (int i = 0; i < sizeof(text) / sizeof(text[0]); i++)
        {
            menu.writeToScreen(menu.getScreenWidth() / 2 - text[i].length() / 2, menu.getScreenHeight() / 2 + i, text[i]);
        }

        // Set menu to active
        SetConsoleActiveScreenBuffer(menu.getScreenHandle());

        // Wait for user input
        while (true)
        {
            if (_kbhit())
            {
                int ch = _getch() - '0';  // Convert char to int
                input(ch);
            }
        }
    }
    catch (const std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
}
