#ifndef MAZE_H
#define MAZE_H

/*!
 * @file maze.h
 * @brief Contains the declaration of the Maze class and its member methods.
 * @author Angus Martin
 */

#include "screenBuffer.h"
#include <map>
#include <memory>

/*!
* @enum NodeType
* @brief An enumeration of the different types of nodes in the maze
*/
enum NodeType {
	NONE, /*!< Node without a type */
	Path, /*!< Path in the maze */
	Wall, /*!< Wall in the maze */
};

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
* @brief A struct that reprsents the nodes in the graph of the maze.
* @details The default type is None reprasenting a node that hasn't been assigned a type yet.
*/
struct MazeNode {
	NodeType type; /*!< The type of the node*/
	std::map<Direction, MazeNode*> neighbors; /*!< A map of directions to neighboring nodes. */

	/*!
	* @brief Default constructor for MazeNode
	* @details Initialize the MazeNode the type NONE
	*/
	MazeNode() : type(NodeType::NONE){}

	/*!
	* @brief Add a neighboring nodes with a direction.
	* @param node - The node to add as a neighbor.
	* @param direction - The direction of the neighboring node.
	*/
	void addNeighbor(MazeNode* node, Direction direction) {
		if (neighbors.find(direction) != neighbors.end()) {
			throw std::runtime_error("Neighbor already exists in the given direction.");
		}

		neighbors[direction] = node;
	}

	/*!
	* @brief Remove a neighboring node with a direction.
	* @param direction - The direction of the neighboring node.
	*/
	bool removeNeighbor(Direction direction) {
		if (neighbors.find(direction) == neighbors.end()) {
			throw std::runtime_error("Neighbor not found in the given direction.");
		}

		neighbors.erase(direction);
	}

	/*!
	* @brief Get the neighboring node in a given direction.
	* @param direction - The direction of the neighboring node.
	* @return The neighboring node in the given direction.
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


	/*!
	* @brief Get the piece type of the node.
	* @return The piece type of the node.
	*/
	NodeType getNodeType() const {
		return type;
	}

	/*!
	* @brief Set the piece type of the node.
	* @param type - The piece type to set.
	* @return True if the piece type was set successfully, false otherwise.
	*/
	bool setNodeType(NodeType type) {
		this->type = type;
		return true;
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
	 int WIDTH; /*!< Width of maze.*/
	 int HEIGHT; /*!< Height of maze.*/
	 std::map<std::pair<int, int>, MazeNode*> mazeMape;

	/*!
	* @brief Generate maze
	* @details The maze is a 2D graph of nodes that are either PATH or WALL.
	* @param width - The width of the maze.
	* @param height - The height of the maze.
	*/
	 void generateMaze(int width, int height);

public :
	
	/*!
	* Default constructor for maze class.
	* @details Generates a 21 by 21 node maze.
	*/
	Maze();

	/*!
	* Constructor for Maze class.
	* @param width - The width of the maze.
	* @param height - The height of the maze.
	*/
	Maze(int width, int height);
	 

};
 

#endif // MAZE_H
