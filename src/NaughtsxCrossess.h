// NaughtsxCrossess.h

#ifndef NAUGHTS_AND_CROSSESS_H
#define NAUGHTS_AND_CROSSESS_H

#include <iostream>
#include <limits>
#include <cstdlib>
#include <ctime>
#include <string>
#include <utility>

using namespace std;

const int BOARD_SIZE = 3;
extern char board[BOARD_SIZE][BOARD_SIZE];

// Function declarations
void printBoard();
void printBoardWithNumbers();
bool isMovesLeft();
int evaluate();
int minimax(int depth, bool isMax, int difficulty);
pair<int, int> findBestMove(int difficulty);
bool playerMove(char player);
void aiMove(int difficulty);
void testGame();
void clearScreen();
int NaughtsxCrossess();

#endif // NAUGHTS_AND_CROSSES_H