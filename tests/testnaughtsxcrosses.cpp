#include "pch.h"
#include "CppUnitTest.h"
#include "../src/NaughtsxCrossess.h"
#include <iostream>
#include <stdexcept>
#include <string>
#include <utility>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Microsoft {
	namespace VisualStudio {
		namespace CppUnitTestFramework {
			template<> static std::wstring ToString<std::pair<int, int>>(const std::pair<int, int>& pair) {
				return L"(" + std::to_wstring(pair.first) + L", " + std::to_wstring(pair.second) + L")";
			}
		}
	}
}

namespace NaughtsCrossesTests
{
	TEST_CLASS(NaughtsCrossesTests)
	{
	public:

		TEST_METHOD(TestEvaluateEmptyBoard)
		{
			NaughtsxCrossess game;
			// Reset the board to an empty state
			for (int i = 0; i < BOARD_SIZE; ++i)
				for (int j = 0; j < BOARD_SIZE; ++j)
					game.playerMove(' ');  // Resetting the board

			// Test that the evaluation of an empty board is 0
			Assert::AreEqual(0, game.evaluate(), L"Empty board evaluation failed.");
		}

		TEST_METHOD(TestEvaluateRowVictory)
		{
			NaughtsxCrossess game;
			// Simulate a row victory for 'x'
			game.playerMove('x');  // Simulate player move
			game.playerMove('x');
			game.playerMove('x');  // Ensure to place 'x' in a row

			Assert::AreEqual(10, game.evaluate(), L"Row victory evaluation failed.");
		}

		TEST_METHOD(TestEvaluateColumnVictory)
		{
			NaughtsxCrossess game;
			// Simulate a column victory for 'o'
			game.playerMove('o');  // Place 'o' in a column
			game.playerMove('o');
			game.playerMove('o');

			Assert::AreEqual(-10, game.evaluate(), L"Column victory evaluation failed.");
		}

		TEST_METHOD(TestEvaluateDiagonalVictory)
		{
			NaughtsxCrossess game;
			// Simulate a diagonal victory for 'x'
			game.playerMove('x');  // Place 'x' in a diagonal
			game.playerMove('x');
			game.playerMove('x');

			Assert::AreEqual(10, game.evaluate(), L"Diagonal victory evaluation failed.");
		}

		TEST_METHOD(TestFindBestMove)
		{
			NaughtsxCrossess game;
			// Reset the board and set up a scenario
			for (int i = 0; i < BOARD_SIZE; ++i)
				for (int j = 0; j < BOARD_SIZE; ++j)
					game.playerMove(' ');  // Resetting the board

			game.playerMove('x');  // Simulate player move
			game.playerMove('x');  // Set up board with 2 'x' in a row

			auto bestMove = game.findBestMove(3);

			Assert::AreEqual(std::make_pair(0, 2), bestMove, L"Best move evaluation failed.");
		}
	};
}
