#ifndef MAZEGAME_H
#define MAZEGAME_H

/*!
 * @file maze.h
 * @brief Contains the declaration of the maze game functions.
 * @author Angus Martin
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include "screenBuffer.h"
#include <conio.h>

 // Constants for the maze
extern std::vector<std::vector<int>> maze;

/*!
* @brief Check if a cell is valid
*/
bool isValid(int x, int y, int width, int height);

/*!
* @brief Generate the maze recursively
* @param x The x coordinate
* @param y The y coordinate
* @param width The width of the maze
* @param height The height of the maze
*/
void generateMazeRecursive(int x, int y, int width, int height);

/*!
* @brief Generate the maze
* @param height The height of the maze
* @param width The width of the maze
*/
void generateMaze(int height, int width);

/*!
* @brief Print the maze
*/
void printMaze();

/*!
* @brief Move the player in the maze
* @param input The input from the player
* @return True if the player can move, false otherwise
*/
bool move(int input);

/*!
* @brief Game Loop
*/
void mazeGame();

#endif // MAZEGAME_H
