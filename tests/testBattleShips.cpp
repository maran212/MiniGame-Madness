#include "pch.h"
#include "CppUnitTest.h"
#include "../src/BattleshipGame.h"
#include "../src/ScreenBuffer.h"
#include <iostream>
#include <stdexcept>
#include <string>
#include <functional>
#include <vector>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Microsoft {
    namespace VisualStudio {
        namespace CppUnitTestFramework {
            template<>
            inline std::wstring ToString<CellState>(const CellState& cellState) {
                switch (cellState) {
                case EMPTY:
                    return L"EMPTY";
                case SHIP:
                    return L"SHIP";
                case MISS:
                    return L"MISS";
                case HIT:
                    return L"HIT";
                default:
                    return L"UNKNOWN";
                }
            }
        }
    }
}

namespace BattleShipsTests
{
    TEST_CLASS(BattleShipsTests)
    {
    public:

        TEST_METHOD(TestPlaceShip)
        {
            Player player;
            Ship ship("Destroyer", 2);
            bool placed = player.placeShip(ship, 0, 0, true);

            Assert::IsTrue(placed, L"Ship was not placed correctly.");
            Assert::AreEqual(2, static_cast<int>(ship.positions.size()), L"Ship size does not match expected size.");
        }

        TEST_METHOD(TestPlaceShipOverlap)
        {
            Player player;
            Ship ship1("Destroyer", 2);
            Ship ship2("Submarine", 3);
            player.placeShip(ship1, 0, 0, true);
            bool placed = player.placeShip(ship2, 0, 1, true);

            Assert::IsFalse(placed, L"Ship was placed where it should have overlapped.");
        }

        TEST_METHOD(TestAutoPlaceShips)
        {
            Player player;
            std::vector<Ship> ships = {
                {"Carrier", 5},
                {"Battleship", 4},
                {"Cruiser", 3},
                {"Submarine", 3},
                {"Destroyer", 2}
            };
            player.autoPlaceShips(ships);

            Assert::AreEqual(5, static_cast<int>(player.ships.size()), L"Number of placed ships does not match expected.");
        }

        TEST_METHOD(TestIsGameOver)
        {
            Player player;
            Ship ship("Destroyer", 2);
            player.placeShip(ship, 0, 0, true);
            player.ships[0].hits = 2;

            Assert::IsTrue(player.isGameOver(), L"Game should be over but is not detected as such.");
        }

        TEST_METHOD(TestAIShot)
        {
            Player player;
            Ship ship("Destroyer", 2);
            player.placeShip(ship, 0, 0, true);
            std::pair<int, int> shot = player.getAIShot();

            Assert::IsTrue(player.grid[shot.first][shot.second] != MISS && player.grid[shot.first][shot.second] != HIT,
                L"AI shot resulted in an invalid outcome (MISS or HIT on an invalid tile).");
        }

        // New Tests Using Simulated Input

        TEST_METHOD(TestSetupGameAutoPlacement)
        {
            // Simulated input: choose auto-placement
            int inputIndex = 0;
            std::vector<std::string> simulatedInputs = { "a" };
            std::function<std::string()> inputProvider = [&simulatedInputs, &inputIndex]() {
                if (inputIndex < simulatedInputs.size()) {
                    return simulatedInputs[inputIndex++];
                }
                return std::string("stop");
                };

            ScreenBuffer buffer;
            Player player;
            player.setupGame(false, &buffer, inputProvider);

            Assert::AreEqual(5, static_cast<int>(player.ships.size()), L"Ships were not placed correctly in auto-placement.");
        }

        TEST_METHOD(TestSetupGameManualPlacement)
        {
            // Simulated input: choose manual placement and provide ship positions
            int inputIndex = 0;
            std::vector<std::string> simulatedInputs = {
                "m",
                "0 0 h",
                "1 0 h",
                "2 0 h",
                "3 0 h",
                "4 0 h"
            };
            std::function<std::string()> inputProvider = [&simulatedInputs, &inputIndex]() {
                if (inputIndex < simulatedInputs.size()) {
                    return simulatedInputs[inputIndex++];
                }
                return std::string("stop");
                };

            ScreenBuffer buffer;
            Player player;
            player.setupGame(false, &buffer, inputProvider);

            Assert::AreEqual(5, static_cast<int>(player.ships.size()), L"Ships were not placed correctly in manual placement.");
        }

        TEST_METHOD(TestPlayerTurnHit)
        {
            // Set up opponent with a ship at (0,0)
            Player opponent;
            Ship ship("Destroyer", 2);
            opponent.placeShip(ship, 0, 0, true);

            // Simulated input: Player fires at (0,0)
            int inputIndex = 0;
            std::vector<std::string> simulatedInputs = { "0 0" };
            std::function<std::string()> inputProvider = [&simulatedInputs, &inputIndex]() {
                if (inputIndex < simulatedInputs.size()) {
                    return simulatedInputs[inputIndex++];
                }
                return std::string("stop");
                };

            ScreenBuffer buffer;
            Player player;
            player.playerTurn(opponent, &buffer, inputProvider);

            // Check that the opponent's grid has a HIT at (0,0)
            Assert::AreEqual(HIT, opponent.grid[0][0], L"Player's shot did not register as HIT.");
        }

        TEST_METHOD(TestPlayerTurnMiss)
        {
            // Opponent has no ships
            Player opponent;

            // Simulated input: Player fires at (0,0)
            int inputIndex = 0;
            std::vector<std::string> simulatedInputs = { "0 0" };
            std::function<std::string()> inputProvider = [&simulatedInputs, &inputIndex]() {
                if (inputIndex < simulatedInputs.size()) {
                    return simulatedInputs[inputIndex++];
                }
                return std::string("stop");
                };

            ScreenBuffer buffer;
            Player player;
            player.playerTurn(opponent, &buffer, inputProvider);

            // Check that the opponent's grid has a MISS at (0,0)
            Assert::AreEqual(MISS, opponent.grid[0][0], L"Player's shot did not register as MISS.");
        }

        TEST_METHOD(TestAITurnHit)
        {
            // Set up player with a ship at (0,0)
            Player player;
            Ship ship("Destroyer", 2);
            player.placeShip(ship, 0, 0, true);

            // Create a Predictable AI that always fires at (0,0)
            class PredictableAI : public Player {
            public:
                virtual std::pair<int, int> getAIShot() {
                    return { 0, 0 };
                }
            };

            PredictableAI ai;
            ScreenBuffer buffer;
            ai.aiTurn(player, &buffer);

            // Check that the player's grid has a HIT at (0,0)
            Assert::AreEqual(HIT, player.grid[0][0], L"AI's shot did not register as HIT.");
        }

        TEST_METHOD(TestAITurnMiss)
        {
            // Player has no ships
            Player player;

            // Create a Predictable AI that always fires at (0,0)
            class PredictableAI : public Player {
            public:
                virtual std::pair<int, int> getAIShot() {
                    return { 0, 0 };
                }
            };

            PredictableAI ai;
            ScreenBuffer buffer;
            ai.aiTurn(player, &buffer);

            // Check that the player's grid has a MISS at (0,0)
            Assert::AreEqual(MISS, player.grid[0][0], L"AI's shot did not register as MISS.");
        }

        /*
        TEST_METHOD(TestBattleshipGameRun_PlayerWins)
        {
            // Simulated inputs for player to sink all AI ships
            int inputIndex = 0;
            std::vector<std::string> simulatedInputs = {
                "a", // Auto-place ships
                // Shots to sink AI's ships
                "0 0", "0 1", "0 2", "0 3", "0 4",
                "1 0", "1 1", "1 2", "1 3",
                "2 0", "2 1", "2 2",
                "3 0", "3 1", "3 2",
                "4 0", "4 1"
            };
            std::function<std::string()> inputProvider = [&simulatedInputs, &inputIndex]() {
                if (inputIndex < simulatedInputs.size()) {
                    return simulatedInputs[inputIndex++];
                }
                return std::string("stop");
                };

            ScreenBuffer buffer;
            BattleshipGame game(&buffer);

            // Mock AI setup
            game.ai.ships.clear();
            game.ai.grid = std::vector<std::vector<CellState>>(gridSize, std::vector<CellState>(gridSize, EMPTY));
            std::vector<Ship> aiShips = {
                {"Carrier", 5},
                {"Battleship", 4},
                {"Cruiser", 3},
                {"Submarine", 3},
                {"Destroyer", 2}
            };
            game.ai.placeShip(aiShips[0], 0, 0, true);
            game.ai.placeShip(aiShips[1], 1, 0, true);
            game.ai.placeShip(aiShips[2], 2, 0, true);
            game.ai.placeShip(aiShips[3], 3, 0, true);
            game.ai.placeShip(aiShips[4], 4, 0, true);

            // Run the game with simulated input
            game.run(inputProvider);

            // Verify that the AI is defeated
            Assert::IsTrue(game.ai.isGameOver(), L"AI should be defeated, but game did not end correctly.");
        }
        */

        /**
        TEST_METHOD(TestBattleshipGameRun_PlayerLoses)
        {
            // Simulated inputs for player missing shots
            int inputIndex = 0;
            std::vector<std::string> simulatedInputs = {
                "a", // Auto-place ships
                // Shots that miss AI's ships
                "9 9", "8 8", "7 7", "6 6", "5 5"
            };
            std::function<std::string()> inputProvider = [&simulatedInputs, &inputIndex]() {
                if (inputIndex < simulatedInputs.size()) {
                    return simulatedInputs[inputIndex++];
                }
                return std::string("stop");
                };

            ScreenBuffer buffer;
            BattleshipGame game(&buffer);

            // Mock player's ships
            game.player.ships.clear();
            game.player.grid = std::vector<std::vector<CellState>>(gridSize, std::vector<CellState>(gridSize, EMPTY));
            std::vector<Ship> playerShips = {
                {"Carrier", 5},
                {"Battleship", 4},
                {"Cruiser", 3},
                {"Submarine", 3},
                {"Destroyer", 2}
            };
            game.player.placeShip(playerShips[0], 0, 0, true);
            game.player.placeShip(playerShips[1], 1, 0, true);
            game.player.placeShip(playerShips[2], 2, 0, true);
            game.player.placeShip(playerShips[3], 3, 0, true);
            game.player.placeShip(playerShips[4], 4, 0, true);

            // Mock AI to sink player's ships
            class PredictableAI : public Player {
            public:
                int shotIndex = 0;
                std::vector<std::pair<int, int>> shots = {
                    {0, 0}, {0, 1}, {0, 2}, {0, 3}, {0, 4},
                    {1, 0}, {1, 1}, {1, 2}, {1, 3},
                    {2, 0}, {2, 1}, {2, 2},
                    {3, 0}, {3, 1}, {3, 2},
                    {4, 0}, {4, 1}
                };

                virtual std::pair<int, int> getAIShot() {
                    if (shotIndex < shots.size()) {
                        return shots[shotIndex++];
                    }
                    return { rand() % gridSize, rand() % gridSize };
                }
            };

            game.ai = PredictableAI();

            // Run the game with simulated input
            game.run(inputProvider);

            // Verify that the player is defeated
            Assert::IsTrue(game.player.isGameOver(), L"Player should be defeated, but game did not end correctly.");
        }
        **/
    };
}
