#include "pch.h"
#include "CppUnitTest.h"
#include "../src/NaughtsxCrossess.h"
#include "../src/ScreenBuffer.h"
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

        TEST_METHOD(TestPlayerMove) {
            ScreenBuffer buffer;
            NaughtsxCrossess game(&buffer);  // Pass the screen buffer to the game

            // Simulate input for position 1
            std::function<std::string()> simulatedInput = []() { return "1"; };

            Assert::IsTrue(game.playerMove('x', simulatedInput), L"Player move failed.");
            Assert::AreEqual('x', game.getBoardValue(0, 0), L"Board was not updated correctly.");
        }

        TEST_METHOD(TestEvaluateEmptyBoard)
        {
            ScreenBuffer buffer;
            NaughtsxCrossess game(&buffer);  // Pass the screen buffer to the game

            game.resetBoard();  // Reset the board to ensure it's empty

            // Test that the evaluation of an empty board is 0
            Assert::AreEqual(0, game.evaluate(), L"Empty board evaluation failed.");
        }

        TEST_METHOD(TestEvaluateRowVictory)
        {
            ScreenBuffer buffer;
            NaughtsxCrossess game(&buffer);  // Pass the screen buffer to the game

            // Place 'x' in row 1 (positions 1, 2, 3)
            game.getBoardValue(0, 0) = 'x';
game.getBoardValue(0, 1) = 'x';
game.getBoardValue(0, 2) = 'x';


            Assert::AreEqual(10, game.evaluate(), L"Row victory evaluation failed.");
        }

        TEST_METHOD(TestEvaluateColumnVictory)
        {
            ScreenBuffer buffer;
            NaughtsxCrossess game(&buffer);  // Pass the screen buffer to the game

            // Place 'o' in column 1 (positions 1, 4, 7)
            game.getBoardValue(0, 0) = 'o';
            game.getBoardValue(1, 0) = 'o';
            game.getBoardValue(2, 0) = 'o';

            Assert::AreEqual(-10, game.evaluate(), L"Column victory evaluation failed.");
        }

        TEST_METHOD(TestEvaluateDiagonalVictory)
        {
            ScreenBuffer buffer;
            NaughtsxCrossess game(&buffer);  // Pass the screen buffer to the game

            // Place 'x' in a diagonal (positions 1, 5, 9)
            game.getBoardValue(0, 0) = 'x';
            game.getBoardValue(1, 1) = 'x';
            game.getBoardValue(2, 2) = 'x';

            Assert::AreEqual(10, game.evaluate(), L"Diagonal victory evaluation failed.");
        }

        TEST_METHOD(TestFindBestMove)
        {
            ScreenBuffer buffer;
            NaughtsxCrossess game(&buffer);  // Pass the screen buffer to the game

            game.resetBoard();  // Reset the board to ensure it's empty

            // Place 'x' in positions 1 and 2
            game.getBoardValue(0, 0) = 'x';
            game.getBoardValue(0, 1) = 'x';

            auto bestMove = game.findBestMove(3);  // Find the best move with difficulty 3

            Assert::AreEqual(std::make_pair(0, 2), bestMove, L"Best move evaluation failed.");
        }

        TEST_METHOD(TestResetBoard)
        {
            ScreenBuffer buffer;
            NaughtsxCrossess game(&buffer);  // Pass the screen buffer to the game

            // Place some moves on the board
            game.getBoardValue(0, 0) = 'x';
            game.getBoardValue(1, 1) = 'o';
            game.getBoardValue(2, 2) = 'x';

            // Reset the board
            game.resetBoard();

            // Ensure the board is empty
            for (int row = 0; row < BOARD_SIZE; ++row) {
                for (int col = 0; col < BOARD_SIZE; ++col) {
                    Assert::AreEqual(' ', game.getBoardValue(row, col), L"Board reset failed.");
                }
            }
        }

        TEST_METHOD(TestRunMethodPvP) {
            // Create the screen buffer and game instance
            ScreenBuffer buffer;
            NaughtsxCrossess game(&buffer);

            // Simulated inputs for the two games (Player O goes first, Player X goes second)
            std::vector<std::string> simulatedInputs = {
                // Game 1: Player X wins in positions 1, 5, 9
                "4",  // Select PvP mode
                "1",  // Player O move (Position 1)
                "2",  // Player X move (Position 2)
                "5",  // Player O move (Position 5)
                "3",  // Player X move (Position 3)
                "9",  // Player O move (Position 9) -> Player O wins
                "y",  // Play again

                // Game 2: Player X wins in positions 1, 2, 3
                "4",  // Select PvP mode again
                "1",  // Player O move (Position 1)
                "4",  // Player X move (Position 4)
                "2",  // Player O move (Position 2)
                "5",  // Player X move (Position 5)
                "3",  // Player O move (Position 3) -> Player O wins
                "n"   // Don't play again, exit game
            };

            int inputIndex = 0;
            std::function<std::string()> inputProvider = [&simulatedInputs, &inputIndex]() {
                if (inputIndex < simulatedInputs.size()) {
                    return simulatedInputs[inputIndex++];
                }
                return std::string("stop");
                };

            // Run the game with simulated input
            game.run(inputProvider);

            // Check for the expected output after Player O wins in Game 1
            std::wstring expectedOwinMessage = L"Player O wins!";
            std::wstring screenOutputO = buffer.readScreenText(0, 8, expectedOwinMessage.length());
            Assert::AreEqual(expectedOwinMessage, screenOutputO, L"Game 1: Player O win message not displayed at correct position.");

            // Check for the expected output after Player X wins in Game 2
            std::wstring expectedXwinMessage = L"Player O wins!";
            std::wstring screenOutputX = buffer.readScreenText(0, 8, expectedXwinMessage.length());
            Assert::AreEqual(expectedXwinMessage, screenOutputX, L"Game 2: Player X win message not displayed at correct position.");
        }


    };

}


