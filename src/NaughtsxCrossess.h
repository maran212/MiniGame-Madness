#ifndef NAUGHTS_AND_CROSSESS_H
#define NAUGHTS_AND_CROSSESS_H
#define NOMINMAX

#include <iostream>
#include <functional>
#include <limits>
#include <cstdlib>
#include <ctime>
#include <string>
#include <utility>
#include <algorithm>
#include "ScreenBuffer.h"

const int BOARD_SIZE = 3; ///< Updated constant name to avoid conflicts

/// @brief Class representing the Noughts and Crosses (Tic-Tac-Toe) game.
class NaughtsxCrossess {
private:
    char board[BOARD_SIZE][BOARD_SIZE]; ///< The game board.
    ScreenBuffer* screenBuffer;         ///< ScreenBuffer pointer for managing console output.
    bool ownsScreenBuffer;              ///< Track if the class owns the screen buffer.
    bool gameEnded;

public:
    /// @brief Constructor to initialize the game board.
    NaughtsxCrossess();

    /// @brief Copy Constructor
    NaughtsxCrossess(const NaughtsxCrossess& other);

    /// @brief Copy Assignment Operator
    NaughtsxCrossess& operator=(const NaughtsxCrossess& other);

    /// @brief Constructor that accepts an external ScreenBuffer.
    explicit NaughtsxCrossess(ScreenBuffer* buffer);

    /// @brief Destructor to clean up internal ScreenBuffer if we own it.
    ~NaughtsxCrossess();

    /// @brief Sets the ScreenBuffer to be used by the game.
    void setScreenBuffer(ScreenBuffer* buffer);

    /// @brief Prints the current state of the board.
    void printBoard() const;

    /// @brief Prints the board with numbers 1-9 to indicate cell positions.
    void printBoardWithNumbers() const;

    /// @brief Checks if there are any moves left on the board.
    /// @return True if there are moves left, false otherwise.
    bool isMovesLeft() const;

    /// @brief Evaluates the current board and returns a score.
    /// @return +10 if 'X' wins, -10 if 'O' wins, 0 otherwise.
    int evaluate() const;

    /// @brief Minimax algorithm to calculate the best move for the AI.
    /// @param depth The current depth of the recursion.
    /// @param isMax True if the AI is maximizing, false if minimizing.
    /// @param difficulty The depth limit for Medium difficulty.
    /// @return The evaluated score.
    int minimax(int depth, bool isMax, int difficulty);

    /// @brief Finds the best move for the AI based on the current board state.
    /// @param difficulty The difficulty level of the AI.
    /// @return The best move as a pair of integers representing row and column.
    std::pair<int, int> findBestMove(int difficulty);

    /// @brief Handles player input for a move with optional input simulation for testing.
    /// @param player The character representing the player ('x' or 'o').
    /// @param inputProvider A function or lambda that provides input for testing.
    /// @return False if the player typed "stop", true otherwise.
    bool playerMove(char player, std::function<std::string()> inputProvider = nullptr);

    /// @brief Handles the AI's move based on the selected difficulty level.
    /// @param difficulty The difficulty level of the AI.
    void aiMove(int difficulty);

    /// @brief Clears the console screen.
    void clearScreen() const;

    /// @brief Resets the game board, clearing all pieces and setting it to the initial state.
    /// This is called at the start of each new game.
    void resetBoard();

    /// @brief Get a reference to the value of the board at a specific position.
    /// @param row The row index of the board.
    /// @param col The column index of the board.
    /// @return A reference to the value at the specified position.
    char& getBoardValue(int row, int col);

    /// @brief Converts a move number (1-9) to board coordinates based on numpad layout.
    /// @param moveNumber The move number entered by the player.
    /// @return A pair of integers representing the row and column.
    std::pair<int, int> moveNumberToPosition(int moveNumber) const;

    /// @brief Runs and manages the game.
    void run(std::function<std::string()> inputProvider = nullptr);
};

#endif // NAUGHTS_AND_CROSSES_H
