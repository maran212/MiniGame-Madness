// In your test file
#include "pch.h"
#include "CppUnitTest.h"
#include "../src/Hangman.h"
#include "../src/MockScreenBuffer.h"
#include <algorithm> // For std::find

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace HangmanTests
{
    TEST_CLASS(HangmanGameplayTests)
    {
    public:
        TEST_METHOD(TestPlayHangman_IncorrectGuess)
        {
            // Create the "easy.txt" file with the word "banana"
            std::ofstream outFile("easy.txt");
            if (outFile.is_open()) {
                outFile << "banana\n";
                outFile.close();
            }
            else {
                Assert::Fail(L"Failed to create easy.txt file.");
            }

            // Create a mock screen buffer
            MockScreenBuffer mockScreenBuffer;

            // Simulate an incorrect guess
            mockScreenBuffer.inputQueue.push("x");
            mockScreenBuffer.inputQueue.push("stop"); // Stop the game after one guess

            // Create a Hangman game with the mock screen buffer
            Hangman game(&mockScreenBuffer);

            try {
                // Run the playHangman method
                game.playHangman("testcode");

                // Verify that the incorrect guess message is displayed
                bool foundIncorrectGuess = false;
                for (const auto& output : mockScreenBuffer.outputs) {
                    if (output.find(L"Wrong guess!") != std::wstring::npos) {
                        foundIncorrectGuess = true;
                        break;
                    }
                }
                Assert::IsTrue(foundIncorrectGuess, L"'Wrong guess!' message was not found in outputs.");
            }
            catch (const std::exception& ex) {
                Assert::Fail(L"Exception occurred during test execution.");
            }

            // Clean up: delete the "easy.txt" file
            if (std::remove("easy.txt") != 0) {
                // Optionally handle error if needed
            }
        }

        TEST_METHOD(TestPlayHangman_CorrectGuess)
        {
            // Create the "easy.txt" file with the word "banana"
            std::ofstream outFile("easy.txt");
            if (outFile.is_open()) {
                outFile << "banana\n";
                outFile.close();
            }
            else {
                Assert::Fail(L"Failed to create easy.txt file.");
            }

            // Create a mock screen buffer
            MockScreenBuffer mockScreenBuffer;

            // Simulate a correct guess
            mockScreenBuffer.inputQueue.push("b");
            mockScreenBuffer.inputQueue.push("stop"); // Stop the game after one guess

            // Create a Hangman game with the mock screen buffer
            Hangman game(&mockScreenBuffer);

            try {
                // Run the playHangman method
                game.playHangman("testcode");

                // Verify that the correct guess message is displayed
                bool foundCorrectGuess = false;
                for (const auto& output : mockScreenBuffer.outputs) {
                    if (output.find(L"Correct guess!") != std::wstring::npos) {
                        foundCorrectGuess = true;
                        break;
                    }
                }
                Assert::IsTrue(foundCorrectGuess, L"'Correct guess!' message was not found in outputs.");
            }
            catch (const std::exception& ex) {
                Assert::Fail(L"Exception occurred during test execution.");
            }

            // Clean up: delete the "easy.txt" file
            if (std::remove("easy.txt") != 0) {
                // Optionally handle error if needed
            }
        }

        TEST_METHOD(TestPlayHangman_PlayerLoses)
        {
            // Create the "easy.txt" file with the word "banana"
            std::ofstream outFile("easy.txt");
            if (outFile.is_open()) {
                outFile << "banana\n";
                outFile.close();
            }
            else {
                Assert::Fail(L"Failed to create easy.txt file.");
            }

            // Create a mock screen buffer
            MockScreenBuffer mockScreenBuffer;

            // Simulate incorrect guesses to reach maximum wrong guesses
            mockScreenBuffer.inputQueue.push("x");
            mockScreenBuffer.inputQueue.push("y");
            mockScreenBuffer.inputQueue.push("z");
            mockScreenBuffer.inputQueue.push("q");
            mockScreenBuffer.inputQueue.push("w");
            mockScreenBuffer.inputQueue.push("e"); // 6 wrong guesses

            // Create a Hangman game with the mock screen buffer
            Hangman game(&mockScreenBuffer);

            try {
                // Run the playHangman method with difficulty "1"
                game.playHangman("testcode");

                // Verify that the losing message is displayed
                bool foundLoseMessage = false;
                for (const auto& output : mockScreenBuffer.outputs) {
                    if (output.find(L"Sorry, you lost. The word was: ") != std::wstring::npos) {
                        foundLoseMessage = true;
                        break;
                    }
                }
                Assert::IsTrue(foundLoseMessage, L"Losing message was not found in outputs.");
            }
            catch (const std::exception& ex) {
                Assert::Fail(L"Exception occurred during test execution.");
            }

            // Clean up: delete the "easy.txt" file
            if (std::remove("easy.txt") != 0) {
                // Optionally handle error if needed
            }
        }

        TEST_METHOD(TestPlayHangman_PlayerWins)
        {
            // Create the "easy.txt" file with the word "banana"
            std::ofstream outFile("easy.txt");
            if (outFile.is_open()) {
                outFile << "banana\n";
                outFile.close();
            }
            else {
                Assert::Fail(L"Failed to create easy.txt file.");
            }

            // Create a mock screen buffer
            MockScreenBuffer mockScreenBuffer;

            // Simulate user inputs for winning the game
            mockScreenBuffer.inputQueue.push("b");
            mockScreenBuffer.inputQueue.push("a");
            mockScreenBuffer.inputQueue.push("n");

            // Create a Hangman game with the mock screen buffer
            Hangman game(&mockScreenBuffer);

            try {
                // Run the playHangman method with difficulty "1"
                game.playHangman("testcode");

                // Verify that the winning message is displayed
                bool foundWinMessage = false;
                for (const auto& output : mockScreenBuffer.outputs) {
                    if (output.find(L"Congratulations! You guessed the word: ") != std::wstring::npos) {
                        foundWinMessage = true;
                        break;
                    }
                }
                Assert::IsTrue(foundWinMessage, L"Winning message was not found in outputs.");
            }
            catch (const std::exception& ex) {
                Assert::Fail(L"Exception occurred during test execution.");
            }

            // Clean up: delete the "easy.txt" file
            if (std::remove("easy.txt") != 0) {
                // Optionally handle error if needed
            }
        }



        // Test the hangman method
        TEST_METHOD(TestHangman)
        {

            // Create the "easy.txt" file with the word "banana"
            std::ofstream outFile("easy.txt");
            if (outFile.is_open()) {
                outFile << "banana\n";
                outFile.close();
            }
            else {
                Assert::Fail(L"Failed to create easy.txt file.");
            }

            // Create a mock screen buffer
            MockScreenBuffer mockScreenBuffer;

            // Simulate user inputs
            mockScreenBuffer.inputQueue.push("testcode");    // Choose difficulty
            mockScreenBuffer.inputQueue.push("a");    // First guess
            mockScreenBuffer.inputQueue.push("stop"); // Exit the game
            mockScreenBuffer.inputQueue.push("n");    // Do not play again

            // Create a Hangman game with the mock screen buffer
            Hangman game(&mockScreenBuffer);

            // Run the hangman method
            game.hangman();

            // Verify that the game stopped as expected
            bool foundExitMessage = false;
            for (const auto& output : mockScreenBuffer.outputs) {
                if (output.find(L"Game stopped. Exiting...") != std::wstring::npos) {
                    foundExitMessage = true;
                    break;
                }
            }
            Assert::IsTrue(foundExitMessage, L"Expected exit message was not found in outputs.");
        }

        // Test clearScreen method
        TEST_METHOD(TestClearScreen)
        {
            MockScreenBuffer mockScreenBuffer;
            Hangman game(&mockScreenBuffer);

            try {
                game.clearScreen();
                Assert::IsTrue(true);  // If no exceptions, the test passes
            }
            catch (...) {
                Assert::Fail(L"clearScreen threw an exception.");
            }
        }

        // Test displayHangman method with valid wrong guess counts
        TEST_METHOD(TestDisplayHangman)
        {
            MockScreenBuffer mockScreenBuffer;
            Hangman game(&mockScreenBuffer);
            try {
                for (int i = 0; i < 6; ++i) {  // Test all valid wrong guesses (0-6)
                    game.displayHangman(i);
                }
                Assert::IsTrue(true);  // If no exceptions, the test passes
            }
            catch (...) {
                Assert::Fail(L"displayHangman threw an exception.");
            }
        }

        // Test getRandomWord method by creating a temporary file and reading from it
        TEST_METHOD(TestGetRandomWord)
        {
            MockScreenBuffer mockScreenBuffer;
            Hangman game(&mockScreenBuffer);
            std::string filePath = "test.txt";
            std::ofstream testFile(filePath);
            testFile << "apple\nbanana\ncherry";
            testFile.close();

            std::vector<std::string> possibleWords = { "apple", "banana", "cherry" };
            std::string word = game.getRandomWord(filePath);

            Assert::IsTrue(std::find(possibleWords.begin(), possibleWords.end(), word) != possibleWords.end());

            // Clean up the test file
            remove(filePath.c_str());
        }

        // Test isYes method for valid and invalid responses
        TEST_METHOD(TestIsYes)
        {
            MockScreenBuffer mockScreenBuffer;
            Hangman game(&mockScreenBuffer);
            Assert::IsTrue(game.isYes("yes"));
            Assert::IsTrue(game.isYes("y"));
            Assert::IsTrue(game.isYes("YES"));
            Assert::IsTrue(game.isYes("Y"));
            Assert::IsFalse(game.isYes("no"));
            Assert::IsFalse(game.isYes("n"));
        }

        // Test isNo method for valid and invalid responses
        TEST_METHOD(TestIsNo)
        {
            MockScreenBuffer mockScreenBuffer;
            Hangman game(&mockScreenBuffer);
            Assert::IsTrue(game.isNo("no"));
            Assert::IsTrue(game.isNo("n"));
            Assert::IsTrue(game.isNo("NO"));
            Assert::IsTrue(game.isNo("N"));
            Assert::IsFalse(game.isNo("yes"));
            Assert::IsFalse(game.isNo("y"));
        }


    };
}
