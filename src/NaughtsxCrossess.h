#ifndef NAUGHTS_AND_CROSSESS_H
#define NAUGHTS_AND_CROSSESS_H

#include <iostream>
#include <limits>
#include <cstdlib>
#include <ctime>
#include <string>
#include <utility>

const int BOARD_SIZE = 3; ///< Updated constant name to avoid conflicts

/// @brief Class representing the Noughts and Crosses (Tic-Tac-Toe) game.
class NaughtsxCrossess {
public:
    /// @brief Constructor to initialize the game board.
    NaughtsxCrossess();

    /// @brief Prints the current state of the board.
    void printBoard() const;
    
    /// @brief runs and manages the game.
    void run();

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

    /// @brief Handles player input for a move.
    /// @param player The character representing the player ('x' or 'o').
    /// @return False if the player typed "stop", true otherwise.
    bool playerMove(char player);

    /// @brief Handles the AI's move based on the selected difficulty level.
    /// @param difficulty The difficulty level of the AI.
    void aiMove(int difficulty);

    /// @brief Clears the console screen.
    void clearScreen() const;

private:
    char board[BOARD_SIZE][BOARD_SIZE]; ///< The game board.
};

#endif // NAUGHTS_AND_CROSSES_H
