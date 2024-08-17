#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <utility>
#include <string>

// Board dimensions
const int BOARD_SIZE = 11;

// Game board and player constants
extern int board[BOARD_SIZE][BOARD_SIZE];
const int WHITE = 1;
const int BLACK = 2;
const int KING = 3;
const int KING_SQUARE = 4;
extern int currentPlayer;

// Function declarations
void populateBoard();
void populateBlackSquares();
void populateWhiteSquares();
std::pair<int, int> move(std::pair<int, int> source, std::pair<int, int> target);
bool isCaptured(std::pair<int, int> source);
bool isKingCaptured();
bool isGameOver();

#endif // GAMEBOARD_H
