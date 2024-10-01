#include "NaughtsxCrossess.h"


// Copy Constructor
NaughtsxCrossess::NaughtsxCrossess(const NaughtsxCrossess& other) {
    if (other.screenBuffer) {
        // Deep copy the ScreenBuffer
        screenBuffer = new ScreenBuffer(*other.screenBuffer);
        ownsScreenBuffer = true;  // Since we allocated a new ScreenBuffer
    }
    else {
        screenBuffer = nullptr;
        ownsScreenBuffer = false;
    }

    // Copy the board
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            board[i][j] = other.board[i][j];
        }
    }
}


// Copy Assignment Operator
NaughtsxCrossess& NaughtsxCrossess::operator=(const NaughtsxCrossess& other) {
    if (this != &other) {  // Protect against self-assignment
        // Clean up existing resources
        if (ownsScreenBuffer && screenBuffer) {
            delete screenBuffer;
            screenBuffer = nullptr;
        }

        if (other.screenBuffer) {
            // Deep copy the ScreenBuffer
            screenBuffer = new ScreenBuffer(*other.screenBuffer);
            ownsScreenBuffer = true;
        }
        else {
            screenBuffer = nullptr;
            ownsScreenBuffer = false;
        }

        // Copy the board
        for (int i = 0; i < BOARD_SIZE; ++i) {
            for (int j = 0; j < BOARD_SIZE; ++j) {
                board[i][j] = other.board[i][j];
            }
        }
    }
    return *this;
}


// Default constructor, initializes its own ScreenBuffer
NaughtsxCrossess::NaughtsxCrossess() : screenBuffer(nullptr), ownsScreenBuffer(true) {
    screenBuffer = new ScreenBuffer();
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            board[i][j] = ' ';
        }
    }
}

// Constructor that accepts an external ScreenBuffer
NaughtsxCrossess::NaughtsxCrossess(ScreenBuffer* buffer) : screenBuffer(buffer), ownsScreenBuffer(false) {
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            board[i][j] = ' ';
        }
    }
}

// Destructor to clean up internal ScreenBuffer if we own it
NaughtsxCrossess::~NaughtsxCrossess() {
    if (ownsScreenBuffer && screenBuffer) {
        delete screenBuffer;
        screenBuffer = nullptr;
    }
}

// Method to set external ScreenBuffer
void NaughtsxCrossess::setScreenBuffer(ScreenBuffer* buffer) {
    if (ownsScreenBuffer && screenBuffer) {
        delete screenBuffer;  // Clean up internal buffer if we are replacing it
    }
    screenBuffer = buffer;
    ownsScreenBuffer = false;  // External buffer means we don't own it
}

void NaughtsxCrossess::printBoard() const {
    screenBuffer->writeToScreen(0, 0, L"-------------");
    int rowOffset = 1;
    for (int i = 0; i < BOARD_SIZE; ++i) {
        std::wstring row = L"| ";
        for (int j = 0; j < BOARD_SIZE; ++j) {
            row += std::wstring(1, board[i][j]) + L" | ";
        }
        screenBuffer->writeToScreen(0, rowOffset++, row);
        screenBuffer->writeToScreen(0, rowOffset++, L"-------------");
    }
}

void NaughtsxCrossess::printBoardWithNumbers() const {
    screenBuffer->writeToScreen(0, 0, L"-------------");
    int rowOffset = 9;
    int cellNumber = 1;
    for (int i = 0; i < BOARD_SIZE; ++i) {
        std::wstring row = L"| ";
        for (int j = 0; j < BOARD_SIZE; ++j) {
            row += std::to_wstring(cellNumber) + L" | ";
            cellNumber++;
        }
        screenBuffer->writeToScreen(0, rowOffset++, row);
        screenBuffer->writeToScreen(0, rowOffset++, L"-------------");
    }
}

bool NaughtsxCrossess::isMovesLeft() const {
    for (int i = 0; i < BOARD_SIZE; ++i)
        for (int j = 0; j < BOARD_SIZE; ++j)
            if (board[i][j] == ' ')
                return true;
    return false;
}

int NaughtsxCrossess::evaluate() const {
    // Check rows for a win
    for (int row = 0; row < BOARD_SIZE; ++row) {
        if (board[row][0] == board[row][1] && board[row][1] == board[row][2]) {
            if (board[row][0] == 'x')
                return +10;
            else if (board[row][0] == 'o')
                return -10;
        }
    }

    // Check columns for a win
    for (int col = 0; col < BOARD_SIZE; ++col) {
        if (board[0][col] == board[1][col] && board[1][col] == board[2][col]) {
            if (board[0][col] == 'x')
                return +10;
            else if (board[0][col] == 'o')
                return -10;
        }
    }

    // Check diagonals for a win
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

    return 0;
}

int NaughtsxCrossess::minimax(int depth, bool isMax, int difficulty) {
    int score = evaluate();

    if (score == 10 || score == -10)
        return score;

    if (!isMovesLeft())
        return 0;

    if (depth == difficulty)
        return 0;

    if (isMax) {
        int best = std::numeric_limits<int>::min();

        for (int i = 0; i < BOARD_SIZE; ++i) {
            for (int j = 0; j < BOARD_SIZE; ++j) {
                if (board[i][j] == ' ') {
                    board[i][j] = 'x';
                    best = std::max(best, minimax(depth + 1, !isMax, difficulty));  // Use std::max here
                    board[i][j] = ' ';
                }
            }
        }
        return best;
    }
    else {
        int best = std::numeric_limits<int>::max();

        for (int i = 0; i < BOARD_SIZE; ++i) {
            for (int j = 0; j < BOARD_SIZE; ++j) {
                if (board[i][j] == ' ') {
                    board[i][j] = 'o';
                    best = std::min(best, minimax(depth + 1, !isMax, difficulty));  // Use std::min here
                    board[i][j] = ' ';
                }
            }
        }
        return best;
    }
}

std::pair<int, int> NaughtsxCrossess::findBestMove(int difficulty) {
    int bestVal = std::numeric_limits<int>::min();
    std::pair<int, int> bestMove = { -1, -1 };

    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            if (board[i][j] == ' ') {
                board[i][j] = 'x';
                int moveVal = minimax(0, false, difficulty);
                board[i][j] = ' ';

                if (moveVal > bestVal) {
                    bestMove = { i, j };
                    bestVal = moveVal;
                }
            }
        }
    }

    return bestMove;
}

bool NaughtsxCrossess::playerMove(char player, std::function<std::string()> inputProvider) {
    screenBuffer->writeToScreen(0, 0, L"Enter your move (1-9) or type 'stop' to end the game: ");

    // Use the input provider if it's passed; otherwise, use the default screenBuffer input
    std::string input = inputProvider ? inputProvider() : screenBuffer->getBlockingInput();

    if (input == "stop") {
        return false;
    }

    int move = std::stoi(input);
    move--;

    int row = move / BOARD_SIZE;
    int col = move % BOARD_SIZE;

    if (move >= 0 && move < BOARD_SIZE * BOARD_SIZE && board[row][col] == ' ') {
        board[row][col] = player;
    }
    else {
        screenBuffer->writeToScreen(0, 1, L"Invalid move. Try again.");
        return playerMove(player, inputProvider);  // Recursively call playerMove with the same inputProvider
    }

    return true;
}

void NaughtsxCrossess::aiMove(int difficulty) {
    if (difficulty == 1) {
        srand(static_cast<unsigned int>(time(0)));
        int row, col;
        do {
            row = rand() % BOARD_SIZE;
            col = rand() % BOARD_SIZE;
        } while (board[row][col] != ' ');
        board[row][col] = 'x';
    }
    else {
        std::pair<int, int> bestMove = findBestMove(difficulty == 2 ? 2 : 100);
        board[bestMove.first][bestMove.second] = 'x';
    }
}

void NaughtsxCrossess::clearScreen() const {
    screenBuffer->clearScreen();
}

void NaughtsxCrossess::run(std::function<std::string()> inputProvider) {
    bool playAgain = true;

    while (playAgain) {
        resetBoard();
        // Ask for difficulty or mode selection
        screenBuffer->setActive();
        clearScreen();
        screenBuffer->writeToScreen(0, 0, L"Select mode (1 = Easy, 2 = Medium, 3 = Hard, 4 = Player vs Player): ");

        std::string input = inputProvider ? inputProvider() : screenBuffer->getBlockingInput();
        if (input == "stop") {
            return;  // Stop the program if "stop" is entered
        }

        int difficulty = std::stoi(input);
        if (difficulty < 1 || difficulty > 4) {
            screenBuffer->writeToScreen(0, 1, L"Invalid mode selected. Exiting.");
            return;
        }

        screenBuffer->writeToScreen(0, 2, L"Welcome to Noughts and Crosses!");
        screenBuffer->writeToScreen(0, 3, L"Here's the board with numbered cells:");
        printBoardWithNumbers();

        bool isPvP = (difficulty == 4);
        bool gameOver = false;

        // Main game loop
        while (isMovesLeft() && !gameOver) {
            clearScreen();
            printBoardWithNumbers();  // Show numbered board
            printBoard();  // Show current board with pieces

            if (!playerMove(isPvP ? 'o' : 'o', inputProvider)) {  // Player 1 move
                clearScreen();
                screenBuffer->writeToScreen(0, 4, L"Game stopped by the player.");
                gameOver = true;
                break;
            }

            clearScreen();
            printBoardWithNumbers();  // Show numbered board
            printBoard();  // Show current board with pieces

            if (evaluate() == -10) {
                clearScreen();
                printBoard();
                screenBuffer->writeToScreen(0, 8, L"Player O wins!");
                gameOver = true;
                break;
            }

            if (!isMovesLeft()) {
                clearScreen();
                printBoard();
                screenBuffer->writeToScreen(0, 8, L"It's a draw!");
                gameOver = true;
                break;
            }

            if (isPvP) {
                if (!playerMove('x', inputProvider)) {  // Player 2 move
                    clearScreen();
                    screenBuffer->writeToScreen(0, 7, L"Game stopped by the player.");
                    gameOver = true;
                    break;
                }
            }
            else {
                clearScreen();
                screenBuffer->writeToScreen(0, 8, L"AI is making a move...");
                aiMove(difficulty);
            }

            clearScreen();
            printBoardWithNumbers();  // Show numbered board
            printBoard();  // Show current board with pieces

            if (evaluate() == 10) {
                clearScreen();
                printBoard();
                screenBuffer->writeToScreen(0, 9, isPvP ? L"Player X wins!" : L"AI wins!");
                gameOver = true;
                break;
            }

            if (!isMovesLeft()) {
                clearScreen();
                printBoard();
                screenBuffer->writeToScreen(0, 10, L"It's a draw!");
                gameOver = true;
                break;
            }
        }

        // Ask if player wants to play again
        screenBuffer->writeToScreen(0, 12, L"Do you want to play again? (y/n): ");
        std::string playAgainInput = inputProvider ? inputProvider() : screenBuffer->getBlockingInput();

        if (playAgainInput != "y" && playAgainInput != "Y") {
            playAgain = false;
        }
    }

    screenBuffer->writeToScreen(0, 13, L"Thanks for playing!");
}

void NaughtsxCrossess::resetBoard() {
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            board[i][j] = ' ';
        }
    }
}

char& NaughtsxCrossess::getBoardValue(int row, int col) {
    return board[row][col];  // Return a reference to the board cell
}
