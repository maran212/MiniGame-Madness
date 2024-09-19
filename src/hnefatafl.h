#ifndef HNEFATAFL_H
#define HNEFATAFL_H

/*!
* @file Hnefatafl.h
* @brief Contains the declaration of the Hnefatafl class and its member methods.
* @author Angus Martin
*/

#include <string>
#include <map>
#include <vector>
#include <utility>
#include <conio.h>
#include "ScreenBuffer.h"
#include <time.h>
#include <stdlib.h>
#include <regex>

/*!
* @class Hnefatafl
* @brief A class that represents the game of Hnefatafl.
*
* @details This class provides methods to initialize the game board, handle player moves,
* @details check game conditions, and implement a basic bot for playing against the player.
*/
class Hnefatafl {
private:
    static const int BOARD_SIZE = 11; /*!< The size of the game board. */
    static const int WHITE = 1; /*!< The integer representation of a white piece. */
    static const int BLACK = 2; /*!< The integer representation of a black piece. */
    static const int KING = 3; /*!< The integer representation of the king piece. */
    static const int KING_SQUARE = 4; /*!< The integer representation of the king's square. */
    static const int EMPTY = 0; /*!< The integer representation of an empty square. */
    static const int OUT_OF_BOUNDS = -1; /*!< Constant to represent out of bounds. */

    int board[BOARD_SIZE][BOARD_SIZE]; /*!< The 2D array representing the game board. */
    int currentPlayer; /*!< The current player (WHITE or BLACK). */
	ScreenBuffer screenBuffer; /*!< The screen buffer for displaying the game. */

    /*!
    * @brief Populates the board with black pieces in their initial positions.
    */
    void populateBlackSquares();

    /*!
    * @brief Populates the board with white pieces in their initial positions.
    */
    void populateWhiteSquares();

public:
    /*!
    * @brief Initializes the game board.
    * @details The board is represented as a 2D array of integers:
    * @details 0: Empty square
    * @details 1: White piece
    * @details 2: Black piece
    * @details 3: King piece
    * @details 4: King's square 
    * @details The board is 11x11 with the center square initially occupied by the king.
    * @details The white pieces are placed in a star pattern around the king, with the black pieces in the middle of each side.
    * @details The king's squares are in the corners of the board and are the win condition for the king.
    */
    void populateBoard();

    /*!
    * @brief Gets the piece at a specific position on the board.
    * @param row The row index of the position.
    * @param col The column index of the position.
    * @return The piece at the specified position.
    */
    int getPiece(int row, int col);

    /*!
    * @brief Moves a piece from the source position to the target position.
    * @param source The source position as a pair of (row, col).
    * @param target The target position as a pair of (row, col).
    * @return A pair representing the result of the move.
    */
    std::pair<int, int> move(std::pair<int, int> source, std::pair<int, int> target);

    /*!
    * @brief Checks if a piece at the given position is captured.
    * @param position The position of the piece as a pair of (row, col).
    * @return true if the piece is captured, false otherwise.
    */
    bool isCaptured(std::pair<int, int> position);

    /*!
	* @breif Checks if neighbouring pieces of target piece are captured.
	* @param row The row index of the target piece.
	* @param col The column index of the target piece.
    */
	void handleNeighboursCaptured(int row, int col);
    
    /*!
    * @brief Checks if the king is captured.
    * @return true if the king is captured, false otherwise.
    */
    bool isKingCaptured();

    /*!
    * @brief Checks if the game is over.
    * @return true if the game is over (either by king capture or escape), false otherwise.
    */
    bool isGameOver();

    /*!
    * @brief Converts a string-based move to board coordinates.
    * @param move The move as a string.
    * @return A pair representing the move as (row, col).
    */
    std::pair<int, int> convertMove(const std::string& move);

    /*!
    * @brief A basic bot to play against the player.
    * @param player The player (WHITE or BLACK) for whom the bot will play.
    * @return A pair representing the bot's chosen move as (row, col).
    */
    std::pair<int, int> bot(int player);

    /*!
    * @brief Prints the current state of the game board.
    */
    void printBoard();

    /*!
    * @brief Check for vaild inputs
	* @param input The input from the user
	* @return true if the input is valid, false otherwise.
	*/
	bool isValidInput(const std::string& input);

    /*!
    * @brief Constructs a new Hnefatafl game object.
    */
    Hnefatafl();

	/*!
	* @brief Run the game
	* @return Whether should return to the main menu (0) or exit the program (1)
	*/
	int run();
};

#endif // HNEFATAFL_H

