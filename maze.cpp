#include <iostream>
#include <vector>
#include <stack>
#include "screenBuffer.h"
#include <conio.h>

using namespace std;

// Directions for moving in the maze (right, down, left, up)
const int DX[4] = {1, 0, -1, 0};
const int DY[4] = {0, 1, 0, -1};

// Cell states
enum CellState
{
    WALL,
    PATH,
    VISITED
};

class Maze
{
private:
    int width;
    int height;
    screenBuffer mazeScreen;
    vector<vector<CellState>> grid;

public:
    /**
     * Constructor for the Maze class
     * @param width The width of the maze
     * @param height The height of the maze
     * @return void
     */
    Maze(int width, int height)
    {
        // Set the width and height of the grid representing of the maze
        grid.resize(height, vector<CellState>(width, WALL));

        // Set the screen size of the existing mazeScreen object
        mazeScreen.setScreenSize(width, height);
    }

    void generate()
    {
        // Seed the random number generator with the current time
        srand(time(0));

        // Create vectors to track visited cells and the path
        vector<int> set(width, 0);
        vector<int> rowSet(width, 0);

        // Iterate through rows
        for (int y = 0; y < height; ++y)
        {
            // Initialize the set for the current row
            for (int x = 0; x < width; ++x)
            {
                // Randomly decide if the cell should be a path or a wall
                if (x > 0 && rand() % 2)
                {
                    grid[y][x] = PATH;
                }
                else
                {
                    grid[y][x] = WALL;
                }

                // Ensure vertical connectivity between sets in adjacent rows
                if (y > 0 && rowSet[x] != rowSet[x - 1])
                {
                    grid[y][x] = PATH;
                }

                // Update the rowSet to reflect the current set of the cell
                rowSet[x] = set[x];
            }

            // Connect vertical edges between the current row and the row above
            for (int x = 0; x < width; ++x)
            {
                if (y > 0 && grid[y][x] == PATH && grid[y - 1][x] == PATH)
                {
                    set[x] = set[x - 1];
                }
            }

            // Reset row set for the next row
            fill(rowSet.begin(), rowSet.end(), 0);
        }

        // Ensure final connectivity by converting any remaining walls in the last row to paths
        for (int x = 0; x < width; ++x)
        {
            if (grid[height - 1][x] == WALL)
            {
                grid[height - 1][x] = PATH;
            }
        }
    }

    /**
     * Print the maze to screen buffer
     * @return void
     */
    void print()
    {
        string mazeString = "";

        for (int y = 0; y < height; ++y)
        {
            for (int x = 0; x < width; ++x)
            {
                if (grid[y][x] == PATH)
                {
                    mazeString += " ";
                }
                else
                {
                    mazeString += "#";
                }
            }
            mazeScreen.writeToScreen(0, y, mazeString);
            mazeString = "";
        }

        SetConsoleActiveScreenBuffer(mazeScreen.getScreenHandle());
    }
};

int main()
{
    Maze maze(120, 40);
    maze.generate();
    maze.print();

    // Wait for user input
    while (true)
    {
        if (_kbhit())
        {
            return _getch();
        }
    }

    return 0;
}
