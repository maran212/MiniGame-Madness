#ifndef MAZE_H
#define MAZE_H

/*!
 * @file maze.h
 * @brief Contains the declaration of the Maze class and its member methods.
 * @author Angus Martin
 */

#include "screenBuffer.h"
#include <map>
#include <vector>
#include <set>
#include <memory>
#include <cstdlib>  
#include <ctime>

 // Forward declaration of the test class
namespace MazeTests {
	class MazeTests;
}

/*!
 * @enum Direction
 * @brief An enumeration of possible directions of neighboring nodes.
 */
enum Direction {
	NORTH, /*!< Direction going to the top of the board. */
	SOUTH, /*!< Direction going to the bottom of the board */
	EAST, /*!< Direction going to the right of the board. */
	WEST, /*!< Direction going to the left of the board. */
};

/*!
* @struct MazeNode
* @brief A struct that represents the nodes in the graph of the maze.
* @details The default is each neighbor is set to nullptr.
*/
struct MazeNode {
    std::map<Direction, MazeNode*> neighbors; /*!< A map of directions to neighboring nodes, using raw pointers since neighbors don't own each other. */

    /*!
    * @brief Default constructor for MazeNode
    * @details Initialize the MazeNode with the type NONE
    */
	MazeNode() {
        neighbors[NORTH] = nullptr;
        neighbors[SOUTH] = nullptr;
        neighbors[EAST] = nullptr;
        neighbors[WEST] = nullptr;
    }

    /*!
    * @brief Add a neighboring node with a direction.
    * @param node - The node to add as a neighbor.
    * @param direction - The direction of the neighboring node.
	* @throws runtime_error if the neighbor already exists in the given direction.
    */
    void addNeighbor(MazeNode* node, Direction direction) {
        if (neighbors[direction] != nullptr) {
            throw std::runtime_error("Neighbor already exists in the given direction.");
        }

        neighbors[direction] = node;
    }

    /*!
    * @brief Remove a neighboring node based on a direction.
    * @param direction - The direction of the neighboring node.
	* @throws runtime_error if the neighbor is not found in the given direction.
    */
    void removeNeighbor(Direction direction) {
        if (neighbors[direction] != nullptr) {
            throw std::runtime_error("Neighbor not found in the given direction.");
        }

        neighbors.erase(direction);
    }

    /*!
    * @brief Get the neighboring node in a given direction.
    * @param direction - The direction of the neighboring node.
    * @return The neighboring node in the given direction, or nullptr if not found.
    */
    MazeNode* getNeighbor(Direction direction) const {
        auto neighbor = neighbors.find(direction);
        return (neighbor != neighbors.end()) ? neighbor->second : nullptr;
    }

    /*!
    * @brief Get all neighboring nodes.
    * @return A map of directions to neighboring nodes.
    */
    std::map<Direction, MazeNode*> getNeighbors() const {
        return neighbors;
    }
};


/*!
* @class Maze
* @brief A class that represents the maze game.
* 
* @details This class provides methods to generate the maze, handle player moves, and check game conditions.
*/
class Maze {
 private:
	 // Declare the test class as a friend
	 friend class MazeTests::MazeTests;

	 static const int OUT_OF_BOUNDS = -1; /*!< Constant to represent out of bounds. */

	 int WIDTH; /*!< Width of maze.*/
	 int HEIGHT; /*!< Height of maze.*/
	 std::map<std::pair<int, int>, std::unique_ptr<MazeNode>> mazeMap; /*!< A map of positions to nodes in the maze.*/
	 std::set<std::pair<int, int>> inMaze; /*!< Set to track which nodes are already in the maze. */

	/*!
	* @brief Generate maze
	* @details The maze is a 2D graph of nodes that are either PATH or WALL.
	* @param width - The width of the maze.
	* @param height - The height of the maze.
	*/
	 void generateMaze(int width, int height);

	 /*!
	 * @brief This method will perform a random walk from a starting node until it links back up with the maze.
	 * @details The random walk will be performed until the path links back up with the maze or try's to go out of bounds.
	 * @param start - The starting position of the node to start the walk from.
	 * @return The path of the random walk.
     */
	 std::vector<std::pair<int, int>> randomWalk(std::pair<int, int> start);

	 /*!
	 * @brief This method takes next step in the walk.
	 * @param current - The current position of the walk.
	 * @return The next position in the walk. 
	 */
	 std::pair<int, int> nextStep(std::pair<int, int> current);

	 /*!
	 * @brief This method erases any loop that occurs in the walk.
	 * @param path - The path of the random walk.
	 * @param current - The current position of the walk.
	 * @return The path with any loop erased.
	 */
	 std::vector<std::pair<int, int>> eraseLoop(std::vector<std::pair<int, int>> path, std::pair<int, int> current);

	 /*!
	 * @brief This method will link nodes in the maze.
	 * @param start - The starting position of the node to link.
	 * @param end - The ending position of the node to link.
	 */
	 void linkNodes(std::pair<int, int> start, std::pair<int, int> end);

	 /*!
	 * @brief This method will get the opposite direction.
	 * @param direction - The direction to get the opposite of.
	 * @return The opposite direction.
	 */
	 Direction getOppositeDirection(Direction direction) const;

	 /*!
	 * @brief This method will pick a random direction to walk in.
	 * @return The direction to walk in.
	 */
	 Direction pickRandomDirection();

	 /*!
	 * @brief This method checks if postion is valid.
	 * @param position - The position to check.
	 * @return True if the position is valid, false otherwise.
	 */
	 bool isValidPosition(std::pair<int, int> position) const;

public :
	
	/*!
	* @brief Default constructor for maze class.
	* @details Generates a 21 by 21 node maze.
	*/
	Maze();

	/*!
	* @brief Constructor for Maze class.
	* @param width - The width of the maze.
	* @param height - The height of the maze.
	*/
	Maze(int width, int height);
	 
	/*!
	* @brief Destructor for Maze class.
	*/
	~Maze() = default; 

	/*!
	* @brief This method will get the width of the maze.
	* @return The width of the maze.
	*/
	int getWidth() const;

	/*!
	* @brief This method will get the height of the maze.
	* @return The height of the maze.
	*/
	int getHeight() const;
};
 
#endif // MAZE_H
