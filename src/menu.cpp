#include "menu.h"

// Initialize games
HnefataflGame hnefataflGame;

NaughtsxCrossess naughtsxCrossessGame;
Hangman hangmanGame;
WordScrambler wordScramblerGame;

Con4 con4Game;


// Input function to start each game
void Menu::startGame(int input)
{
    switch (input)
    {
    case 1:
        // Call function to start Hangman
        hangmanGame.hangman();
        break;
    case 2:
        // Call function to start Connect 4
        con4Game.connect4();
        break;
    case 3:
        // Call function to start Maze
        //mazeGame();
        std::cout << "Comming Soon" << std::endl;
        break;
    case 4:
        // Call function to start Naughts and Crosses
		naughtsxCrossessGame.run();
        break;
    case 5:
        // Call function to start Checkers
		checkers();
        break;
    case 6:
        // Call the class to start Hnefatafl
        
        hnefataflGame.play();

        break;
    case 7:
        // Call function to start Sudoku
        std::cout << "Comming Soon" << std::endl;
        break;
    case 8:
        // Call function to start Word Scramble
        wordScramblerGame.run();
        break;
    case 9:
        // Call function to start Battleship
		Battleship();
        break;
    case 10:
        // Call function to start Minesweeper
        std::cout << "Comming Soon" << std::endl;
        break;
    case 11:
        // Call function to start Multiplayer Chess
        std::cout << "Comming Soon" << std::endl;
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


// Main menu function to display the menu options
void Menu::displayMenu()
{
    try
    {
		// Create a new screen buffer
		ScreenBuffer screenBuffer;

        // Define menu options
        std::wstring text[] = {
            L"MINIGAME MADNESS",
            L"1. Hangman",
            L"2. Connect 4",
            L"3. Maze",
            L"4. Naughts and Crosses",
            L"5. Checkers",
            L"6. Hnefatafl",
            L"7. Sudoku",
            L"8. Word Scramble",
            L"9. Battleship",
            L"10. Minesweeper",
            L"11. Multiplayer Chess",
            L"13. Exit",
            L"Enter a number to select a game: "
        };

        // Print menu options to the console
        int width = 50; // Adjust width based on your console
        int startY = 2; // Starting row position
        
		for (int i = 0; i < sizeof(text) / sizeof(text[0]); i++)
		{
			screenBuffer.writeToScreen(width, startY + i, text[i]);
		}

		// Set screen buffer to active
		screenBuffer.setActive();
 
    }
    catch (const std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
}
