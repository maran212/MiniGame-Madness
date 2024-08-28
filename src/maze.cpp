#include "maze.h"

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

    for (const auto& dir : directions)
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
void printMaze(int playerX, int playerY)
{
    int height = maze.size();
    int width = maze[0].size();

    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            if (x == playerX && y == playerY)
            {
                std::cout << "*"; // Player representation
            }
            else if (maze[x][y] == 1)
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
    std::cout << "\033[2J" << std::endl;

    // Generate and print the maze
    generateMaze(21, 21);

    // Set the player's starting position
    int playerX = 2 * (rand() % (maze[0].size() / 2));
    int playerY = 0;

    bool finished = false;
    while (!finished)
    {
        if (_kbhit())
        {
            char input = _getch();
            finished = move(input, playerX, playerY);
            std::cout << "\033[2J" << std::endl;
            printMaze(playerX, playerY); // Print the maze with the updated player position
        }
    }
}

