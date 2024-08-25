#include "BattleshipGame.h"
#include <iostream>
#include <stdexcept>
#include <string>

// Assertion functions
bool assertEqual(const int expected, const int actual)
{
    if (expected != actual)
    {
        throw std::runtime_error("Expected: " + std::to_string(expected) + " | Actual: " + std::to_string(actual));
    }
    return true;
}

bool assertEqual(const std::pair<int, int>& expected, const std::pair<int, int>& actual)
{
    if (expected != actual)
    {
        throw std::runtime_error("Expected: (" + std::to_string(expected.first) + ", " + std::to_string(expected.second) + ") | Actual: (" + std::to_string(actual.first) + ", " + std::to_string(actual.second) + ")");
    }
    return true;
}

bool assertTrue(const bool actual)
{
    if (!actual)
    {
        throw std::runtime_error("Expected: true | Actual: false");
    }
    return true;
}

// Test functions
bool testPlaceShip()
{
    Player player;
    Ship ship("Destroyer", 2);
    bool placed = placeShip(player, ship, 0, 0, true);
    return assertTrue(placed) && assertEqual(2, static_cast<int>(ship.positions.size()));
}

bool testPlaceShipOverlap()
{
    Player player;
    Ship ship1("Destroyer", 2);
    Ship ship2("Submarine", 3);
    placeShip(player, ship1, 0, 0, true);
    bool placed = placeShip(player, ship2, 0, 1, true);
    return assertTrue(!placed);
}

bool testAutoPlaceShips()
{
    Player player;
    vector<Ship> ships = {
        {"Carrier", 5},
        {"Battleship", 4},
        {"Cruiser", 3},
        {"Submarine", 3},
        {"Destroyer", 2}
    };
    autoPlaceShips(player, ships);
    return assertEqual(5, static_cast<int>(player.ships.size()));
}

bool testIsGameOver()
{
    Player player;
    Ship ship("Destroyer", 2);
    placeShip(player, ship, 0, 0, true);
    player.ships[0].hits = 2;
    return assertTrue(isGameOver(player));
}

bool testAIShot()
{
    Player player;
    Ship ship("Destroyer", 2);
    placeShip(player, ship, 0, 0, true);
    pair<int, int> shot = getAIShot(player);
    return assertTrue(player.grid[shot.first][shot.second] != MISS && player.grid[shot.first][shot.second] != HIT);
}

int main()
{
    int passed = 0;
    int total = 5;

    std::cout << "Running tests..." << std::endl;

    std::cout << "Test 1: Place Ship" << std::endl;
    try
    {
        testPlaceShip();
        passed++;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    std::cout << "Test 2: Place Ship Overlap" << std::endl;
    try
    {
        testPlaceShipOverlap();
        passed++;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    std::cout << "Test 3: Auto Place Ships" << std::endl;
    try
    {
        testAutoPlaceShips();
        passed++;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    std::cout << "Test 4: Is Game Over" << std::endl;
    try
    {
        testIsGameOver();
        passed++;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    std::cout << "Test 5: AI Shot" << std::endl;
    try
    {
        testAIShot();
        passed++;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    std::cout << "Passed " << passed << " of " << total << " tests" << std::endl;

    return 0;
}
