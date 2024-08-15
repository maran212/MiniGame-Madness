#ifndef MAZEGAME_H
#define MAZEGAME_H

#include <vector>
#include "screenBuffer.h"

// Declare the maze as an external variable to be used across different files
extern std::vector<std::vector<int>> maze;

// Function prototypes
bool isValid(int x, int y, int width, int height);
void generateMazeRecursive(int x, int y, int width, int height);
void generateMaze(int height, int width);
void printMaze(screenBuffer& sb);
bool move(int input, screenBuffer& sb);
void mazeGame();

#endif // MAZEGAME_H

