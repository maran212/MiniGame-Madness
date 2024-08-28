#include "NaughtsxCrossess.h"

NaughtsxCrossess::NaughtsxCrossess() {
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            board[i][j] = ' ';
        }
    }
}

void NaughtsxCrossess::printBoard() const {
    std::cout << "-------------\n";
    for (int i = 0; i < BOARD_SIZE; ++i) {
        std::cout << "| ";
        for (int j = 0; j < BOARD_SIZE; ++j) {
            std::cout << board[i][j] << " | ";
        }
        std::cout << "\n-------------\n";
    }
}

void NaughtsxCrossess::printBoardWithNumbers() const {
    std::cout << "-------------\n";
    int cellNumber = 1;
    for (int i = 0; i < BOARD_SIZE; ++i) {
        std::cout << "| ";
        for (int j = 0; j < BOARD_SIZE; ++j) {
            std::cout << cellNumber << " | ";
            cellNumber++;
        }
        std::cout << "\n-------------\n";
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
    for (int row = 0; row < BOARD_SIZE; ++row) {
        if (board[row][0] == board[row][1] && board[row][1] == board[row][2]) {
            if (board[row][0] == 'x')
                return +10;
            else if (board[row][0] == 'o')
                return -10;
        }
    }

    for (int col = 0; col < BOARD_SIZE; ++col) {
        if (board[0][col] == board[1][col] && board[1][col] == board[2][col]) {
            if (board[0][col] == 'x')
                return +10;
            else if (board[0][col] == 'o')
                return -10;
        }
    }

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
                    best = std::max(best, minimax(depth + 1, !isMax, difficulty));
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
                    best = std::min(best, minimax(depth + 1, !isMax, difficulty));
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

bool NaughtsxCrossess::playerMove(char player) {
    std::string input;
    std::cout << "Enter your move (1-9) or type 'stop' to end the game: ";
    std::cin >> input;

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
        std::cout << "Invalid move. Try again.\n";
        return playerMove(player);
    }

    return true;
}

void NaughtsxCrossess::aiMove(int difficulty) {
    if (difficulty == 1) {
        srand(time(0));
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
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void NaughtsxCrossess::run() {
    // Run tests if needed
    // testGame();

    // Proceed with the game if all tests pass
    std::string input;
    std::cout << "Select mode (1 = Easy, 2 = Medium, 3 = Hard, 4 = Player vs Player): ";
    std::cin >> input;

    if (input == "stop") {
        return; // Stop the program if "stop" is entered
    }

    int difficulty = std::stoi(input);

    if (difficulty < 1 || difficulty > 4) {
        std::cout << "Invalid mode selected. Exiting.\n";
        return;
    }

    std::cout << "Welcome to Noughts and Crosses!\n";
    std::cout << "Here's the board with numbered cells:\n";
    printBoardWithNumbers();

    bool isPvP = (difficulty == 4);

    // Main game loop
    while (isMovesLeft()) {
        clearScreen();  // Clear console before showing the board
        printBoardWithNumbers();
        printBoard();

        if (!playerMove(isPvP ? 'o' : 'o')) { // Player 1 move
            std::cout << "Game stopped by the player.\n";
            break;
        }

        clearScreen();
        printBoardWithNumbers();
        printBoard();

        if (evaluate() == -10) {
            std::cout << "Player O wins!\n";
            break;
        }

        if (!isMovesLeft()) {
            std::cout << "It's a draw!\n";
            break;
        }

        if (isPvP) {
            if (!playerMove('x')) { // Player 2 move
                std::cout << "Game stopped by the player.\n";
                break;
            }
        }
        else {
            std::cout << "AI is making a move...\n";
            aiMove(difficulty);
        }

        clearScreen();
        printBoardWithNumbers();
        printBoard();

        if (evaluate() == 10) {
            std::cout << (isPvP ? "Player X wins!\n" : "AI wins!\n");
            break;
        }

        if (!isMovesLeft()) {
            std::cout << "It's a draw!\n";
            break;
        }
    }
}
