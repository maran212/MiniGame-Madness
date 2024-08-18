#include "hnefatafl.h"
#include <iostream>

/**
* Constructor for the HnefataflGame class
*/
HnefataflGame::HnefataflGame(){
    populateBoard();
	currentPlayer = BLACK;
};

/**
* Initializes the game board
* The board is represented as a 2D array of integers:
* 0: Empty square
* 1: White piece
* 2: Black piece
* 3: King piece
* 4: King's square 
* The board is 11x11 with the center square initially occupied by the king.
* The white pieces are placed in a star pattern around the king, with the black pieces in the middle of each side.
* The king's squares are in the corners of the board and are the win condition for the king.
*/
void HnefataflGame::populateBoard() {
    // Initialize the board to empty
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            board[i][j] = 0;
        }
    }

    // Populate black and white squares
    populateBlackSquares();
    populateWhiteSquares();

    // Set the king's position
    board[5][5] = KING;

    // Set the king's squares
    board[0][0] = KING_SQUARE;
    board[10][10] = KING_SQUARE;
    board[0][10] = KING_SQUARE;
    board[10][0] = KING_SQUARE;
};

/**
* Helper function to populate the black squares on the board
*/
void HnefataflGame::populateBlackSquares() {
    for (int col = 3; col < 8; ++col) {
        board[0][col] = BLACK;
        board[10][col] = BLACK;
    }
    for (int row = 3; row < 8; ++row) {
        board[row][0] = BLACK;
        board[row][10] = BLACK;
    }

    board[1][5] = BLACK;
    board[9][5] = BLACK;
    board[5][1] = BLACK;
    board[5][9] = BLACK;
};

/**
* Helper function to populate the white squares on the board
*/
void HnefataflGame::populateWhiteSquares() {
    for (int col = 4; col < 7; ++col) {
        board[4][col] = WHITE;
        board[5][col] = WHITE;
        board[6][col] = WHITE;
    }

    board[3][5] = WHITE;
    board[7][5] = WHITE;
    board[5][3] = WHITE;
    board[5][7] = WHITE;
};

/**
* Moves a piece from the source to the target position
* @param std::pair<int, int> source The source position of the piece
* @param std::pair<int, int> target The target position of the piece
* @return std::pair<int, int> The final position of the piece after the move
*/
std::pair<int, int> HnefataflGame::move(std::pair<int, int> source, std::pair<int, int> target) {
    int sourceRow = source.first;
    int sourceCol = source.second;
    int targetRow = target.first;
    int targetCol = target.second;

    currentPlayer = board[sourceRow][sourceCol];
    int currentRow = sourceRow;
    int currentCol = sourceCol;

    // Moving logic (up, down, left, right)
    if (currentRow > targetRow && currentCol == targetCol) {
        while (currentRow > targetRow && board[currentRow - 1][currentCol] == 0) {
            currentRow--;
        }
    }
    else if (currentRow < targetRow && currentCol == targetCol) {
        while (currentRow < targetRow && board[currentRow + 1][currentCol] == 0) {
            currentRow++;
        }
    }
    else if (currentCol > targetCol && currentRow == targetRow) {
        while (currentCol > targetCol && board[currentRow][currentCol - 1] == 0) {
            currentCol--;
        }
    }
    else if (currentCol < targetCol && currentRow == targetRow) {
        while (currentCol < targetCol && board[currentRow][currentCol + 1] == 0) {
            currentCol++;
        }
    }

    board[currentRow][currentCol] = currentPlayer;

    return std::make_pair(currentRow, currentCol);
};

/**
* Checks if a piece at the given position is captured (surrounded on opposite sides by opponent pieces or King's squares in the corner)
* @param std::pair<int, int> source The position of the piece to check
* @return bool True if the piece is captured, false otherwise
*/
bool HnefataflGame::isCaptured(std::pair<int, int> source) {
    int sourceRow = source.first;
    int sourceCol = source.second;

    currentPlayer = board[sourceRow][sourceCol];
    int opponentPlayer = (currentPlayer == WHITE) ? BLACK : WHITE;

    int up = (sourceRow > 0) ? board[sourceRow - 1][sourceCol] : -1;
    int down = (sourceRow < BOARD_SIZE - 1) ? board[sourceRow + 1][sourceCol] : -1;
    int left = (sourceCol > 0) ? board[sourceRow][sourceCol - 1] : -1;
    int right = (sourceCol < BOARD_SIZE - 1) ? board[sourceRow][sourceCol + 1] : -1;

    return ((up == opponentPlayer || up == KING_SQUARE) && (down == opponentPlayer || down == KING_SQUARE)) ||
        ((left == opponentPlayer || left == KING_SQUARE) && (right == opponentPlayer || right == KING_SQUARE));
};

/**
* Checks if the king is captured (surrounded on four sides by black pieces)
* @return bool True if the king is captured, false otherwise
*/
bool HnefataflGame::isKingCaptured() {
    int kingRow = -1, kingCol = -1;

    for (int row = 0; row < BOARD_SIZE; ++row) {
        for (int col = 0; col < BOARD_SIZE; ++col) {
            if (board[row][col] == KING) {
                kingRow = row;
                kingCol = col;
                break;
            }
        }
    }

    int up = (kingRow > 0) ? board[kingRow - 1][kingCol] : -1;
    int down = (kingRow < BOARD_SIZE - 1) ? board[kingRow + 1][kingCol] : -1;
    int left = (kingCol > 0) ? board[kingRow][kingCol - 1] : -1;
    int right = (kingCol < BOARD_SIZE - 1) ? board[kingRow][kingCol + 1] : -1;

    return up == BLACK && down == BLACK && left == BLACK && right == BLACK;
};

/**
* Checks if the game is over (either by king capture or escape)
* @return bool True if the game is over, false otherwise
*/
bool HnefataflGame::isGameOver() {
    if (isKingCaptured()) return true;

    for (int row = 0; row < BOARD_SIZE; ++row) {
        for (int col = 0; col < BOARD_SIZE; ++col) {
            if (board[row][col] == KING && (row == 0 || row == 10) && (col == 0 || col == 10)) {
                return true;
            }
        }
    }

    return false;
};

/**
* Converts a string-based move to board coordinates
* @param std::string move The move in the format 'A1'
* @return std::pair<int, int> The row and column of the move
*/
std::pair<int, int> HnefataflGame::getMove(std::string move) {
    std::string rows = "ABCDEFGHIJK";
    int row = rows.find(move[0]);
    int col = move[1] - '1';

    return std::make_pair(row, col);
};

/**
* Prints the current state of the game board
*/
void HnefataflGame::printBoard() {
    std::string rows = "ABCDEFGHIJK";
    std::cout << "    1   2   3   4   5   6   7   8   9  10  11" << std::endl;
    std::cout << "  +---+---+---+---+---+---+---+---+---+---+---+" << std::endl;

    for (int row = 0; row < BOARD_SIZE; ++row) {
        std::cout << rows[row] << " |";
        for (int col = 0; col < BOARD_SIZE; ++col) {
            if (board[row][col] == 0)
                std::cout << "   |";
            else if (board[row][col] == WHITE)
                std::cout << " W |";
            else if (board[row][col] == BLACK)
                std::cout << " B |";
            else if (board[row][col] == KING)
                std::cout << " K |";
            else if (board[row][col] == KING_SQUARE)
                std::cout << " X |";
        }
        std::cout << std::endl;
        std::cout << "  +---+---+---+---+---+---+---+---+---+---+---+" << std::endl;
    }
};

/**
* The main game loop
*/
void HnefataflGame::play() {
    std::string input;
    std::pair<int, int> source, target;

    printBoard();

    while (!isGameOver()) {
        bool validInput = false;

        while (!validInput) {
            std::cout << "Enter your move (e.g., A1 B2): ";
            std::getline(std::cin, input);

            if (input.length() == 5 && input[2] == ' ' &&
                input[0] >= 'A' && input[0] <= 'K' &&
                input[3] >= 'A' && input[3] <= 'K' &&
                input[1] >= '1' && input[1] <= '9' &&
                input[4] >= '1' && input[4] <= '9') {

                source = getMove(input.substr(0, 2));
                target = getMove(input.substr(3, 2));

                // Validate the move
                if (board[source.first][source.second] != 0 &&
                    board[target.first][target.second] == 0 &&
                    (source.first == target.first || source.second == target.second)) {

                    validInput = true;
                }
                else {
                    std::cout << "Invalid move. Please try again." << std::endl;
                }
            }
            else {
                std::cout << "Invalid input format. Please use the format 'A1 B2'." << std::endl;
            }
        }

        // Perform the move
        std::pair<int, int> finalPosition = move(source, target);

        // Check if a piece was captured
        if (isCaptured(finalPosition)) {
            std::cout << "Piece captured!" << std::endl;
            board[source.first][source.second] = 0; // Remove captured piece
        }
        else {
            // Clear the source square after a valid move
            board[source.first][source.second] = 0;
        }

        // Check if the game is over after the move
        if (isGameOver()) {
            std::cout << "Game Over!" << std::endl;
            if (isKingCaptured()) {
                std::cout << "The king has been captured. Black wins!" << std::endl;
            }
            else {
                std::cout << "The king has escaped. White wins!" << std::endl;
            }
            break;
        }

        // Switch players
        currentPlayer = (currentPlayer == WHITE) ? BLACK : WHITE;

        // Print the updated board
        printBoard();
    }
};



