#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include "screenBuffer.h"
#include <conio.h>

using namespace std;

// 2D array to store the maze
vector<vector<int>> maze;

/**
 * Function to check if a cell is within the maze and is a valid path
 * @param x X-coordinate of the cell
 * @param y Y-coordinate of the cell
 * @param width Width of the maze
 * @param height Height of the maze
 * @return bool
 */
bool isValid(int x, int y, int width, int height)
{
    return x >= 0 && x < width && y >= 0 && y < height && maze[x][y] == 1;
}

/**
 * Function to recursively generate the maze
 * @param x X-coordinate of the current cell
 * @param y Y-coordinate of the current cell
 * @param width Width of the maze
 * @param height Height of the maze
 * @return void
 */
void generateMazeRecursive(int x, int y, int width, int height)
{
    // Directions for moving (Right, Down, Left, Up)
    vector<pair<int, int>> directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

    // Shuffle directions to ensure randomness
    random_shuffle(directions.begin(), directions.end());

    // Iterate through each direction
    for (auto dir : directions)
    {
        int newX = x + dir.first * 2;
        int newY = y + dir.second * 2;

        // Check if the new cell is valid and unvisited
        if (isValid(newX, newY, width, height))
        {
            // Mark the new cell as empty
            maze[newX][newY] = 0;

            // Remove the wall between the current cell and the new cell
            maze[x + dir.first][y + dir.second] = 0;

            // Recursively generate the maze from the new cell
            generateMazeRecursive(newX, newY, width, height);
        }
    }
}

/**
 * Function to generate the maze
 * @param height Height of the maze
 * @param width Width of the maze
 * @return void
 */
void generateMaze(int height, int width)
{
    // Initialize the maze with all walls
    maze = vector<vector<int>>(height, vector<int>(width, 1));

    // Set edge cells as walls
    for (int i = 0; i < height; ++i)
    {
        maze[i][0] = 1;         // Left edge
        maze[i][width - 1] = 1; // Right edge
    }
    for (int j = 0; j < width; ++j)
    {
        maze[0][j] = 1;          // Top edge
        maze[height - 1][j] = 1; // Bottom edge
    }

    // Random seed
    srand(time(0));

    // Randomly select the starting point, ensuring it is not on the edge
    int startX = 2 * (rand() % ((width - 2) / 2)) + 1;  // Ensure starting point is odd
    int startY = 2 * (rand() % ((height - 2) / 2)) + 1; // Ensure starting point is odd

    // Mark the starting point as empty
    maze[startX][startY] = 0;

    // Start maze generation from the starting point
    generateMazeRecursive(startX, startY, width, height);
}

/**
 * Function to print the maze using the screen buffer
 * @param sb Screen buffer object
 * @return void
 */
void printMaze(screenBuffer &sb)
{
    // Get the maze dimensions
    int height = maze.size();
    int width = maze[0].size();

    // Loop through the maze and print it
    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            if (maze[x][y] == 1)
            {
                // Print walls
                sb.writeToScreen(x, y, " ", 7, 7); // White text on white background
            }
            else
            {
                // Print paths
                sb.writeToScreen(x, y, " ", 0, 0); // Black text on black background
            }
        }
    }

    // Randomly select the entrance and exit points
    int entranceX = 2 * (rand() % (width / 2));
    int exitX = 2 * (rand() % (width / 2));

    // Print entrance and exit points
    sb.writeToScreen(entranceX, 0, " ", 2, 2);      // Green text on green background
    sb.writeToScreen(exitX, height - 1, " ", 1, 1); // Red text on red background

    // Move cursor to entrance of the maze
    sb.setCursorPosition(entranceX, 0);
}

/**
 * Function to move through the maze
 * @param input User input
 * @param sb Screen buffer object
 * @return finished bolean of if the maze is finished
 */
bool move(int input, screenBuffer &sb)
{
    // Get the maze dimensions
    int height = maze.size();
    int width = maze[0].size();

    // Get the current cursor position
    std::pair<int, int> postion = sb.getCursorPosition();

    // Check if the current position is the exit
    if (postion.second == height - 1)
    {
        // Print message and return
        sb.writeToScreen(0, height + 1, "You have reached the exit!", 15, 0); // White text on black background
        return true;
    }

    // Check the user input and move accordingly
    switch (input)
    {
    case 'w': // Up
        if (isValid(postion.first, postion.second - 1, width, height))
        {
            // remove the player character
            sb.writeToScreen(postion.first, postion.second, " ", 0, 0);

            sb.setCursorPosition(postion.first, postion.second - 1);

            // Print the player character
            sb.writeToScreen(postion.first, postion.second - 1, "*", 3, 3);
        }
        break;
    case 's': // Down
        if (isValid(postion.first, postion.second + 1, width, height))
        {
            // remove the player character
            sb.writeToScreen(postion.first, postion.second, " ", 0, 0);

            sb.setCursorPosition(postion.first, postion.second + 1);

            // Print the player character
            sb.writeToScreen(postion.first, postion.second + 1, "*", 3, 3);
        }
        break;
    case 'a': // Left
        if (isValid(postion.first - 1, postion.second, width, height))
        {
            // remove the player character
            sb.writeToScreen(postion.first, postion.second, " ", 0, 0);

            sb.setCursorPosition(postion.first - 1, postion.second);

            // Print the player character
            sb.writeToScreen(postion.first - 1, postion.second, "*", 3, 3);
        }
        break;
    case 'd': // Right
        if (isValid(postion.first + 1, postion.second, width, height))
        {
            // remove the player character
            sb.writeToScreen(postion.first, postion.second, " ", 0, 0);

            sb.setCursorPosition(postion.first + 1, postion.second);

            // Print the player character
            sb.writeToScreen(postion.first + 1, postion.second, "*", 3, 3);
        }
        break;
    default:
        break;
    }

    return false;
}

int main()
{
    // Create a screen buffer object
    screenBuffer sb;

    // Generate the maze
    generateMaze(71, 71);

    // Print the maze using the screen buffer
    printMaze(sb);
    SetConsoleActiveScreenBuffer(sb.getScreenHandle());

    // Wait for user input
    bool finished = false;
    while (!finished)
    {

        if (_kbhit())
        {
            // Move through the maze
            finished = move(_getch(), sb);
        }
    }

    return 0;
}