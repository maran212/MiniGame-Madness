#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include "screenBuffer.h"
#include <conio.h>

using namespace std;

vector<vector<int>> maze;

// Check if the cell is within bounds and is an open path
bool isValid(int x, int y, int width, int height)
{
    return x >= 0 && x < width && y >= 0 && y < height && maze[x][y] == 0;
}

// Recursive maze generation
void generateMazeRecursive(int x, int y, int width, int height)
{
    vector<pair<int, int>> directions = { {0, 1}, {1, 0}, {0, -1}, {-1, 0} };
    random_shuffle(directions.begin(), directions.end());

    for (auto dir : directions)
    {
        int newX = x + dir.first * 2;
        int newY = y + dir.second * 2;

        if (isValid(newX, newY, width, height))
        {
            maze[newX][newY] = 0;
            maze[x + dir.first][y + dir.second] = 0;
            generateMazeRecursive(newX, newY, width, height);
        }
    }
}

// Initialize and generate the maze
void generateMaze(int height, int width)
{
    maze = vector<vector<int>>(height, vector<int>(width, 1));

    srand(time(0));
    int startX = 2 * (rand() % ((width - 2) / 2)) + 1;
    int startY = 2 * (rand() % ((height - 2) / 2)) + 1;

    maze[startX][startY] = 0;
    generateMazeRecursive(startX, startY, width, height);
}

// Print the maze
void printMaze(screenBuffer& sb)
{
    int height = maze.size();
    int width = maze[0].size();

    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            if (maze[x][y] == 1)
            {
                sb.writeToScreen(x, y, " ", 7, 7);
            }
            else
            {
                sb.writeToScreen(x, y, " ", 0, 0);
            }
        }
    }

    int entranceX, exitX;

    // Ensure the entrance and exit are placed on a valid path
    do {
        entranceX = 2 * (rand() % (width / 2));
    } while (maze[entranceX][0] != 0);

    do {
        exitX = 2 * (rand() % (width / 2));
    } while (maze[exitX][height - 1] != 0);

    sb.writeToScreen(entranceX, 0, " ", 2, 2);
    sb.writeToScreen(exitX, height - 1, " ", 1, 1);

    sb.setCursorPosition(entranceX, 0);
}

// Move through the maze
bool move(int input, screenBuffer& sb)
{
    int height = maze.size();
    int width = maze[0].size();
    pair<int, int> position = sb.getCursorPosition();

    if (position.second == height - 1)
    {
        sb.writeToScreen(0, height + 1, "You have reached the exit!", 15, 0);
        return true;
    }

    switch (input)
    {
    case 'w': // Up
        if (isValid(position.first, position.second - 1, width, height))
        {
            sb.writeToScreen(position.first, position.second, " ", 0, 0);
            sb.setCursorPosition(position.first, position.second - 1);
            sb.writeToScreen(position.first, position.second - 1, "*", 3, 0);
        }
        break;
    case 's': // Down
        if (isValid(position.first, position.second + 1, width, height))
        {
            sb.writeToScreen(position.first, position.second, " ", 0, 0);
            sb.setCursorPosition(position.first, position.second + 1);
            sb.writeToScreen(position.first, position.second + 1, "*", 3, 0);
        }
        break;
    case 'a': // Left
        if (isValid(position.first - 1, position.second, width, height))
        {
            sb.writeToScreen(position.first, position.second, " ", 0, 0);
            sb.setCursorPosition(position.first - 1, position.second);
            sb.writeToScreen(position.first - 1, position.second, "*", 3, 0);
        }
        break;
    case 'd': // Right
        if (isValid(position.first + 1, position.second, width, height))
        {
            sb.writeToScreen(position.first, position.second, " ", 0, 0);
            sb.setCursorPosition(position.first + 1, position.second);
            sb.writeToScreen(position.first + 1, position.second, "*", 3, 0);
        }
        break;
    default:
        break;
    }

    return false;
}

void mazeGame()
{
    screenBuffer sb;
    generateMaze(71, 71);
    printMaze(sb);
    SetConsoleActiveScreenBuffer(sb.getScreenHandle());

    bool finished = false;
    while (!finished)
    {
        if (_kbhit())
        {
            finished = move(_getch(), sb);
        }
    }
}
