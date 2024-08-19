#ifndef MAZEGAME_H
#define MAZEGAME_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include "screenBuffer.h"
#include <conio.h>

// Maze represented as a 2D vector of integers
extern std::vector<std::vector<int>> maze;

// Check if the cell is within bounds and is an open path
bool isValid(int x, int y, int width, int height);

// Recursive maze generation
void generateMazeRecursive(int x, int y, int width, int height);

// Initialize and generate the maze
void generateMaze(int height, int width);

// Print the maze
void printMaze(screenBuffer& sb);

// Move through the maze
bool move(int input, screenBuffer& sb);

// Start the maze game
void mazeGame();

#endif // MAZEGAME_H
