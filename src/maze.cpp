#include "maze.h"  

// Checks if position is vaild  
bool Maze::isValidPosition(std::pair<int, int> position) const {  
   return position.first >= 0 && position.first < WIDTH && position.second >= 0 && position.second < HEIGHT;  
}  

// Picks a random direction to walk in  
Direction Maze::pickRandomDirection() {
   // Get the random number  
   int random = rand() % 4; 

   Direction direction = Direction::NORTH;

   // Get the direction  
   switch (random) {  
   case 0:  
       direction = Direction::NORTH;  
   case 1:  
       direction = Direction::SOUTH;
   case 2:  
       direction = Direction::EAST;
   case 3:  
       direction = Direction::WEST;
   }  

   return direction;
}  

// Gets the opposite direction  
Direction Maze::getOppositeDirection(Direction direction) const {  
	Direction opposite = Direction::NORTH;

    switch (direction) {
    case Direction::NORTH:
        opposite = Direction::SOUTH;
    case Direction::SOUTH:
        opposite = Direction::NORTH;
    case Direction::EAST:
        opposite = Direction::WEST;
    case Direction::WEST:
        opposite = Direction::EAST;
    }

	return opposite;
}  

// Links nodes in the maze  
void Maze::linkNodes(std::pair<int, int> start, std::pair<int, int> end) {  
   // Get the nodes  
   std::unique_ptr<MazeNode>& startNode = mazeMap[start];  
   std::unique_ptr<MazeNode>& endNode = mazeMap[end];  

   if (startNode && endNode) {  
       // Get the direction  
       Direction direction = (start.first == end.first) ? ((start.second < end.second) ? Direction::SOUTH : Direction::NORTH) : ((start.first < end.first) ? Direction::EAST : Direction::WEST);  

       // Link the nodes  
       startNode->addNeighbor(endNode.get(), direction);  
       endNode->addNeighbor(startNode.get(), getOppositeDirection(direction));  
   }  
}  

// Erase loops in the walk  
std::vector<std::pair<int, int>> Maze::eraseLoop(std::vector<std::pair<int, int>> path, std::pair<int, int> current) {  
   auto startOfLoop = std::find(path.begin(), path.end(), current);  

   if (startOfLoop != path.end()) {  
       // Erase all elements after and including the current position  
       path.erase(startOfLoop, path.end());  
   }  

   return path;  
}  

// Next step in the walk  
std::pair<int, int> Maze::nextStep(std::pair<int, int> current) {  
   // Get the random direction  
   Direction direction = pickRandomDirection();  
   std::pair<int, int> next = std::make_pair(OUT_OF_BOUNDS, OUT_OF_BOUNDS);  

   // Get the next position  
   switch (direction) {  
   case Direction::NORTH:  
       if (current.second - 1 > OUT_OF_BOUNDS)  
       {  
           next = std::make_pair(current.first, current.second - 1);  
       }  
       break;  
   case Direction::SOUTH:  
       if (current.second + 1 < HEIGHT)  
       {  
           next = std::make_pair(current.first, current.second + 1);  
       }  
       break;  
   case Direction::EAST:  
       if (current.first + 1 < WIDTH)  
       {  
           next = std::make_pair(current.first + 1, current.second);  
       }  
       break;  
   case Direction::WEST:  
       if (current.first - 1 > OUT_OF_BOUNDS)
       {  
           next = std::make_pair(current.first - 1, current.second);  
       }  
   }  

   return next;  
}  

// Start random walk  
std::vector<std::pair<int, int>> Maze::randomWalk(std::pair<int, int> start) {  
   std::vector<std::pair<int, int>> path;  
   std::pair<int, int> current = start;

   while (inMaze.find(current) == inMaze.end()) {  
       path.push_back(current); 
       std::pair<int, int> next = nextStep(current);  

       if (!isValidPosition(next)) {  
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

   // List to hold all available positions not in the maze
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

   while (inMaze.size() < WIDTH * HEIGHT) {
	   // Get a random position to start the walk from.
	   int randomIndex = rand() % availablePositions.size();
	   start = *std::next(availablePositions.begin(), randomIndex);
	   availablePositions.erase(start);

	   // Perform a random walk
	   std::vector<std::pair<int, int>> path = randomWalk(start);

	   // Add the path to the maze
	   for (auto position : path) {
		   inMaze.insert(position);
	   }

	   // Link the nodes in the path
	   for (int i = 0; i < path.size() - 1; i++) {
		   linkNodes(path[i], path[i + 1]);
	   }

   }
}

// Deafult Maze constructor 21x21
Maze::Maze() {
    srand(static_cast<unsigned int>(time(0)));
    generateMaze(21, 21);
}

// Maze constructor with width and height
Maze::Maze(int width, int height) {
	srand(static_cast<unsigned int>(time(0)));
	generateMaze(width, height);
}