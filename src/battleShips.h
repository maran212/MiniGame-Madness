
#ifndef BATTLESHIP_GAME_H
#define BATTLESHIP_GAME_H

#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <cstdlib>

/// @brief The size of the game grid.
const int gridSize = 10;

/// @brief Enumeration representing the state of a cell in the grid.
enum CellState { EMPTY, SHIP, MISS, HIT };

/// @brief Represents a ship in the game.
class Ship {
public:
    std::string name; ///< The name of the ship.
    int size; ///< The size of the ship.
    std::vector<std::pair<int, int>> positions; ///< The positions occupied by the ship on the grid.
    int hits; ///< The number of times the ship has been hit.

    /// @brief Constructs a Ship with a given name and size.
    /// @param n The name of the ship.
    /// @param s The size of the ship.
    Ship(std::string n, int s) : name(n), size(s), hits(0) {}
};

/// @brief Represents a player in the game.
class Player {
public:
    std::vector<std::vector<CellState>> grid; ///< The player's grid.
    std::vector<Ship> ships; ///< The ships owned by the player.
    int shipsRemaining; ///< The number of ships remaining that have not been sunk.

    /// @brief Constructs a Player with an empty grid and no ships.
    Player() : grid(gridSize, std::vector<CellState>(gridSize, EMPTY)), shipsRemaining(0) {}

    /// @brief Displays the player's grid.
    /// @param revealShips If true, ships will be shown on the grid.
    void displayGrid(bool revealShips);

    /// @brief Places a ship on the player's grid.
    /// @param ship The ship to place.
    /// @param row The starting row for the ship.
    /// @param col The starting column for the ship.
    /// @param horizontal If true, the ship is placed horizontally; otherwise, it is placed vertically.
    /// @return True if the ship was placed successfully; otherwise, false.
    bool placeShip(Ship& ship, int row, int col, bool horizontal);

    /// @brief Automatically places all ships on the player's grid.
    /// @param ships The ships to be placed.
    void autoPlaceShips(std::vector<Ship>& ships);

    /// @brief Checks if the game is over for the player (i.e., all ships are sunk).
    /// @return True if the game is over; otherwise, false.
    bool isGameOver() const;

    /// @brief The player's turn to attack the opponent.
    /// @param opponent The opponent being attacked.
    void playerTurn(Player& opponent);

    /// @brief The AI's turn to attack the opponent.
    /// @param opponent The opponent being attacked.
    void aiTurn(Player& opponent);

    /// @brief Sets up the player's ships on the grid.
    /// @param isAI If true, the setup is for an AI player; otherwise, it's for a human player.
    void setupGame(bool isAI);

    /// @brief Shows the player's and opponent's boards.
    /// @param ai The AI player's board.
    void showBoards(Player& ai);

    /// @brief Generates a shot for the AI player.
    /// @return A pair of integers representing the row and column of the shot.
    std::pair<int, int> getAIShot();
};

/// @brief Main function for running the Battleship game.
/// @return An integer representing the exit status of the game.
int Battleship();

#endif // BATTLESHIP_GAME_H
