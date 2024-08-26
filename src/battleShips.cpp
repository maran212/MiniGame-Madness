#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <string>

using namespace std;

const int gridSize = 10;

enum CellState { EMPTY, SHIP, MISS, HIT };

struct Ship {
    string name;
    int size;
    vector<pair<int, int>> positions;
    int hits;

    Ship(string n, int s) : name(n), size(s), hits(0) {}
};

struct Player {
    vector<vector<CellState>> grid;
    vector<Ship> ships;
    int shipsRemaining;

    Player() : grid(gridSize, vector<CellState>(gridSize, EMPTY)), shipsRemaining(0) {}
};

// Function declarations
void displayGrid(const vector<vector<CellState>>& grid, bool revealShips);
bool placeShip(Player& player, Ship& ship, int row, int col, bool horizontal);
void autoPlaceShips(Player& player, vector<Ship>& ships);
bool isGameOver(const Player& player);
pair<int, int> getAIShot(Player& player);
void playerTurn(Player& player, Player& opponent);
void aiTurn(Player& player, Player& opponent);
void setupGame(Player& player, bool isAI);
void showBoards(Player& player, Player& ai);

int Battleship() {
    srand(static_cast<unsigned int>(time(0))); // Seed the random number generator with the current time

    Player player, ai;
    setupGame(player, false); // Player setup
    setupGame(ai, true); // AI setup

    // Main game loop
    while (!isGameOver(player) && !isGameOver(ai)) {
        playerTurn(player, ai);
        if (!isGameOver(ai)) {
            aiTurn(ai, player);
        }
    }

    if (isGameOver(player)) {
        cout << "You lost!" << endl;
    }
    else {
        cout << "You won!" << endl;
    }

    return 0;
}

void displayGrid(const vector<vector<CellState>>& grid, bool revealShips) {
    cout << "  ";
    for (int i = 0; i < gridSize; ++i) {
        cout << i << " ";
    }
    cout << endl;

    for (int row = 0; row < gridSize; ++row) {
        cout << row << " ";
        for (int col = 0; col < gridSize; ++col) {
            if (grid[row][col] == SHIP && revealShips) {
                cout << "S ";
            }
            else if (grid[row][col] == MISS) {
                cout << "M ";
            }
            else if (grid[row][col] == HIT) {
                cout << "H ";
            }
            else {
                cout << ". ";
            }
        }
        cout << endl;
    }
}

bool placeShip(Player& player, Ship& ship, int row, int col, bool horizontal) {
    if (horizontal) {
        if (col + ship.size > gridSize) return false;
        for (int i = 0; i < ship.size; ++i) {
            if (player.grid[row][col + i] != EMPTY) return false;
        }
        for (int i = 0; i < ship.size; ++i) {
            player.grid[row][col + i] = SHIP;
            ship.positions.push_back({ row, col + i });
        }
    }
    else {
        if (row + ship.size > gridSize) return false;
        for (int i = 0; i < ship.size; ++i) {
            if (player.grid[row + i][col] != EMPTY) return false;
        }
        for (int i = 0; i < ship.size; ++i) {
            player.grid[row + i][col] = SHIP;
            ship.positions.push_back({ row + i, col });
        }
    }
    player.ships.push_back(ship);
    player.shipsRemaining++;
    return true;
}

void autoPlaceShips(Player& player, vector<Ship>& ships) {
    for (auto& ship : ships) {
        bool placed = false;
        while (!placed) {
            int row = rand() % gridSize;
            int col = rand() % gridSize;
            bool horizontal = rand() % 2;
            placed = placeShip(player, ship, row, col, horizontal);
        }
    }
}

bool isGameOver(const Player& player) {
    for (const auto& ship : player.ships) {
        if (ship.hits < ship.size) {
            return false;  // Game is not over if any ship has not been fully hit
        }
    }
    return true;  // All ships have been sunk
}

pair<int, int> getAIShot(Player& player) {
    int row, col;
    do {
        row = rand() % gridSize;
        col = rand() % gridSize;
    } while (player.grid[row][col] == MISS || player.grid[row][col] == HIT);

    return { row, col };
}

void playerTurn(Player& player, Player& opponent) {
    string input;
    int row, col;

    displayGrid(opponent.grid, false);
    cout << "Enter row and column to fire (e.g., '27' or '2 7') or type 'show' to see both boards: ";
    getline(cin >> ws, input);  // Read the entire line of input, including any spaces

    if (input == "show") {
        showBoards(player, opponent);
        playerTurn(player, opponent);  // Recur to let the player make a move after showing the boards
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
        cout << "Invalid input. Please enter two digits, such as '27' or '2 7'." << endl;
        playerTurn(player, opponent);  // Let the player retry the turn
        return;
    }

    // Validate row and col
    if (row < 0 || row >= gridSize || col < 0 || col >= gridSize) {
        cout << "Invalid coordinates. Please enter values within the grid." << endl;
        playerTurn(player, opponent);  // Let the player retry the turn
        return;
    }

    // Fire at the opponent's grid
    if (opponent.grid[row][col] == SHIP) {
        cout << "Hit!" << endl;
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
        cout << "Miss!" << endl;
        opponent.grid[row][col] = MISS;
    }
}

void aiTurn(Player& ai, Player& player) {
    pair<int, int> shot = getAIShot(player);
    int row = shot.first;
    int col = shot.second;
    cout << "AI fires at " << row << ", " << col << endl;
    if (player.grid[row][col] == SHIP) {
        cout << "AI hit your ship!" << endl;
        player.grid[row][col] = HIT;
        for (auto& ship : player.ships) {
            for (auto& pos : ship.positions) {
                if (pos.first == row && pos.second == col) {
                    ship.hits++;
                    break;
                }
            }
        }
    }
    else {
        cout << "AI missed!" << endl;
        player.grid[row][col] = MISS;
    }
}

void setupGame(Player& player, bool isAI) {
    vector<Ship> ships = {
        {"Carrier", 5},
        {"Battleship", 4},
        {"Cruiser", 3},
        {"Submarine", 3},
        {"Destroyer", 2}
    };

    if (!isAI) {
        char choice;
        cout << "Do you want to manually place your ships or auto-place them? (m/a): ";
        cin >> choice;

        if (choice == 'a' || choice == 'A') {
            autoPlaceShips(player, ships);
            cout << "Ships have been auto-placed. Here's your board:" << endl;
            displayGrid(player.grid, true);
        }
        else {
            for (auto& ship : ships) {
                bool placed = false;
                while (!placed) {
                    displayGrid(player.grid, true);
                    cout << "Place your " << ship.name << " (size " << ship.size << ") at row, col and orientation (h/v): ";
                    int row, col;
                    char orientation;
                    cin >> row >> col >> orientation;
                    bool horizontal = (orientation == 'h');
                    placed = placeShip(player, ship, row, col, horizontal);
                    if (!placed) {
                        cout << "Invalid placement, try again." << endl;
                    }
                }
            }
        }
    }
    else {
        autoPlaceShips(player, ships);  // Auto-place for AI
    }
}

void showBoards(Player& player, Player& ai) {
    cout << "\nYour Board:" << endl;
    displayGrid(player.grid, true);
    cout << "\nAI's Board:" << endl;
    displayGrid(ai.grid, true);
}
