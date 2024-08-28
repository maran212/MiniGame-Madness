#ifndef MENU_H
#define MENU_H

/*!
 * @file menu.h
 * @brief Contains the declaration of the Menu class and its member functions.
 */

#include "screenBuffer.h" 
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
public:
    /*!
    * @brief Input function to start each game
    * @param input - The input from the user
    */
    void input(int input);

    /*!
    * @brief Function to display the menu
    */
    void displayMenu();
};

#endif // MENU_H