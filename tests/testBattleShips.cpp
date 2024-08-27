#include "pch.h"
#include "CppUnitTest.h"
#include "../src/battleShips.h"
#include <iostream>
#include <stdexcept>
#include <string>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

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
	};
}
