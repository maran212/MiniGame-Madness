#ifndef CHESS_H
#define CHESS_H

/*!
* @file chess.h
* @brief Contains the declaration of the Chess class and its member functions for chess game.
*/

#include "ScreenBuffer.h"
#include <string>
#include <map>
#include <stdexcept>
#include <memory>

/*!
 * @enum PieceType
 * @brief An enumeration of the different types of chess pieces.
*/
enum PieceType {
	EMPTY, /*!< An empty square. */
	PAWN, /*!< The pawn piece type. */
	ROOK, /*!< The rook piece type. */
	KNIGHT, /*!< The knight piece type. */
	BISHOP, /*!< The bishop piece type. */
	QUEEN, /*!< The queen piece type. */
	KING /*!< The king piece type. */
};

/*!
 * @enum PlayerColour
 * @brief An enumeration of the different player colors.
*/
enum PlayerColour {
	BLANK_PLAYER, /*!< A blank player color, for empty squares. */
	WHITE_PLAYER, /*!< The white player color. */
	BLACK_PLAYER, /*!< The black player color. */
	RED_PLAYER, /*!< The red player color. */
	GREEN_PLAYER, /*!< The green player color. */
	BLUE_PLAYER, /*!< The blue player color. */
	YELLOW_PLAYER /*!< The yellow player color. */
};

/*!
 * @enum SquareColour
 * @brief An enumeration of the different square colors.
*/
enum SquareColour {
	WHITE_SQUARE, /*!< A white square. */
	BLACK_SQUARE /*!< A black square. */
};

/*!
 * @enum Direction
 * @brief An enumeration of possible directions of neighboring squares.
 */
enum Direction {
	NORTH, /*!< Direction going to the top of the board. */
	SOUTH, /*!< Direction going to the bottom of the board */
	EAST, /*!< Direction going to the right of the board. */
	WEST, /*!< Direction going to the left of the board. */
	NORTHEAST, /*!< Direction going to the top right of the board. */
	NORTHWEST, /*!< Direction going to the top left of the board. */
	SOUTHEAST, /*!< Direction going to the bottom right of the board. */
	SOUTHWEST /*!< Direction going to the bottom left of the board. */
};

/*!
* @struct ChessSquare
* @brief A struct that represents a chess square.
* @details This struct contains the type of the piece and the color of the player that owns the piece as well as colour of the square.
* @details The default type is EMPTY and the default player color is BLANK reprasenting an emptry square.
*/
struct ChessSquare {
	PieceType type; /*!< The type of the piece. */
	PlayerColour playerColour; /*!< The color of the player that owns the piece. */
	SquareColour squareColour; /*!< The color of the square. */
	std::map<Direction, ChessSquare*> neighbors; /*!< A map of directions to neighboring squares. */

	/*!
	 * @brief Default constructor for ChessSquare.
	 * @details Initializes the ChessSquare with an EMPTY type, a BLANK player color.
	 * @param squareColour The Colour of the square.
	 */
	ChessSquare(SquareColour squareColour) : type(PieceType::EMPTY), playerColour(PlayerColour::BLANK_PLAYER), squareColour(squareColour){}
	
	/*!
	 * @brief Constructor for ChessSquare.
	 * @details Initializes the ChessSquare with the given type, player color, and square colour.
	 * @param type The type of the piece.
	 * @param playerColour The color of the player that owns the piece.
	 * @param squareColour The color of the square.
	 */
	ChessSquare(PieceType type, PlayerColour playerColour, SquareColour squareColour) : type(type), playerColour(playerColour), squareColour(squareColour) {}

	/*!
	* @brief Add a neighboring square with a direction.
	* @param square - The square to add as a neighbor.
	* @param direction - The direction of the neighboring square.
	*/
	void addNeighbor(ChessSquare* square, Direction direction) {
		if (neighbors.find(direction) != neighbors.end()) {
			throw std::runtime_error("Neighbor already exists in the given direction.");
		}

		neighbors[direction] = square;
	}

	/*!
	* @brief Remove a neighboring square with a direction.
	* @param direction - The direction of the neighboring square.
	*/
	bool removeNeighbor(Direction direction) {
		if (neighbors.find(direction) == neighbors.end()) {
			throw std::runtime_error("Neighbor not found in the given direction.");
		}

		neighbors.erase(direction);
	}

	/*!
	* @brief Get the neighboring square in a given direction.
	* @param direction - The direction of the neighboring square.
	* @return The neighboring square in the given direction.
	*/
	ChessSquare* getNeighbor(Direction direction) const {
		auto neighbor = neighbors.find(direction);
		return (neighbor != neighbors.end()) ? neighbor->second : nullptr;
	}

	/*!
	* @brief Get all neighboring squares.
	* @return A map of directions to neighboring squares.
	*/
	std::map<Direction, ChessSquare*> getNeighbors() const {
		return neighbors;
	}


	/*!
	* @brief Get the piece type of the square.
	* @return The piece type of the square.
	*/
	PieceType getPieceType() const {
		return type;
	}

	/*!
	* @brief Set the piece type of the square.
	* @param type - The piece type to set.
	* @return True if the piece type was set successfully, false otherwise.
	*/
	bool setPieceType(PieceType type) {
		this->type = type;
		return true;
	}

	/*!
	* @brief Get the player color of the square.
	* @return The player color of the square.
	*/
	PlayerColour getPlayerColour() const {
		return playerColour;
	}

	/*!
	* @brief Set the player color of the square.
	* @param playerColour - The player color to set.
	* @return True if the player color was set successfully, false otherwise.
	*/
	bool setPlayerColour(PlayerColour playerColour) {
		this->playerColour = playerColour;
		return true;
	}

	/*!
	* @brief Get the square colour of the square.
	* @return The square colour of the square.
	*/
	SquareColour getSquareColour() const {
		return squareColour;
	}
};


/*!
* @class Chess
* @brief A class that represents the game of Chess.
*/
class Chess{
 private:

	std::map<std::string, std::unique_ptr<ChessSquare>> boardMap; /*!< A map of string positions to ChessSquare pointers. */

	/*!
	* @brief Generate 2 player board.
	* @details The board is represented as a 2D graph of ChessSquare structs in a 8x8 square shape.
	*/
	 void generateBoard2Player();

 public:
	 /*!
	  * @brief Generate the game board.
	  * @details The board is represented as a 2D graph of ChessSquare structs.
	  * @details Each square contains the type of the piece, the color of the player that owns the piece, and the color of the square.
	  * @details The boards shape and size will change based on the number of players.
	  */
	 void generateBoard();
	 
};

#endif // !CHESS

