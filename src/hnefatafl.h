#ifndef HNEFATAFL_H
#define HNEFATAFL_H

#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <map>

class HnefataflGame {
private:
	// Constants for the game
    static const int BOARD_SIZE = 11;
    static const int WHITE = 1;
    static const int BLACK = 2;
    static const int KING = 3;
    static const int KING_SQUARE = 4;

    int board[BOARD_SIZE][BOARD_SIZE];
    int currentPlayer;

    // Helper functions to populate specific squares on the board
    void populateBlackSquares();
    void populateWhiteSquares();

public:
	// Constructor
    HnefataflGame();

    // Initializes the game board
    void populateBoard();

    // Moves a piece from the source to the target position
    std::pair<int, int> move(std::pair<int, int> source, std::pair<int, int> target);

    // Checks if a piece at the given position is captured
    bool isCaptured(std::pair<int, int> position);

    // Checks if the king is captured
    bool isKingCaptured();

    // Checks if the game is over (either by king capture or escape)
    bool isGameOver();

    // Converts a string-based move to board coordinates
    std::pair<int, int> getMove(const std::string move);

	// Bot to play against the player
    std::pair<int, int> bot(int player);

    // Prints the current state of the game board
    void printBoard();

    // The main game loop
    void play();
};

#endif // HNEFATAFL_H

