#include "maze.h"

// Generate Maze
void Maze::generateMaze(int width, int height) {
	for (int row = 0; row < height; row++) {
		for (int col = 0; col < width; col++) {
			MazeNode node;
			std::pair<int, int> position = std::make_pair(row, col);
			mazeMape[position] = &node;
		}
	}
}
