#include "pch.h"
#include "CppUnitTest.h"
#include "../src/NaughtsxCrossess.h"
#include <iostream>
#include <sstream>
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

        TEST_METHOD(TestPlayerMove)
        {
            NaughtsxCrossess game;

            // Redirect std::cin to use a stringstream with fake input
            std::istringstream input("1\n"); // Simulate input for position 1
            std::cin.rdbuf(input.rdbuf());

            Assert::IsTrue(game.playerMove('x'), L"Player move failed.");
            Assert::AreEqual('x', game.getBoardValue(0, 0), L"Board was not updated correctly.");
        }

        TEST_METHOD(TestEvaluateEmptyBoard)
        {
            NaughtsxCrossess game;

            // Simulate input for placing ' ' (space) in all positions 1-9 to ensure the board is empty
            std::istringstream input("1\n2\n3\n4\n5\n6\n7\n8\n9\n");
            std::cin.rdbuf(input.rdbuf());

            for (int i = 0; i < BOARD_SIZE * BOARD_SIZE; ++i)
            {
                game.playerMove(' ');  // Place ' ' in each position
            }

            // Test that the evaluation of an empty board is 0
            Assert::AreEqual(0, game.evaluate(), L"Empty board evaluation failed.");
        }

        TEST_METHOD(TestEvaluateRowVictory)
        {
            NaughtsxCrossess game;

            // Simulate input for placing 'x' in row 1 (positions 1, 2, 3)
            std::istringstream input("1\n2\n3\n");
            std::cin.rdbuf(input.rdbuf());

            game.playerMove('x');
            game.playerMove('x');
            game.playerMove('x');

            Assert::AreEqual(10, game.evaluate(), L"Row victory evaluation failed.");
        }

        TEST_METHOD(TestEvaluateColumnVictory)
        {
            NaughtsxCrossess game;

            // Simulate input for placing 'o' in column 1 (positions 1, 4, 7)
            std::istringstream input("1\n4\n7\n");
            std::cin.rdbuf(input.rdbuf());

            game.playerMove('o');
            game.playerMove('o');
            game.playerMove('o');

            Assert::AreEqual(-10, game.evaluate(), L"Column victory evaluation failed.");
        }

        TEST_METHOD(TestEvaluateDiagonalVictory)
        {
            NaughtsxCrossess game;

            // Simulate input for placing 'x' in a diagonal (positions 1, 5, 9)
            std::istringstream input("1\n5\n9\n");
            std::cin.rdbuf(input.rdbuf());

            game.playerMove('x');
            game.playerMove('x');
            game.playerMove('x');

            Assert::AreEqual(10, game.evaluate(), L"Diagonal victory evaluation failed.");
        }

        TEST_METHOD(TestFindBestMove)
        {
            NaughtsxCrossess game;

            // Simulate input for clearing the board by placing ' ' (space) in all positions 1-9
            std::istringstream clearInput("1\n2\n3\n4\n5\n6\n7\n8\n9\n");
            std::cin.rdbuf(clearInput.rdbuf());

            for (int i = 0; i < BOARD_SIZE * BOARD_SIZE; ++i)
            {
                game.playerMove(' ');  // Place ' ' in each position to clear the board
            }

            // Simulate input for placing 'x' in positions 1 and 2
            std::istringstream input("1\n2\n");
            std::cin.rdbuf(input.rdbuf());

            game.playerMove('x');  // Simulate placing 'x' at position 1 (index 0,0)
            game.playerMove('x');  // Simulate placing 'x' at position 2 (index 0,1)

            auto bestMove = game.findBestMove(3);  // Find the best move with difficulty 3

            Assert::AreEqual(std::make_pair(0, 2), bestMove, L"Best move evaluation failed.");
        }


    };
}
