#include "menu.h"

// Initialize games
Hnefatafl hnefataflGame;

NaughtsxCrossess naughtsxCrossessGame;
Hangman hangmanGame;
WordScrambler wordScramblerGame;

Con4 con4Game;


// Input function to start each game
int Menu::startGame(int input)
{
	int output = RETURN_TO_MENU;

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
        output = hnefataflGame.run();
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
		output = EXIT_GAME;
        break;
    default:
        std::cerr << "Invalid input! Please select a valid option." << std::endl;
        break;
    }

	return output;
}


// Main menu function to display the menu options
int Menu::displayMenu()
{
    try
    {
		// Create a new screen buffer
		ScreenBuffer screenBuffer;

		// Set cursor visibility
		screenBuffer.setCursorVisibility(false);

        // Define menu options
        std::wstring text[] = {
            L"MINIGAME MADNESS",
            L"Hangman",
            L"Connect 4",
            L"Maze",
            L"Naughts and Crosses",
            L"Checkers",
            L"Hnefatafl",
            L"Sudoku",
            L"Word Scramble",
            L"Battleship",
            L"Minesweeper",
            L"Multiplayer Chess",
            L"Exit",
        };

        // Print menu options to the console
        int width = 50; // Adjust width based on your console
        int startY = 2; // Starting row position
        
		for (int i = 0; i < sizeof(text) / sizeof(text[0]); i++)
		{
			screenBuffer.writeToScreen(width, startY + i, text[i]);
		}

		// Highlight the first option
		screenBuffer.writeToScreen(width, startY + 1, text[1], ScreenBuffer::FOREGROUND_NORMAL, 4);

		// Set screen buffer to active
		screenBuffer.setActive();

		// Row used to track the current selection and output of startGame
        int row = 1;
		int output = -1;

        while (output == -1) {
            int ch = _getch();  // Read first input character

            // Arrow keys send two codes, so we need to check the first and read the second
            if (ch == 0 || ch == 224) {  // Arrow keys usually start with 0 or 224
                ch = _getch();  // Get the second code

                switch (ch) {
                case 72:  // Up arrow
					if (row > 1) {
						screenBuffer.writeToScreen(width, startY + row, text[row], ScreenBuffer::FOREGROUND_NORMAL, ScreenBuffer::BACKGROUND_NORMAL);
						row--;
						screenBuffer.writeToScreen(width, startY + row, text[row], ScreenBuffer::FOREGROUND_NORMAL, 4);
					}
                    break;
                case 80:  // Down arrow
					if (row < 12) {
						screenBuffer.writeToScreen(width, startY + row, text[row], ScreenBuffer::FOREGROUND_NORMAL, ScreenBuffer::BACKGROUND_NORMAL);
						row++;
						screenBuffer.writeToScreen(width, startY + row, text[row], ScreenBuffer::FOREGROUND_NORMAL, 4);
					}
                    break;
				default:
					break;
                }
			}
            else if (ch == 13) {  // Enter key
				output = startGame(row);
                return output;
            }
        }
 
    }
    catch (const std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

	return RETURN_TO_MENU;
}
