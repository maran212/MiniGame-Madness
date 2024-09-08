#ifndef MENU_H
#define MENU_H

/*!
 * @file menu.h
 * @brief Contains the declaration of the Menu class and its member functions.
 * @author Angus Martin
 */

#include "ScreenBuffer.h" 
#include "hangman.h"
#include "con4.h"
#include "maze.h"
#include "hnefatafl.h"
#include "wordScrambler.h"
#include "battleShips.h"
#include "NaughtsxCrossess.h"
#include "chckrs.h"
#include <iostream>
#include <conio.h>
#include "NaughtsxCrossess.h"
#include "WordScrambler.h"
#include "battleShips.h"



/*!
* @class Menu
* @brief A class that represents the menu of the game.
*/
class Menu {
private:
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