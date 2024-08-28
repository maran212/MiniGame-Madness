#include "battleShips.h"

void Player::displayGrid(bool revealShips) {
    std::cout << "  ";
    for (int i = 0; i < gridSize; ++i) {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    for (int row = 0; row < gridSize; ++row) {
        std::cout << row << " ";
        for (int col = 0; col < gridSize; ++col) {
            if (grid[row][col] == SHIP && revealShips) {
                std::cout << "S ";
            }
            else if (grid[row][col] == MISS) {
                std::cout << "M ";
            }
            else if (grid[row][col] == HIT) {
                std::cout << "H ";
            }
            else {
                std::cout << ". ";
            }
        }
        std::cout << std::endl;
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
    shipsRemaining++;
    return true;
}

void Player::autoPlaceShips(std::vector<Ship>& ships) {
    for (auto& ship : ships) {
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

void Player::playerTurn(Player& opponent) {
    std::string input;
    int row, col;

    displayGrid(false);
    std::cout << "Enter row and column to fire (e.g., '27' or '2 7') or type 'show' to see both boards: ";
    std::getline(std::cin >> std::ws, input);  // Read the entire line of input, including any spaces

    if (input == "show") {
        showBoards(opponent);
        playerTurn(opponent);  // Recur to let the player make a move after showing the boards
        return;
    }

    // Handling input in the form "row col" or "rowcol"
    if (input.length() == 2) {
        row = input[0] - '0';
        col = input[1] - '0';
    }
    else if (input.length() == 3 && input[1] == ' ') {
        row = input[0] - '0';
        col = input[2] - '0';
    }
    else {
        std::cout << "Invalid input. Please enter two digits, such as '27' or '2 7'." << std::endl;
        playerTurn(opponent);  // Let the player retry the turn
        return;
    }

    // Validate row and col
    if (row < 0 || row >= gridSize || col < 0 || col >= gridSize) {
        std::cout << "Invalid coordinates. Please enter values within the grid." << std::endl;
        playerTurn(opponent);  // Let the player retry the turn
        return;
    }

    // Fire at the opponent's grid
    if (opponent.grid[row][col] == SHIP) {
        std::cout << "Hit!" << std::endl;
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
        std::cout << "Miss!" << std::endl;
        opponent.grid[row][col] = MISS;
    }
}

void Player::aiTurn(Player& opponent) {
    auto shot = getAIShot();
    int row = shot.first;
    int col = shot.second;
    std::cout << "AI fires at " << row << ", " << col << std::endl;
    if (opponent.grid[row][col] == SHIP) {
        std::cout << "AI hit your ship!" << std::endl;
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
        std::cout << "AI missed!" << std::endl;
        opponent.grid[row][col] = MISS;
    }
}

void Player::setupGame(bool isAI) {
    std::vector<Ship> ships = {
        {"Carrier", 5},
        {"Battleship", 4},
        {"Cruiser", 3},
        {"Submarine", 3},
        {"Destroyer", 2}
    };

    if (!isAI) {
        char choice;
        std::cout << "Do you want to manually place your ships or auto-place them? (m/a): ";
        std::cin >> choice;

        if (choice == 'a' || choice == 'A') {
            autoPlaceShips(ships);
            std::cout << "Ships have been auto-placed. Here's your board:" << std::endl;
            displayGrid(true);
        }
        else {
            for (auto& ship : ships) {
                bool placed = false;
                while (!placed) {
                    displayGrid(true);
                    std::cout << "Place your " << ship.name << " (size " << ship.size << ") at row, col and orientation (h/v): ";
                    int row, col;
                    char orientation;
                    std::cin >> row >> col >> orientation;
                    bool horizontal = (orientation == 'h');
                    placed = placeShip(ship, row, col, horizontal);
                    if (!placed) {
                        std::cout << "Invalid placement, try again." << std::endl;
                    }
                }
            }
        }
    }
    else {
        autoPlaceShips(ships);  // Auto-place for AI
    }
}

void Player::showBoards(Player& ai) {
    std::cout << "\nYour Board:" << std::endl;
    displayGrid(true);
    std::cout << "\nAI's Board:" << std::endl;
    ai.displayGrid(false);
}

int Battleship() {
    srand(static_cast<unsigned int>(time(0))); // Seed the random number generator with the current time

    Player player, ai;
    player.setupGame(false); // Player setup
    ai.setupGame(true); // AI setup

    // Main game loop
    while (!player.isGameOver() && !ai.isGameOver()) {
        player.playerTurn(ai);
        if (!ai.isGameOver()) {
            ai.aiTurn(player);
        }
    }

    if (player.isGameOver()) {
        std::cout << "You lost!" << std::endl;
    }
    else {
        std::cout << "You won!" << std::endl;
    }

    return 0;
}
