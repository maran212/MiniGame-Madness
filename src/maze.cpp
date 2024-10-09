#include "maze.h"  

// Maze constructor with width and height
Maze::Maze(int width, int height) {
    srand(static_cast<unsigned int>(time(0)));
    generateMaze(width, height);
}

// Checks if position is vaild  
bool Maze::isValidPosition(std::pair<int, int> position) const {
    return (position.first >= 0 && position.first < WIDTH) &&
        (position.second >= 0 && position.second < HEIGHT);
}


// Picks a random direction to walk in  
Direction Maze::pickRandomDirection(std::vector<Direction>& directions) {
    return directions[rand() % directions.size()];
}

// Gets the opposite direction  
Direction Maze::getOppositeDirection(Direction direction) const {  
	Direction opposite = Direction::NORTH;

    switch (direction) {
    case Direction::NORTH:
        opposite = Direction::SOUTH;
		break;
    case Direction::SOUTH:
        opposite = Direction::NORTH;
        break;
    case Direction::EAST:
        opposite = Direction::WEST;
        break;
    case Direction::WEST:
        opposite = Direction::EAST;
        break;
    default: 
        break;
    }

	return opposite;
}  

// Links nodes in the maze  
void Maze::linkNodes(std::pair<int, int> start, std::pair<int, int> end) {  
   // Get the nodes  
   std::unique_ptr<MazeNode>& startNode = mazeMap[start];  
   std::unique_ptr<MazeNode>& endNode = mazeMap[end];  

   if (startNode && endNode) {
       // Determine the direction based on position differences
       Direction direction;
       if (start.first == end.first) {
           direction = (start.second < end.second) ? Direction::EAST : Direction::WEST;
       }
       else {
           direction = (start.first < end.first) ? Direction::SOUTH : Direction::NORTH;
       }

       // Link the nodes
       startNode->addNeighbor(endNode.get(), direction);
       endNode->addNeighbor(startNode.get(), getOppositeDirection(direction));
   }
}  

// Erase any loop that occurs in the walk
std::vector<std::pair<int, int>> Maze::eraseLoop(std::vector<std::pair<int, int>> path, std::pair<int, int> current) {
    auto startOfLoop = std::find(path.begin(), path.end(), current);
    if (startOfLoop != path.end()) {
        path.erase(startOfLoop + 1, path.end()); // Preserve 'current' in the path
    }
    return path;
}

 
// Next step in the walk  
std::pair<int, int> Maze::nextStep(std::pair<int, int> current) {
    std::vector<Direction> directions = { Direction::NORTH, Direction::SOUTH, Direction::EAST, Direction::WEST };
    std::pair<int, int> next = current;

    // Keep picking directions until a valid position is found or no directions remain
    while (directions.size() > 0) {
        // Pick a random direction
        Direction direction = pickRandomDirection(directions);

        switch (direction) {
        case Direction::NORTH:
            if (current.second - 1 > OUT_OF_BOUNDS) {
                next = std::make_pair(current.first, current.second - 1);
            }
            break;
        case Direction::SOUTH:
            if (current.second + 1 < HEIGHT) {
                next = std::make_pair(current.first, current.second + 1);
            }
            break;
        case Direction::EAST:
            if (current.first + 1 < WIDTH) {
                next = std::make_pair(current.first + 1, current.second);
            }
            break;
        case Direction::WEST:
            if (current.first - 1 > OUT_OF_BOUNDS) {
                next = std::make_pair(current.first - 1, current.second);
            }
            break;
        }

        // If the next position is valid, return it
        if (isValidPosition(next)) {
            return next;
        }

        // Remove the chosen direction from the list since it led to an invalid move
        directions.erase(std::remove(directions.begin(), directions.end(), direction), directions.end());
    }

    // If no valid moves are found, return the current position (i.e., no movement)
    return next;
}


// Start random walk  
std::vector<std::pair<int, int>> Maze::randomWalk(std::pair<int, int> start) {
    std::vector<std::pair<int, int>> path;
    std::pair<int, int> current = start;

    // Continue walking until a node in the maze is encountered
    while (inMaze.find(current) == inMaze.end()) {
        path.push_back(current); 

        std::pair<int, int> next = nextStep(current);

        // If no valid movement is possible (next == current), break the loop
        if (next == current) {
            break;
        }

        current = next;
        path = eraseLoop(path, current);
    }

    return path;
}


// Generate maze  
void Maze::generateMaze(int width, int height) {
    WIDTH = width;
    HEIGHT = height;

    mazeMap.clear();
    inMaze.clear();

    // Set to hold all available positions not yet in the maze
    std::set<std::pair<int, int>> availablePositions;

    // Create nodes for each position in the maze
    for (int i = 0; i < WIDTH; i++) {
        for (int j = 0; j < HEIGHT; j++) {
            mazeMap[std::make_pair(i, j)] = std::make_unique<MazeNode>();
            availablePositions.insert(std::make_pair(i, j));
        }
    }

    // Start maze at a random position
    std::pair<int, int> start = std::make_pair(rand() % WIDTH, rand() % HEIGHT);
    inMaze.insert(start);
    availablePositions.erase(start);

    // Continue generating the maze until all positions are in the maze
    while (inMaze.size() < WIDTH * HEIGHT) {
        // Get a random position to start the walk from
        int randomIndex = rand() % availablePositions.size();
        start = *std::next(availablePositions.begin(), randomIndex);
        availablePositions.erase(start);

        // Perform a random walk from the selected position
        std::vector<std::pair<int, int>> path = randomWalk(start);

        // Add the path to the maze and link nodes along the way
        for (size_t i = 0; i < path.size(); ++i) {
            const std::pair<int, int>& position = path[i];

             inMaze.insert(position);

            // Link the current node with the next node in the path
            if (i < path.size() - 1) {
                linkNodes(path[i], path[i + 1]);
            }
        }
    }
}


// Print the maze to the console
void Maze::printMaze() {
    screenBuffer.clearScreen();

    for (int row = 0; row < HEIGHT; row++) {
        std::wstring midRow = L"|";
        std::wstring subRow = L"+";

        for (int col = 0; col < WIDTH; col++) {
            std::pair<int, int> position = std::make_pair(row, col);

            // Vertical  wall (East connection)
            if (mazeMap.at(position)->getNeighbor(Direction::EAST) == nullptr) {
                midRow += L" |";  
            }
            else {
                midRow += L"  ";  // No wall (open path)
            }

            // Horizontal wall (South connection)
            if (mazeMap.at(position)->getNeighbor(Direction::SOUTH) == nullptr) {
                subRow += L"-+";   
            }
            else {
                subRow += L" +";   // No wall (open path)
            }
        }

        // Write the rows to the screen
        screenBuffer.writeToScreen(0, row * 2, midRow);      
        screenBuffer.writeToScreen(0, row * 2 + 1, subRow);  
    }
}


// Run the maze game
int Maze::run() {
	// Set the player position to the start of the maze
	//playerPosition = start;

	// Print the maze
    screenBuffer.setActive();
	printMaze();

	Sleep(100000);

	// Loop until the player reaches the end of the maze
	while (playerPosition != end) {
		// Get the player input
		char input = _getch();

		// Move the player based on the input
		switch (input) {
		case 'w':
			if (mazeMap.at(playerPosition)->getNeighbor(Direction::NORTH) != nullptr) {
				playerPosition = std::make_pair(playerPosition.first, playerPosition.second - 1);
			}
			break;
		case 's':
			if (mazeMap.at(playerPosition)->getNeighbor(Direction::SOUTH) != nullptr) {
				playerPosition = std::make_pair(playerPosition.first, playerPosition.second + 1);
			}
			break;
		case 'a':
			if (mazeMap.at(playerPosition)->getNeighbor(Direction::WEST) != nullptr) {
				playerPosition = std::make_pair(playerPosition.first - 1, playerPosition.second);
			}
			break;
		case 'd':
			if (mazeMap.at(playerPosition)->getNeighbor(Direction::EAST) != nullptr) {
				playerPosition = std::make_pair(playerPosition.first + 1, playerPosition.second);
			}
			break;
		default:
			break;
		}

		// Print the maze
		printMaze();
	}

	return 0;
}