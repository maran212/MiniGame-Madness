#include "hnefatafl.h"


// Constructor for the Hnefatafl class
Hnefatafl::Hnefatafl(){
    populateBoard();
	currentPlayer = BLACK;
};


// Initializes the game board
void Hnefatafl::populateBoard() {
    // Initialize the board to empty
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            board[i][j] = EMPTY;
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


// Helper function to populate the black squares on the board
void Hnefatafl::populateBlackSquares() {
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


// Helper function to populate the white squares on the board
void Hnefatafl::populateWhiteSquares() {
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


// Get the piece at the given position
int Hnefatafl::getPiece(int row, int col) {
	if (row < 0 || row >= BOARD_SIZE || col < 0 || col >= BOARD_SIZE) {
		return -1;
	}

	return board[row][col];
};


// Moves a piece from the source to the target position
std::pair<int, int> Hnefatafl::move(std::pair<int, int> source, std::pair<int, int> target) {
    int sourceRow = source.first;
    int sourceCol = source.second;
    int targetRow = target.first;
    int targetCol = target.second;

    currentPlayer = board[sourceRow][sourceCol];
    int currentRow = sourceRow;
    int currentCol = sourceCol;

    // Moving logic (up, down, left, right)
    if (currentRow > targetRow && currentCol == targetCol) {
        while (currentRow > targetRow && board[currentRow - 1][currentCol] == EMPTY) {
            currentRow--;
        }
    }
    else if (currentRow < targetRow && currentCol == targetCol) {
        while (currentRow < targetRow && board[currentRow + 1][currentCol] == EMPTY) {
            currentRow++;
        }
    }
    else if (currentCol > targetCol && currentRow == targetRow) {
        while (currentCol > targetCol && board[currentRow][currentCol - 1] == EMPTY) {
            currentCol--;
        }
    }
    else if (currentCol < targetCol && currentRow == targetRow) {
        while (currentCol < targetCol && board[currentRow][currentCol + 1] == EMPTY) {
            currentCol++;
        }
    }

	// If the piece is moved, update the board
    board[currentRow][currentCol] = currentPlayer;
    board[sourceRow][sourceCol] = EMPTY;

	if (board[currentRow][currentCol] == KING && board[targetRow][targetCol] == KING_SQUARE) {
		board[targetRow][targetCol] = KING;
        board[currentRow][currentCol] = EMPTY;
	}
	
    return std::make_pair(currentRow, currentCol);
};


// Checks if a piece at the given position is captured (surrounded on opposite sides by opponent pieces or King's squares in the corner)
bool Hnefatafl::isCaptured(std::pair<int, int> source) {
    
    // Get the piece at the current source position
    int sourceRow = source.first;
    int sourceCol = source.second;
    int piece = getPiece(sourceRow, sourceCol);

    // Get the opponent's player identifier
    int opponentPlayer = (piece == WHITE) ? BLACK : WHITE;

    // Check for out-of-bounds before accessing surrounding positions
    int up = getPiece(sourceRow - 1, sourceCol);
    int down = getPiece(sourceRow + 1, sourceCol);
    int left = getPiece(sourceRow, sourceCol - 1);
    int right = getPiece(sourceRow, sourceCol + 1);

    // Check if the piece is surrounded on opposite sides by the opponent or king's squares
    bool horizontalCapture = (left == opponentPlayer || left == KING_SQUARE) &&
        (right == opponentPlayer || right == KING_SQUARE);
    bool verticalCapture = (up == opponentPlayer || up == KING_SQUARE) &&
        (down == opponentPlayer || down == KING_SQUARE);

    return horizontalCapture || verticalCapture;
};


// Helper function to handle the capture of neighboring pieces
void Hnefatafl::handleNeighboursCaptured(int row, int col) {

    std::pair<int, int> neighbores[] = {
        {row - 1, col},  // up
        {row + 1, col},  // down
        {row, col - 1},  // left
        {row, col + 1}   // right
    };

	// Loop through the four neighboring positions
    for (const auto& pos : neighbores) {
        int newRow = pos.first;
        int newCol = pos.second;

        // Boundary check to ensure the position is within the board limits (0 to 10)
        if (newRow > -1 && newRow < BOARD_SIZE && newCol > -1 && newCol < BOARD_SIZE) {
            // Check if the neighboring piece is captured
            if (isCaptured(pos)) {
                board[newRow][newCol] = EMPTY;  
            }
        }
    }
};


// Checks if the king is captured (surrounded on four sides by black pieces)
bool Hnefatafl::isKingCaptured() {
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

	int up = getPiece(kingRow - 1, kingCol);
	int down = getPiece(kingRow + 1, kingCol);
	int left = getPiece(kingRow, kingCol - 1);
    int right = getPiece(kingRow, kingCol + 1);

    return (up == BLACK || up == OUT_OF_BOUNDS) && (down == BLACK || down == OUT_OF_BOUNDS) && (left == BLACK || left == OUT_OF_BOUNDS ) && (right == BLACK || right == OUT_OF_BOUNDS);
};


// Checks if the game is over (either by king capture or escape)
bool Hnefatafl::isGameOver() {
    if (isKingCaptured()) return true;

    if (board[0][0] == KING || board[0][10] == KING || board[10][0] == KING || board[10][10] == KING)
    {
        return true;
    }

    return false;
};


// Converts a string-based move to board coordinates
std::pair<int, int> Hnefatafl::covertMove(std::string move) {
    std::string rows = "ABCDEFGHIJK";
    int row = move[1] - '1';
    int col = static_cast<int>(rows.find(move[0]));

    return std::make_pair(row, col);
};


// Bot to play against the player (randomly selects a piece and a move)
std::pair<int, int> Hnefatafl::bot(int player) {
    srand(time(0));
	// Find if bot is white or black
	int botPlayer = (player == WHITE) ? BLACK : WHITE;

    // All bots pieces on the board
    std::map<std::pair<int, int>, std::vector<std::pair<int, int>>> botPiecesMap;

	// Find all the bot's pieces on the board and possible moves
    for (int row = 0; row < BOARD_SIZE; row++) {
        for (int col = 0; col < BOARD_SIZE; col++) {

			// Check if the piece is a bot piece or if the bot is white, the king
            if (board[row][col] == botPlayer || (botPlayer == WHITE && board[row][col] == KING)) {
                std::pair<int, int> position = std::make_pair(row, col);
                std::vector<std::pair<int, int>> possibleMoves;

				// Check possible moves up
				for (int i = row - 1; i >= 0; i--) {
					if (board[i][col] == EMPTY) {
						possibleMoves.push_back(std::make_pair(i, col));
					}
					else {
						break;
					}
				}
                
				// Check possible moves down
				for (int i = row + 1; i < BOARD_SIZE; i++) {
					if (board[i][col] == EMPTY) {
						possibleMoves.push_back(std::make_pair(i, col));
					}
					else {
						break;
					}
				}

				// Check possible moves left
				for (int j = col - 1; j >= 0; j--) {
					if (board[row][j] == EMPTY) {
						possibleMoves.push_back(std::make_pair(row, j));
					}
					else {
						break;
					}
				}

				// Check possible moves right
				for (int j = col + 1; j < BOARD_SIZE; j++) {
					if (board[row][j] == EMPTY) {
						possibleMoves.push_back(std::make_pair(row, j));
					}
					else {
						break;
					}
				}

				botPiecesMap[position] = possibleMoves;
            }
        }
    }
	

	// Randomly select a piece to move
	std::map<std::pair<int, int>, std::vector<std::pair<int, int>>>::iterator it = botPiecesMap.begin();
	std::advance(it, rand() % botPiecesMap.size());
	std::pair<int, int> source = it->first;

	// Randomly select a move for the piece
	std::vector<std::pair<int, int>> possibleMoves = it->second;
	std::pair<int, int> target = possibleMoves[rand() % possibleMoves.size()];

	// Perform the move
	std::pair<int, int> finalPosition = move(source, target);

    // Clear the source square after a valid move
    board[source.first][source.second] = EMPTY;

	// Print the bot's move
	std::string rows = "ABCDEFGHIJK";
	std::cout << "Bot moved from " << rows[source.first] << source.second + 1 << " to " << rows[finalPosition.first] << finalPosition.second + 1 << std::endl;

	return finalPosition;
};


// Prints the current state of the game board
void Hnefatafl::printBoard() {
    std::wstring rowLabels[BOARD_SIZE] = {L" 1", L" 2", L" 3", L" 4", L" 5", L" 6", L" 7", L" 8", L" 9", L"10", L"11"};

    screenBuffer.clearScreen();

    // Print column numbers at the top
    screenBuffer.writeToScreen(4, 0, L"    A   B   C   D   E   F   G   H   I   J   K ");

    // Loop through each row and print horizontal lines and pieces
    for (int row = 0; row < BOARD_SIZE; ++row) {
        // Print horizontal line
        screenBuffer.writeToScreen(4, row * 2 + 1, L"  +---+---+---+---+---+---+---+---+---+---+---+");

        // Print row label and the actual pieces
        std::wstring rowText = rowLabels[row] + L" |";
        for (int col = 0; col < BOARD_SIZE; ++col) {
            if (board[row][col] == 0)
                rowText += L"   |";
            else if (board[row][col] == WHITE)
                rowText += L" W |";
            else if (board[row][col] == BLACK)
                rowText += L" B |";
            else if (board[row][col] == KING)
                rowText += L" K |";
            else if (board[row][col] == KING_SQUARE)
                rowText += L" X |";
        }

        // Print the row content
        screenBuffer.writeToScreen(3, row * 2 + 2, rowText);
    }

    // Print the final horizontal line at the bottom
    screenBuffer.writeToScreen(4, BOARD_SIZE * 2 + 1, L"  +---+---+---+---+---+---+---+---+---+---+---+");
};

// Checks for vaild input from the user
bool Hnefatafl::isValidInput(const std::string& input) {
	if (input.length() == 5 && input[2] == ' ' &&
		input[0] >= 'A' && input[0] <= 'K' &&
		input[3] >= 'A' && input[3] <= 'K' &&
		input[1] >= '1' && input[1] <= '9' &&
		input[4] >= '1' && input[4] <= '9') {
		return true;
	}
	else {
		return false;
	}
}


// The game loop
int  Hnefatafl::run() {
	int player;
    std::string input;
    std::pair<int, int> source, target, finalPosition;


	// Print the initial board
	screenBuffer.setActive();
    printBoard();

	// choose starting player
	screenBuffer.writeToScreen(4, 24, L"Choose starting player (W/B) :");

	while (true) {
		input = screenBuffer.getBlockingInput();
		if (input == "W" || input == "w") {
			player = WHITE;
			break;
		}
		else if (input == "B" || input == "b") {
			player = BLACK;
			break;
		}
		else {
			screenBuffer.writeToScreen(4, 24, L"Invalid input. Please choose either 'W' or 'B':");
		}
	}
        
	// Main game loop
    while (!isGameOver()) {
        bool validInput = false;

        if (currentPlayer == player)
        { 
            screenBuffer.writeToScreen(4, 24, L"Enter your move (e.g., A1 B2): ");
            while (!validInput) {
				input = screenBuffer.getBlockingInput();

                if (isValidInput(input)) {
                    source = covertMove(input.substr(0, 2));
                    target = covertMove(input.substr(3, 2));

                    validInput = true;
                }
                else {
                    screenBuffer.writeToScreen(4, 24, L"Invalid input. Please enter your move in the format 'A1 B2':");
                }
            }

			// Perform the move
            finalPosition = move(source, target);
		}
		else {
			// Bot's turn
			std::cout << "Bot's turn..." << std::endl;
            finalPosition = bot(player);
		}

		// Handle the capture of neighboring pieces
		handleNeighboursCaptured(finalPosition.first, finalPosition.second);

        // Switch players
        currentPlayer = (currentPlayer == WHITE) ? BLACK : WHITE;

        // Print the updated board
        printBoard();
    }

	// Print the game result
	if (isKingCaptured()) {
        screenBuffer.writeToScreen(4, 30, L"The king has been captured. Black wins!");
	}
	else {
        screenBuffer.writeToScreen(4, 30, L"The king has escaped. White wins!");
	}

	// Return to the main menu or exit the game
	screenBuffer.writeToScreen(4, 31, L"Press 'r' to return to the main menu or 'q' to exit the game.");

	while (true) {
		char key = _getch();
		if (key == 'r') {
			return 0;
		}
		else if (key == 'q') {
			return 1;
		}
		else {
			screenBuffer.writeToScreen(4, 31, L"Invalid input. Press 'r' to return to the main menu or 'q' to exit the game.");
		}
	}
};



