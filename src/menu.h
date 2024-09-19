#ifndef MENU_H
#define MENU_H

/*!
* @file Menu.h
* @brief Contains the declaration of the Menu class and its member functions.
* @author Angus Martin
*/

#include "ScreenBuffer.h" 
#include "hangman.h"
#include "con4.h"
#include "maze.h"
#include "hnefatafl.h"  
#include "wordScrambler.h"
#include "BattleshipGame.h"
#include "NaughtsxCrossess.h"
#include "chckrs.h"
#include <conio.h>

/*!
* @class Menu
* @brief A class that represents the menu of the game.
*/
class Menu {
private:
	int row; /*!< The row of the menu */
	int padding; /*!< The padding to add to x cordinate of the menu */
	int width; /*!< The width of the menu */
	int startY; /*!< The starting y cordinate of the menu */

	ScreenBuffer screenBuffer;
    /*!
    * @brief function to start a game based on the user input
    * @param input - The input from the user
    */
    int startGame(int input);

public:
    static const int RETURN_TO_MENU = 0;
    static const int EXIT_GAME = 1;

    /*!
    * @brief Function to display the menu
    */
    int displayMenu();
};

#endif // MENU_H