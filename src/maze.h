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
        neighbors[direction] = node;
    }

    /*!
    * @brief Remove a neighboring node based on a direction.
    * @param direction - The direction of the neighboring node.
	* @throws runtime_error if the neighbor is not found in the given direction.
    */
    void removeNeighbor(Direction direction) {
        if (neighbors[direction] == nullptr) {
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
* @details This class provides methods to generate the maze, handle player moves, and check game conditions.
*/
class Maze {
 private:
	 // Declare the test class as a friend
	 friend class MazeTests::MazeTests;

	 static const int OUT_OF_BOUNDS = -1; /*!< Constant to represent out of bounds. */
	 ScreenBuffer screenBuffer; /*!< The screen buffer for displaying the game. */

	 int WIDTH; /*!< Width of maze.*/
	 int HEIGHT; /*!< Height of maze.*/

	 std::pair<int, int> start; /*!< The start position of the maze.*/
	 std::pair<int, int> end; /*!< The end position of the maze.*/
	 std::pair<int, int> playerPosition; /*!< The position of the player in the maze.*/

	 std::map<std::pair<int, int>, std::unique_ptr<MazeNode>> mazeMap; /*!< A map of positions to nodes in the maze.*/
	 std::set<std::pair<int, int>> inMaze; /*!< Set to track which nodes are already in the maze. */

	 /*!
	 * @brief Checks if postion is valid.
	 * @param position - The position to check.
	 * @return True if the position is valid, false otherwise.
	 */
	 bool isValidPosition(std::pair<int, int> position) const;

	 /*!
	 * @brief Pick a random direction to walk in.
	 * @param directions - The directions to choose from.
	 * @return The direction to walk in.
	 */
	 Direction pickRandomDirection(std::vector<Direction>& directions);

	 /*!
	 * @brief Get the opposite direction.
	 * @param direction - The direction to get the opposite of.
	 * @return The opposite direction.
	 */
	 Direction getOppositeDirection(Direction direction) const;

	 /*!
	 * @brief Link nodes in the maze.
	 * @param start - The starting position of the node to link.
	 * @param end - The ending position of the node to link.
	 */
	 void linkNodes(std::pair<int, int> start, std::pair<int, int> end);

	 /*!
	 * @brief Erases any loop that occurs in the walk.
	 * @param path - The path of the random walk.
	 * @param current - The current position of the walk.
	 * @return The path with any loop erased.
	 */
	 std::vector<std::pair<int, int>> eraseLoop(std::vector<std::pair<int, int>> path, std::pair<int, int> current);

	 /*!
	 * @brief Take next step in the walk.
	 * @param current - The current position of the walk.
	 * @return The next position in the walk.
	 */
	 std::pair<int, int> nextStep(std::pair<int, int> current);

	 /*!
	 * @brief A random walk from a starting node until it links back up with the maze.
	 * @details The random walk will be performed until the path links back up with the maze or try's to go out of bounds.
	 * @param start - The starting position of the node to start the walk from.
	 * @return The path of the random walk.
	 */
	 std::vector<std::pair<int, int>> randomWalk(std::pair<int, int> start);

	 /*!
	 * @brief Generate maze
	 * @details The maze is a 2D graph of nodes that are either PATH or WALL.
	 * @param width - The width of the maze.
     * @param height - The height of the maze.
     */
	 void generateMaze(int width, int height);

	 /*!
	 * @brief Prints the maze to the console.
	 */
	 void printMaze();

	 /*!
	 * @brief Update the maze printed to the console.
	 * @param playerPosition - The position of the player.
	 */
	 void updateMaze(std::pair<int, int> playerPosition);

	 /*!
	 * @brief Choose a random start and end point of the maze.
	 * @return A pair of start and end points.
	 */
	 std::pair<std::pair<int, int>, std::pair<int, int>> chooseStartAndEnd();

	 /*!
	 * @brief Check if the player has reached the end of the maze.
	 * @return True if the player has reached the end, false otherwise.
	 */
	 bool checkWin() const;

	 /*!
	 * @brief Moving the player.
	 * @param direction - The direction the player wants to move in.
	 * @return True if the player can move in the given direction, false otherwise.
	 */
	 bool movePlayer(Direction direction);

	 /*!
	 * @brief Get player input.
	 * @return The direction the player wants to move in.
	 */
	 Direction getPlayerInput();

public :
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
	* @brief Runs the game logic/loop.
	* @details The game logic will handle player moves, check game conditions, and print the maze to the console.
	* @return either RETURN_TO_MENU or EXIT_GAME based on the user input.
	*/
	int run();
};
 
#endif // MAZE_H
