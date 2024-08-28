#ifndef MENU_H
#define MENU_H

#include "screenBuffer.h" 
#include "hangman.h"
#include "con4.h"
#include "maze.h"
#include "hnefatafl.h"
#include <iostream>
#include <conio.h>
#include "NaughtsxCrossess.h"
#include "WordScrambler.h"
#include "battleShips.h"

/**
* Input function to start each game
* @param input - The input from the user
*/
void input(int input);

/**
* Function to display the menu
*/
void menu();

#endif // MENU_H