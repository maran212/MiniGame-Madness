#include "BattleshipGame.h"

BattleshipGame::BattleshipGame() : screenBuffer(nullptr), ownsScreenBuffer(true), player(), ai() {
    screenBuffer = new ScreenBuffer();
}

BattleshipGame::BattleshipGame(ScreenBuffer* buffer) : screenBuffer(buffer), ownsScreenBuffer(false), player(), ai() {
    // Use the provided screenBuffer
}

BattleshipGame::~BattleshipGame() {
    if (ownsScreenBuffer && screenBuffer) {
        delete screenBuffer;
        screenBuffer = nullptr;
    }
}
// Copy Constructor
BattleshipGame::BattleshipGame(const BattleshipGame& other) : player(other.player), ai(other.ai) {
    if (other.screenBuffer && other.ownsScreenBuffer) {
        // Deep copy the ScreenBuffer
        screenBuffer = new ScreenBuffer(*other.screenBuffer);
        ownsScreenBuffer = true;
    }
    else {
        // If the original doesn't own the screenBuffer or it's nullptr, we share it
        screenBuffer = other.screenBuffer;
        ownsScreenBuffer = false;
    }
}

// Copy Assignment Operator
BattleshipGame& BattleshipGame::operator=(const BattleshipGame& other) {
    if (this != &other) {  // Protect against self-assignment
        // Clean up existing resources
        if (ownsScreenBuffer && screenBuffer) {
            delete screenBuffer;
            screenBuffer = nullptr;
        }

        // Copy players
        player = other.player;
        ai = other.ai;

        if (other.screenBuffer && other.ownsScreenBuffer) {
            // Deep copy the ScreenBuffer
            screenBuffer = new ScreenBuffer(*other.screenBuffer);
            ownsScreenBuffer = true;
        }
        else {
            // Share the screenBuffer
            screenBuffer = other.screenBuffer;
            ownsScreenBuffer = false;
        }
    }
    return *this;
}



void Player::displayGrid(bool revealShips, ScreenBuffer* screenBuffer, int startX, int startY) {
    int y = startY;
    std::wstring header = L"   ";
    for (int i = 0; i < gridSize; ++i) {
        header += std::to_wstring(i) + L" ";
    }
    screenBuffer->writeToScreen(startX, y++, header);

    for (int row = 0; row < gridSize; ++row) {
        std::wstring rowStr = L"";
        if (row < 10) rowStr += L" ";
        rowStr += std::to_wstring(row) + L" ";
        for (int col = 0; col < gridSize; ++col) {
            wchar_t cellChar;
            if (grid[row][col] == SHIP && revealShips) {
                cellChar = L'S';
            }
            else if (grid[row][col] == MISS) {
                cellChar = L'M';
            }
            else if (grid[row][col] == HIT) {
                cellChar = L'H';
            }
            else {
                cellChar = L'.';
            }
            rowStr += cellChar;
            rowStr += L" ";
        }
        screenBuffer->writeToScreen(startX, y++, rowStr);
    }
}

bool Player::placeShip(Ship& ship, int row, int col, bool horizontal) {
    if (horizontal) {
        if (col + ship.size > gridSize) return false;
        for (int i = 0; i < ship.size; ++i) {
            if (grid[row][col + i] != EMPTY) return false;
        }
        for (int i = 0; i < ship.size; ++i) {
            grid[row][col + i] = SHIP;
            ship.positions.push_back({ row, col + i });
        }
    }
    else {
        if (row + ship.size > gridSize) return false;
        for (int i = 0; i < ship.size; ++i) {
            if (grid[row + i][col] != EMPTY) return false;
        }
        for (int i = 0; i < ship.size; ++i) {
            grid[row + i][col] = SHIP;
            ship.positions.push_back({ row + i, col });
        }
    }
    ships.push_back(ship);
    return true;
}

void Player::autoPlaceShips(std::vector<Ship>& shipsList) {
    for (auto& ship : shipsList) {
        bool placed = false;
        while (!placed) {
            int row = rand() % gridSize;
            int col = rand() % gridSize;
            bool horizontal = rand() % 2;
            placed = placeShip(ship, row, col, horizontal);
        }
    }
}

bool Player::isGameOver() const {
    for (const auto& ship : ships) {
        if (ship.hits < ship.size) {
            return false;  // Game is not over if any ship has not been fully hit
        }
    }
    return true;  // All ships have been sunk
}

std::pair<int, int> Player::getAIShot() {
    int row, col;
    do {
        row = rand() % gridSize;
        col = rand() % gridSize;
    } while (grid[row][col] == MISS || grid[row][col] == HIT);
    return { row, col };
}

void Player::playerTurn(Player& opponent, ScreenBuffer* screenBuffer, std::function<std::string()> inputProvider) {
    while (true) {
        screenBuffer->clearScreen();
        showBoards(opponent, screenBuffer); // Show both boards

        screenBuffer->writeToScreen(0, gridSize * 2 + 3, L"Enter row and column to fire (e.g., '27' or '2 7'): ");

        std::string input;
        if (inputProvider) {
            input = inputProvider();
        }
        else {
            input = screenBuffer->getBlockingInput();
        }

        int row = -1, col = -1;
        // Handling input in the form "rowcol" or "row col"
        if (input.length() == 2 && isdigit(input[0]) && isdigit(input[1])) {
            row = input[0] - '0';
            col = input[1] - '0';
        }
        else if (input.length() >= 3 && isdigit(input[0]) && input[1] == ' ' && isdigit(input[2])) {
            row = input[0] - '0';
            col = input[2] - '0';
        }
        else {
            screenBuffer->writeToScreen(0, gridSize * 2 + 4, L"Invalid input. Please enter two digits, such as '27' or '2 7'.");
            if (!inputProvider) {
                screenBuffer->getBlockingInput();
            }
            continue;  // Prompt for input again
        }

        // Validate row and col
        if (row < 0 || row >= gridSize || col < 0 || col >= gridSize) {
            screenBuffer->writeToScreen(0, gridSize * 2 + 4, L"Invalid coordinates. Please enter values within the grid.");
            if (!inputProvider) {
                screenBuffer->getBlockingInput();
            }
            continue;  // Prompt for input again
        }

        // Fire at the opponent's grid
        if (opponent.grid[row][col] == SHIP) {
            screenBuffer->writeToScreen(0, gridSize * 2 + 4, L"Hit!");
            opponent.grid[row][col] = HIT;
            for (auto& ship : opponent.ships) {
                for (auto& pos : ship.positions) {
                    if (pos.first == row && pos.second == col) {
                        ship.hits++;
                        break;
                    }
                }
            }
        }
        else if (opponent.grid[row][col] == EMPTY) {
            screenBuffer->writeToScreen(0, gridSize * 2 + 4, L"Miss!");
            opponent.grid[row][col] = MISS;
        }
        else {
            screenBuffer->writeToScreen(0, gridSize * 2 + 4, L"You have already fired at this location.");
            if (!inputProvider) {
                screenBuffer->getBlockingInput();
            }
            continue;  // Prompt for input again
        }

        Sleep(1500);
        break;  // Exit the loop after a valid turn
    }
}

void Player::aiTurn(Player& opponent, ScreenBuffer* screenBuffer, std::function<std::string()> inputProvider) {
    auto shot = getAIShot();
    int row = shot.first;
    int col = shot.second;

    screenBuffer->clearScreen();

    // Show only the player's board
    screenBuffer->writeToScreen(0, 0, L"Your Board:");
    opponent.displayGrid(true, screenBuffer, 0, 1); // Show player's board with ships and hits/misses

    screenBuffer->writeToScreen(0, gridSize + 2, L"AI fires at " + std::to_wstring(row) + L", " + std::to_wstring(col));
    if (opponent.grid[row][col] == SHIP) {
        screenBuffer->writeToScreen(0, gridSize + 3, L"AI hit your ship!");
        opponent.grid[row][col] = HIT;
        for (auto& ship : opponent.ships) {
            for (auto& pos : ship.positions) {
                if (pos.first == row && pos.second == col) {
                    ship.hits++;
                    break;
                }
            }
        }
    }
    else {
        screenBuffer->writeToScreen(0, gridSize + 3, L"AI missed!");
        opponent.grid[row][col] = MISS;
    }

    Sleep(1500);
}

void Player::setupGame(bool isAI, ScreenBuffer* screenBuffer, std::function<std::string()> inputProvider) {
    std::vector<Ship> shipsList = {
        {"Carrier", 5},
        {"Battleship", 4},
        {"Cruiser", 3},
        {"Submarine", 3},
        {"Destroyer", 2}
    };

    if (!isAI) {
        std::string choice;
        if (inputProvider) {
            choice = inputProvider();
        }
        else {
            screenBuffer->writeToScreen(0, 0, L"Do you want to manually place your ships or auto-place them? (m/a): ");
            choice = screenBuffer->getBlockingInput();
        }

        if (choice == "a" || choice == "A") {
            autoPlaceShips(shipsList);
            screenBuffer->writeToScreen(0, 1, L"Ships have been auto-placed. Here's your board:");
            displayGrid(true, screenBuffer, 0, 2);
            screenBuffer->writeToScreen(0, gridSize + 3, L"Press Enter to continue...");
            if (!inputProvider) {
                screenBuffer->getBlockingInput();
            }
        }
        else {
            for (auto& ship : shipsList) {
                bool placed = false;
                while (!placed) {
                    screenBuffer->clearScreen();
                    displayGrid(true, screenBuffer);
                    screenBuffer->writeToScreen(0, gridSize + 2, L"Place your " + std::wstring(ship.name.begin(), ship.name.end()) +
                        L" (size " + std::to_wstring(ship.size) + L") at row, col and orientation (h/v): ");

                    std::string input;
                    if (inputProvider) {
                        input = inputProvider();
                    }
                    else {
                        input = screenBuffer->getBlockingInput();
                    }

                    int row = -1, col = -1;
                    char orientation = 'h';

                    // Parse the input
                    if (input.length() >= 5) {
                        row = input[0] - '0';
                        col = input[2] - '0';
                        orientation = input[4];
                    }
                    else {
                        screenBuffer->writeToScreen(0, gridSize + 3, L"Invalid input. Please enter row, col, and orientation.");
                        if (!inputProvider) {
                            screenBuffer->getBlockingInput();
                        }
                        continue;
                    }

                    if (row < 0 || row >= gridSize || col < 0 || col >= gridSize ||
                        (orientation != 'h' && orientation != 'v')) {
                        screenBuffer->writeToScreen(0, gridSize + 3, L"Invalid input. Try again.");
                        if (!inputProvider) {
                            screenBuffer->getBlockingInput();
                        }
                        continue;
                    }

                    bool horizontal = (orientation == 'h');
                    placed = placeShip(ship, row, col, horizontal);
                    if (!placed) {
                        screenBuffer->writeToScreen(0, gridSize + 3, L"Invalid placement, try again.");
                        if (!inputProvider) {
                            screenBuffer->getBlockingInput();
                        }
                    }
                }
            }
        }
    }
    else {
        autoPlaceShips(shipsList);  // Auto-place for AI
    }
}

void Player::showBoards(Player& opponent, ScreenBuffer* screenBuffer) {
    screenBuffer->writeToScreen(0, 0, L"Your Board:");
    displayGrid(true, screenBuffer, 0, 1); // Show your board with ships and hits/misses

    screenBuffer->writeToScreen(gridSize * 2 + 5, 0, L"Opponent's Board:");
    opponent.displayGrid(false, screenBuffer, gridSize * 2 + 1 + 5, 1); // Show opponent's board without ships
}

void BattleshipGame::run(std::function<std::string()> inputProvider) {
    srand(static_cast<unsigned int>(time(0))); // Seed the random number generator with the current time

    screenBuffer->setActive();
    player.setupGame(false, screenBuffer, inputProvider); // Player setup
    ai.setupGame(true, screenBuffer);      // AI setup

    // Main game loop
    while (!player.isGameOver() && !ai.isGameOver()) {
        player.playerTurn(ai, screenBuffer, inputProvider);
        if (!ai.isGameOver()) {
            ai.aiTurn(player, screenBuffer, inputProvider);
        }
    }

    screenBuffer->clearScreen();
    if (player.isGameOver()) {
        screenBuffer->writeToScreen(0, 0, L"You lost!");
    }
    else {
        screenBuffer->writeToScreen(0, 0, L"You won!");
    }
    screenBuffer->writeToScreen(0, 1, L"Press Enter to exit...");
    if (!inputProvider) {
        screenBuffer->getBlockingInput();
    }
}
