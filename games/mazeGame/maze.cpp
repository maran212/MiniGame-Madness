#include <iostream>
#include <vector>
#include <ctime>
#include <stack>
#include <algorithm>
#include "screenBuffer.h"
#include "windows.h"
#include <conio.h>
#include <random>

using namespace std;

// Cell states
enum CellState
{
    WALL,
    PATH
};

class Maze
{
private:
    int width;
    int height;
    vector<vector<CellState>> grid;
    screenBuffer mazeScreen;

    void randomWalk(int startX, int startY)
    {
        stack<pair<int, int>> pathStack;
        vector<vector<bool>> visited(height, vector<bool>(width, false));
        pathStack.push({startX, startY});
        visited[startY][startX] = true;

        // Random number generator and distribution
        random_device rd;                      // Obtain a random number from hardware
        mt19937 g(rd());                       // Seed the generator
        uniform_int_distribution<> dist(0, 3); // Distribution in range [0, 3]

        while (!pathStack.empty())
        {
            auto [x, y] = pathStack.top();
            pathStack.pop();
            grid[y][x] = PATH;

            // Randomly shuffle directions to ensure unbiased random walk
            vector<pair<int, int>> directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
            shuffle(directions.begin(), directions.end(), g);

            for (const auto &[dx, dy] : directions)
            {
                int nx = x + dx;
                int ny = y + dy;

                if (nx >= 0 && ny >= 0 && nx < width && ny < height)
                {
                    if (!visited[ny][nx])
                    {
                        visited[ny][nx] = true;
                        pathStack.push({nx, ny});
                        break; // Move to the next cell
                    }
                }
            }
        }
    }

public:
    Maze(int width, int height) : width(width), height(height)
    {
        grid.resize(height, vector<CellState>(width, WALL));
    }

    void generate()
    {
        srand(static_cast<unsigned>(time(0))); // Seed the random number generator

        for (int y = 0; y < height; ++y)
        {
            for (int x = 0; x < width; ++x)
            {
                if (grid[y][x] == WALL)
                {
                    randomWalk(x, y);
                }
            }
        }

        // Ensure all cells are part of the maze
        for (int y = 0; y < height; ++y)
        {
            for (int x = 0; x < width; ++x)
            {
                if (grid[y][x] == WALL)
                {
                    grid[y][x] = PATH; // Optional: ensure no isolated walls
                }
            }
        }
    }

    void print()
    {
        mazeScreen.clearScreen();

        // Top border
        for (int x = 0; x < width + 2; ++x)
        {
            mazeScreen.writeToScreen(x, 0, "#");
        }

        // Maze content with borders
        for (int y = 0; y < height; ++y)
        {
            mazeScreen.writeToScreen(0, y + 1, "#"); // Left border
            for (int x = 0; x < width; ++x)
            {
                char displayChar = (grid[y][x] == PATH) ? ' ' : 'X';
                mazeScreen.writeToScreen(x + 1, y + 1, string(1, displayChar)); // Write one character at a time
            }
            mazeScreen.writeToScreen(width + 1, y + 1, "#"); // Right border
        }

        // Bottom border
        for (int x = 0; x < width + 2; ++x)
        {
            mazeScreen.writeToScreen(x, height + 1, "#");
        }

        SetConsoleActiveScreenBuffer(mazeScreen.getScreenHandle());
    }
};

int main()
{
    // Create a maze object
    Maze maze(41, 21);

    // Generate the maze
    maze.generate();

    // Print the maze
    maze.print();

    // Wait for a key press before exiting
    while (true)
    {
        if (_kbhit())
        {
            break;
        }
    }

    return 0;
}
