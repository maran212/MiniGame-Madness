#include <iostream>
#include <limits>
#include <cstdlib>
#include <ctime>
#include <string>
#include "NaughtsxCrossess.h"
#include "hangman.h"

using namespace std;

char board[BOARD_SIZE][BOARD_SIZE] = { {' ', ' ', ' '},
                           {' ', ' ', ' '},
                           {' ', ' ', ' '} };

/// Prints the current state of the board.
void printBoard() {
    cout << "-------------\n";
    for (int i = 0; i < BOARD_SIZE; ++i) {
        cout << "| ";
        for (int j = 0; j < BOARD_SIZE; ++j) {
            cout << board[i][j] << " | ";
        }
        cout << "\n-------------\n";
    }
}

/// Prints the board with numbers 1-9 to indicate cell positions.
void printBoardWithNumbers() {
    cout << "-------------\n";
    int cellNumber = 1;
    for (int i = 0; i < BOARD_SIZE; ++i) {
        cout << "| ";
        for (int j = 0; j < BOARD_SIZE; ++j) {
            cout << cellNumber << " | ";
            cellNumber++;
        }
        cout << "\n-------------\n";
    }
}

/// Checks if there are any moves left on the board.
bool isMovesLeft() {
    for (int i = 0; i < BOARD_SIZE; ++i)
        for (int j = 0; j < BOARD_SIZE; ++j)
            if (board[i][j] == ' ')
                return true;
    return false;
}

/// Evaluates the current board and returns a score:
/// +10 if 'X' wins, -10 if 'O' wins, 0 otherwise.
int evaluate() {
    // Check rows for victory
    for (int row = 0; row < BOARD_SIZE; ++row) {
        if (board[row][0] == board[row][1] && board[row][1] == board[row][2]) {
            if (board[row][0] == 'x')
                return +10;
            else if (board[row][0] == 'o')
                return -10;
        }
    }

    // Check columns for victory
    for (int col = 0; col < BOARD_SIZE; ++col) {
        if (board[0][col] == board[1][col] && board[1][col] == board[2][col]) {
            if (board[0][col] == 'x')
                return +10;
            else if (board[0][col] == 'o')
                return -10;
        }
    }

    // Check diagonals for victory
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
        if (board[0][0] == 'x')
            return +10;
        else if (board[0][0] == 'o')
            return -10;
    }

    if (board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
        if (board[0][2] == 'x')
            return +10;
        else if (board[0][2] == 'o')
            return -10;
    }

    // No winner
    return 0;
}

/// Minimax algorithm to calculate the best move for the AI.
/// `depth` limits how far ahead the AI will look (for Medium difficulty).
/// `isMax` indicates whether the AI is maximizing (true) or minimizing (false).
/// `difficulty` limits the depth for Medium difficulty.
int minimax(int depth, bool isMax, int difficulty) {
    int score = evaluate();

    // If AI or player has won the game, return the evaluated score
    if (score == 10 || score == -10)
        return score;

    // If no moves left, return a draw
    if (!isMovesLeft())
        return 0;

    // If depth limit is reached for Medium difficulty, stop recursion
    if (depth == difficulty)
        return 0;

    // If AI's turn (maximizing)
    if (isMax) {
        int best = std::numeric_limits<int>::min();

        for (int i = 0; i < BOARD_SIZE; ++i) {
            for (int j = 0; j < BOARD_SIZE; ++j) {
                if (board[i][j] == ' ') {
                    board[i][j] = 'x'; // Try the move
                    best = max(best, minimax(depth + 1, !isMax, difficulty));
                    board[i][j] = ' '; // Undo the move
                }
            }
        }
        return best;
    }
    // If player's turn (minimizing)
    else {
        int best = std::numeric_limits<int>::max();

        for (int i = 0; i < BOARD_SIZE; ++i) {
            for (int j = 0; j < BOARD_SIZE; ++j) {
                if (board[i][j] == ' ') {
                    board[i][j] = 'o'; // Try the move
                    best = min(best, minimax(depth + 1, !isMax, difficulty));
                    board[i][j] = ' '; // Undo the move
                }
            }
        }
        return best;
    }
}

/// Finds the best move for the AI based on the current board state.
/// The `difficulty` parameter influences how far ahead the AI looks.
pair<int, int> findBestMove(int difficulty) {
    int bestVal = std::numeric_limits<int>::min();
    pair<int, int> bestMove = { -1, -1 };

    // Evaluate all possible moves and choose the best one
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            if (board[i][j] == ' ') {
                board[i][j] = 'x'; // Try the move
                int moveVal = minimax(0, false, difficulty);
                board[i][j] = ' '; // Undo the move

                // If this move is better than the best move found so far, update bestMove
                if (moveVal > bestVal) {
                    bestMove = { i, j };
                    bestVal = moveVal;
                }
            }
        }
    }

    return bestMove;
}

/// Handles player input for a move. Returns false if the player typed "stop".
bool playerMove(char player) {
    string input;
    cout << "Enter your move (1-9) or type 'stop' to end the game: ";
    cin >> input;

    if (input == "stop") {
        return false;
    }

    int move = stoi(input);
    move--; // Adjust to 0-indexed

    int row = move / BOARD_SIZE;
    int col = move % BOARD_SIZE;

    // Check if the move is valid
    if (move >= 0 && move < BOARD_SIZE * BOARD_SIZE && board[row][col] == ' ') {
        board[row][col] = player;
    }
    else {
        cout << "Invalid move. Try again.\n";
        return playerMove(player); // Recursive call until a valid move is entered
    }

    return true;
}

/// Handles the AI's move based on the selected difficulty level.
void aiMove(int difficulty) {
    if (difficulty == 1) { // Easy difficulty: Random move
        srand(time(0));
        int row, col;
        do {
            row = rand() % BOARD_SIZE;
            col = rand() % BOARD_SIZE;
        } while (board[row][col] != ' ');
        board[row][col] = 'x';
    }
    else { // Medium and Hard difficulty: Minimax algorithm
        pair<int, int> bestMove = findBestMove(difficulty == 2 ? 2 : 100); // Medium: 2-depth, Hard: full depth
        board[bestMove.first][bestMove.second] = 'x';
    }
}

/// Runs a series of tests to validate the game logic and output results.
void testGame() {
    bool allTestsPassed = true;

    // Test 1: Initial evaluation of an empty board
    int result = evaluate();
    if (result != 0) {
        cout << "Test 1 Failed: Expected 0, got " << result << endl;
        allTestsPassed = false;
    }
    else {
        cout << "Test 1 Passed\n";
    }

    // Test 2: Simulate a winning board for 'X'
    board[0][0] = board[0][1] = board[0][2] = 'x';
    result = evaluate();
    if (result != 10) {
        cout << "Test 2 Failed: Expected 10, got " << result << endl;
        allTestsPassed = false;
    }
    else {
        cout << "Test 2 Passed\n";
    }

    // Reset board for next tests
    board[0][0] = board[0][1] = board[0][2] = ' ';

    // Test 3: Simulate a winning board for 'O'
    board[2][0] = board[2][1] = board[2][2] = 'o';
    result = evaluate();
    if (result != -10) {
        cout << "Test 3 Failed: Expected -10, got " << result << endl;
        allTestsPassed = false;
    }
    else {
        cout << "Test 3 Passed\n";
    }

    // Reset board for next tests
    board[2][0] = board[2][1] = board[2][2] = ' ';

    // Test 4: Check AI move in an easy scenario
    board[0][0] = 'x';
    board[0][1] = 'x';
    board[0][2] = ' ';
    board[1][0] = ' ';
    board[1][1] = ' ';
    board[1][2] = ' ';
    board[2][0] = ' ';
    board[2][1] = ' ';
    board[2][2] = ' ';
    pair<int, int> bestMove = findBestMove(3); // Hard difficulty
    if (bestMove != make_pair(0, 2)) {
        cout << "Test 4 Failed: Expected move (0,2), got (" << bestMove.first << "," << bestMove.second << ")\n";
        allTestsPassed = false;
    }
    else {
        cout << "Test 4 Passed\n";
    }

    // Reset board for next tests
    for (int i = 0; i < BOARD_SIZE; ++i)
        for (int j = 0; j < BOARD_SIZE; ++j)
            board[i][j] = ' ';

    // Test 5: Check if the board is correctly displayed
    printBoard();
    cout << "Please visually inspect the board. It should be empty.\n";

    // Report overall test results
    if (allTestsPassed) {
        cout << "All tests passed!\n";
    }
    else {
        cout << "Some tests failed. Please review the results.\n";
    }
}



/// Main function to run the game.
int NaughtsxCrossess() {
    // Run tests
    // testGame();

    // Proceed with the game if all tests pass
    string input;
    cout << "Select mode (1 = Easy, 2 = Medium, 3 = Hard, 4 = Player vs Player): ";
    cin >> input;

    if (input == "stop") {
        return 0; // Stop the program if "stop" is entered
    }

    int difficulty = stoi(input);

    if (difficulty < 1 || difficulty > 4) {
        cout << "Invalid mode selected. Exiting.\n";
        return 0;
    }

    cout << "Welcome to Noughts and Crosses!\n";
    cout << "Here's the board with numbered cells:\n";
    printBoardWithNumbers();

    bool isPvP = (difficulty == 4);

    // Main game loop
    while (isMovesLeft()) {
        clearScreen();  // Clear console before showing the board
        printBoardWithNumbers();
        printBoard();

        if (!playerMove(isPvP ? 'o' : 'o')) { // Player 1 move
            cout << "Game stopped by the player.\n";
            break;
        }

        clearScreen();
        printBoardWithNumbers();
        printBoard();

        if (evaluate() == -10) {
            cout << "Player O wins!\n";
            break;
        }

        if (!isMovesLeft()) {
            cout << "It's a draw!\n";
            break;
        }

        if (isPvP) {
            if (!playerMove('x')) { // Player 2 move
                cout << "Game stopped by the player.\n";
                break;
            }
        }
        else {
            cout << "AI is making a move...\n";
            aiMove(difficulty);
        }

        clearScreen();
        printBoardWithNumbers();
        printBoard();

        if (evaluate() == 10) {
            cout << (isPvP ? "Player X wins!\n" : "AI wins!\n");
            break;
        }

        if (!isMovesLeft()) {
            cout << "It's a draw!\n";
            break;
        }
    }

    return 0;
}