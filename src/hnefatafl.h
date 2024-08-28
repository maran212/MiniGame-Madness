#ifndef HNEFATAFL_H
#define HNEFATAFL_H

/*!
 * @file HnefataflGame.h
 * @brief Contains the declaration of the HnefataflGame class and its member functions.
 */

#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <map>

/*!
 * @class HnefataflGame
 * @brief A class that represents the game of Hnefatafl.
 *
 * This class provides methods to initialize the game board, handle player moves,
 * check game conditions, and implement a basic bot for playing against the player.
 */
class HnefataflGame {
private:
    // Constants for the game
    static const int BOARD_SIZE = 11; /*!< The size of the game board. */
    static const int WHITE = 1;       /*!< The integer representation of a white piece. */
    static const int BLACK = 2;       /*!< The integer representation of a black piece. */
    static const int KING = 3;        /*!< The integer representation of the king piece. */
    static const int KING_SQUARE = 4; /*!< The integer representation of the king's square. */

    int board[BOARD_SIZE][BOARD_SIZE]; /*!< The 2D array representing the game board. */
    int currentPlayer;                 /*!< The current player (WHITE or BLACK). */

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
     * @brief Constructs a new HnefataflGame object.
     */
    HnefataflGame();

    /*!
     * @brief Initializes the game board.
     * 
     * @detail The board is represented as a 2D array of integers:
     * @detail 0: Empty square
     * @detail 1: White piece
     * @detail 2: Black piece
     * @detail 3: King piece
     * @detail 4: King's square 
     * @detail The board is 11x11 with the center square initially occupied by the king.
     * @detail The white pieces are placed in a star pattern around the king, with the black pieces in the middle of each side.
     * @detailThe king's squares are in the corners of the board and are the win condition for the king.
     */
    void populateBoard();

    /*!
     * @brief Gets the piece at a specific position on the board.
     *
     * @param row The row index of the position.
     * @param col The column index of the position.
     * @return The piece at the specified position.
     */
    int getPiece(int row, int col);

    /*!
     * @brief Moves a piece from the source position to the target position.
     *
     * @param source The source position as a pair of (row, col).
     * @param target The target position as a pair of (row, col).
     * @return A pair representing the result of the move.
     */
    std::pair<int, int> move(std::pair<int, int> source, std::pair<int, int> target);

    /*!
     * @brief Checks if a piece at the given position is captured.
     *
     * @param position The position of the piece as a pair of (row, col).
     * @return true if the piece is captured, false otherwise.
     */
    bool isCaptured(std::pair<int, int> position);

    /*!
     * @brief Checks if the king is captured.
     *
     * @return true if the king is captured, false otherwise.
     */
    bool isKingCaptured();

    /*!
     * @brief Checks if the game is over.
     *
     * @return true if the game is over (either by king capture or escape), false otherwise.
     */
    bool isGameOver();

    /*!
     * @brief Converts a string-based move to board coordinates.
     *
     * @param move The move as a string.
     * @return A pair representing the move as (row, col).
     */
    std::pair<int, int> getMove(const std::string move);

    /*!
     * @brief A basic bot to play against the player.
     *
     * @param player The player (WHITE or BLACK) for whom the bot will play.
     * @return A pair representing the bot's chosen move as (row, col).
     */
    std::pair<int, int> bot(int player);

    /*!
     * @brief Prints the current state of the game board.
     */
    void printBoard();

    /*!
     * @brief The main game loop.
     */
    void play();

    /*!
     * @class HnefataflGameTest
     * @brief A friend class for unit testing HnefataflGame.
     */
    friend class HnefataflGameTest;
};

#endif // HNEFATAFL_H

