#ifndef BATTLESHIP_GAME_H
#define BATTLESHIP_GAME_H

#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <cstdlib>

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
void aiTurn(Player& ai, Player& player);
void setupGame(Player& player, bool isAI);
void showBoards(Player& player, Player& ai);
int Battleship();

#endif // BATTLESHIP_GAME_H
