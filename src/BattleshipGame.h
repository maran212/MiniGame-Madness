#ifndef BATTLESHIP_GAME_H
#define BATTLESHIP_GAME_H

#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <cstdlib>
#include <functional>
#include "ScreenBuffer.h"

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

    /// @brief Constructs a Player with an empty grid and no ships.
    Player() : grid(gridSize, std::vector<CellState>(gridSize, EMPTY)) {}

    /// @brief Displays the player's grid.
    /// @param revealShips If true, ships will be shown on the grid.
    /// @param screenBuffer Pointer to the ScreenBuffer for output.
    /// @param startX The starting X position for display.
    /// @param startY The starting Y position for display.
    void displayGrid(bool revealShips, ScreenBuffer* screenBuffer, int startX = 0, int startY = 0);

    /// @brief Places a ship on the player's grid.
    /// @param ship The ship to place.
    /// @param row The starting row for the ship.
    /// @param col The starting column for the ship.
    /// @param horizontal If true, the ship is placed horizontally; otherwise, vertically.
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
    /// @param screenBuffer Pointer to the ScreenBuffer for input/output.
    /// @param inputProvider Function to provide input for testing purposes.
    void playerTurn(Player& opponent, ScreenBuffer* screenBuffer, std::function<std::string()> inputProvider = nullptr);

    /// @brief The AI's turn to attack the opponent.
    /// @param opponent The opponent being attacked.
    /// @param screenBuffer Pointer to the ScreenBuffer for output.
    /// @param inputProvider Function to provide input for testing purposes.
    void aiTurn(Player& opponent, ScreenBuffer* screenBuffer, std::function<std::string()> inputProvider = nullptr);

    /// @brief Sets up the player's ships on the grid.
    /// @param isAI If true, the setup is for an AI player; otherwise, it's for a human player.
    /// @param screenBuffer Pointer to the ScreenBuffer for input/output.
    /// @param inputProvider Function to provide input for testing purposes.
    void setupGame(bool isAI, ScreenBuffer* screenBuffer, std::function<std::string()> inputProvider = nullptr);

    /// @brief Shows the player's and opponent's boards.
    /// @param opponent The opponent's board.
    /// @param screenBuffer Pointer to the ScreenBuffer for output.
    void showBoards(Player& opponent, ScreenBuffer* screenBuffer);

    /// @brief Generates a shot for the AI player.
    /// @return A pair of integers representing the row and column of the shot.
    virtual std::pair<int, int> getAIShot();
};

/// @brief Class representing the Battleship game.
class BattleshipGame {
public:
    /// @brief Default constructor. Initializes the game with its own ScreenBuffer.
    BattleshipGame();

    /// @brief Constructor that accepts an external ScreenBuffer.
    /// @param buffer Pointer to an externally provided ScreenBuffer.
    BattleshipGame(ScreenBuffer* buffer);

    /// @brief Copy Constructor
    BattleshipGame(const BattleshipGame& other);

    /// @brief Copy Assignment Operator
    BattleshipGame& operator=(const BattleshipGame& other);

    /// @brief Destructor to clean up resources.
    ~BattleshipGame();

    /// @brief Main function to run the Battleship game.
    /// @param inputProvider Function to provide input for testing purposes.
    void run(std::function<std::string()> inputProvider = nullptr);

    Player player; ///< The human player.
    Player ai;     ///< The AI opponent.

private:
    ScreenBuffer* screenBuffer;
    bool ownsScreenBuffer;
};

#endif // BATTLESHIP_GAME_H
