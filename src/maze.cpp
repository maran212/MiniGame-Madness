#include "maze.h"
#include <iostream>
#include <conio.h>

std::vector<std::vector<int>> maze;

// Check if the cell is within bounds and is an open path
bool isValid(int x, int y, int width, int height)
{
    return x >= 0 && x < width && y >= 0 && y < height && maze[x][y] == 0;
}

// Recursive maze generation
void generateMazeRecursive(int x, int y, int width, int height)
{
    std::vector<std::pair<int, int>> directions = { {0, 1}, {1, 0}, {0, -1}, {-1, 0} };
    std::random_shuffle(directions.begin(), directions.end());

    for (std::pair<int, int> dir : directions)
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
    maze = std::vector<std::vector<int>>(height, std::vector<int>(width, 1));

    srand(time(0));
    int startX = 2 * (rand() % ((width - 2) / 2)) + 1;
    int startY = 2 * (rand() % ((height - 2) / 2)) + 1;

    maze[startX][startY] = 0;
    generateMazeRecursive(startX, startY, width, height);
}

// Print the maze to the console
void printMaze()
{
    int height = maze.size();
    int width = maze[0].size();

    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            if (maze[x][y] == 1)
            {
                std::cout << "#";
            }
            else
            {
                std::cout << " ";
            }
        }
        std::cout << std::endl;
    }

    int entranceX, exitX;

    // Ensure the entrance and exit are placed on a valid path
    do {
        entranceX = 2 * (rand() % (width / 2));
    } while (maze[entranceX][0] != 0);

    do {
        exitX = 2 * (rand() % (width / 2));
    } while (maze[exitX][height - 1] != 0);

    std::cout << "Entrance at (" << entranceX << ", 0)" << std::endl;
    std::cout << "Exit at (" << exitX << ", " << height - 1 << ")" << std::endl;

    // Print the player position
    std::cout << "Player starts at (" << entranceX << ", 0)" << std::endl;
}

// Move through the maze
bool move(int input, int& playerX, int& playerY)
{
    int height = maze.size();
    int width = maze[0].size();

    if (playerY == height - 1)
    {
        std::cout << "You have reached the exit!" << std::endl;
        return true;
    }

    switch (input)
    {
    case 'w': // Up
        if (isValid(playerX, playerY - 1, width, height))
        {
            playerY--;
        }
        break;
    case 's': // Down
        if (isValid(playerX, playerY + 1, width, height))
        {
            playerY++;
        }
        break;
    case 'a': // Left
        if (isValid(playerX - 1, playerY, width, height))
        {
            playerX--;
        }
        break;
    case 'd': // Right
        if (isValid(playerX + 1, playerY, width, height))
        {
            playerX++;
        }
        break;
    default:
        break;
    }

    return false;
}

void mazeGame()
{
    // Clear the console screen
    system("cls");

    // Generate and print the maze
    generateMaze(21, 21);
    printMaze();

    // Set the player's starting position
    int playerX, playerY;
    playerX = 2 * (rand() % (maze[0].size() / 2));
    playerY = 0;

    bool finished = false;
    while (!finished)
    {
        if (_kbhit())
        {
            char input = _getch();
            finished = move(input, playerX, playerY);
            system("cls"); // Clear the console screen
            printMaze();   // Print the maze with the updated player position
        }
    }
}

