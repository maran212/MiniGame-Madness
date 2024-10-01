// WordScramblerTests.cpp
#include "pch.h"
#include "CppUnitTest.h"
#include "../src/WordScrambler.h"
#include "../src/MockScreenBuffer.h"
#include <algorithm> // For std::find
#include <fstream> 

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace WordScramblerTests
{
    TEST_CLASS(WordScramblerGameplayTests)
    {
    public:

        // Test that the player wins the game when they guess the correct word
        TEST_METHOD(TestPlayWordScrambler_CorrectGuess)
        {
            // Create the "easy.txt" file with the word "apple"
            std::ofstream outFile("easy.txt");
            if (outFile.is_open()) {
                outFile << "apple\n";
                outFile.close();
            }
            else {
                Assert::Fail(L"Failed to create easy.txt file.");
            }

            // Create a mock screen buffer
            MockScreenBuffer mockScreenBuffer;

            // Simulate the correct guess
            mockScreenBuffer.inputQueue.push("apple");

            // Create a WordScrambler game with the mock screen buffer
            WordScrambler game(&mockScreenBuffer);

            // Run the playWordScrambler method with difficulty "testcode"
            try {
                game.playWordScrambler("testcode");

                // Verify that the congratulatory message is displayed
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
                std::string exMessage = ex.what();
                std::wstring errorMessage = L"Exception occurred during test execution: " + std::wstring(exMessage.begin(), exMessage.end());
                Assert::Fail(errorMessage.c_str());
            }

            // Clean up: delete the "easy.txt" file
            if (std::remove("easy.txt") != 0) {
                // Optionally handle error if needed
            }
        }

        // Test that the game responds correctly to an incorrect guess
        TEST_METHOD(TestPlayWordScrambler_IncorrectGuess)
        {
            // Create the "easy.txt" file with the word "apple"
            std::ofstream outFile("easy.txt");
            if (outFile.is_open()) {
                outFile << "apple\n";
                outFile.close();
            }
            else {
                Assert::Fail(L"Failed to create easy.txt file.");
            }

            // Create a mock screen buffer
            MockScreenBuffer mockScreenBuffer;

            // Simulate an incorrect guess
            mockScreenBuffer.inputQueue.push("banana");
            mockScreenBuffer.inputQueue.push("stop"); // To stop the game

            // Create a WordScrambler game with the mock screen buffer
            WordScrambler game(&mockScreenBuffer);

            // Run the playWordScrambler method with difficulty "testcode"
            try {
                game.playWordScrambler("testcode");

                // Verify that the incorrect message is displayed
                bool foundIncorrectMessage = false;
                for (const auto& output : mockScreenBuffer.outputs) {
                    if (output.find(L"Incorrect! Try again.") != std::wstring::npos) {
                        foundIncorrectMessage = true;
                        break;
                    }
                }
                Assert::IsTrue(foundIncorrectMessage, L"'Incorrect! Try again.' message was not found in outputs.");
            }
            catch (const std::exception& ex) {
                std::string exMessage = ex.what();
                std::wstring errorMessage = L"Exception occurred during test execution: " + std::wstring(exMessage.begin(), exMessage.end());
                Assert::Fail(errorMessage.c_str());
            }

            // Clean up: delete the "easy.txt" file
            if (std::remove("easy.txt") != 0) {
                // Optionally handle error if needed
            }
        }

        // Test that the hint functionality works correctly
        TEST_METHOD(TestPlayWordScrambler_DisplayHint)
        {
            // Create the "easy.txt" file with the word "apple"
            std::ofstream outFile("easy.txt");
            if (outFile.is_open()) {
                outFile << "apple\n";
                outFile.close();
            }
            else {
                Assert::Fail(L"Failed to create easy.txt file.");
            }

            // Create a mock screen buffer
            MockScreenBuffer mockScreenBuffer;

            // Simulate the user requesting a hint
            mockScreenBuffer.inputQueue.push("hint");
            mockScreenBuffer.inputQueue.push("y"); // Confirm to use the hint
            mockScreenBuffer.inputQueue.push("");  // Pause for user to continue (after hint is displayed)
            mockScreenBuffer.inputQueue.push("apple"); // Then guess the word

            // Create a WordScrambler game with the mock screen buffer
            WordScrambler game(&mockScreenBuffer);

            // Run the playWordScrambler method with difficulty "testcode"
            try {
                game.playWordScrambler("testcode");

                // Verify that the hint message is displayed
                bool foundHintMessage = false;
                for (const auto& output : mockScreenBuffer.outputs) {
                    if (output.find(L"Hint: The first letter is") != std::wstring::npos) {
                        foundHintMessage = true;
                        break;
                    }
                }
                Assert::IsTrue(foundHintMessage, L"Hint message was not found in outputs.");
            }
            catch (const std::exception& ex) {
                std::string exMessage = ex.what();
                std::wstring errorMessage = L"Exception occurred during test execution: " + std::wstring(exMessage.begin(), exMessage.end());
                Assert::Fail(errorMessage.c_str());
            }

            // Clean up: delete the "easy.txt" file
            if (std::remove("easy.txt") != 0) {
                // Optionally handle error if needed
            }
        }

        // Test that the player loses the game after maximum incorrect guesses
        TEST_METHOD(TestPlayWordScrambler_PlayerLoses)
        {
            // Create the "easy.txt" file with the word "apple"
            std::ofstream outFile("easy.txt");
            if (outFile.is_open()) {
                outFile << "apple\n";
                outFile.close();
            }
            else {
                Assert::Fail(L"Failed to create easy.txt file.");
            }

            // Create a mock screen buffer
            MockScreenBuffer mockScreenBuffer;

            // Simulate incorrect guesses until attempts run out
            for (int i = 0; i < 10; ++i) {
                mockScreenBuffer.inputQueue.push("banana"); // Wrong guess
            }

            // Create a WordScrambler game with the mock screen buffer
            WordScrambler game(&mockScreenBuffer);

            // Run the playWordScrambler method with difficulty "testcode"
            try {
                game.playWordScrambler("testcode");

                // Verify that the losing message is displayed
                bool foundLoseMessage = false;
                for (const auto& output : mockScreenBuffer.outputs) {
                    if (output.find(L"Sorry, you've run out of attempts. The word was: ") != std::wstring::npos) {
                        foundLoseMessage = true;
                        break;
                    }
                }
                Assert::IsTrue(foundLoseMessage, L"Losing message was not found in outputs.");
            }
            catch (const std::exception& ex) {
                std::string exMessage = ex.what();
                std::wstring errorMessage = L"Exception occurred during test execution: " + std::wstring(exMessage.begin(), exMessage.end());
                Assert::Fail(errorMessage.c_str());
            }

            // Clean up: delete the "easy.txt" file
            if (std::remove("easy.txt") != 0) {
                // Optionally handle error if needed
            }
        }

        // Test the scrambleWord method to ensure it scrambles the word correctly
        TEST_METHOD(TestScrambleWord)
        {
            WordScrambler game;
            std::string word = "apple";
            std::string scrambledWord = game.scrambleWord(word);

            // Since scrambling is random, the scrambled word may sometimes be the same as the original
            // So we can check that the scrambled word has the same letters as the original
            Assert::AreEqual(word.length(), scrambledWord.length(), L"Scrambled word has different length.");

            // Check that scrambled word is a permutation of the original word
            std::string sortedOriginal = word;
            std::string sortedScrambled = scrambledWord;
            std::sort(sortedOriginal.begin(), sortedOriginal.end());
            std::sort(sortedScrambled.begin(), sortedScrambled.end());

            Assert::AreEqual(sortedOriginal, sortedScrambled, L"Scrambled word is not a permutation of the original word.");
        }

        // Test the toLowerCase method
        TEST_METHOD(TestToLowerCase)
        {
            WordScrambler game;
            std::string input = "ApPlE";
            std::string lower = game.toLowerCase(input);

            Assert::AreEqual(std::string("apple"), lower, L"toLowerCase did not convert string correctly.");
        }

        // Test the getRandomWord method with a valid file
        TEST_METHOD(TestGetRandomWord)
        {
            // Create a temporary file with known words
            std::ofstream outFile("test_words.txt");
            if (outFile.is_open()) {
                outFile << "apple\nbanana\ncherry\n";
                outFile.close();
            }
            else {
                Assert::Fail(L"Failed to create test_words.txt file.");
            }

            WordScrambler game;
            std::string word = game.getRandomWord("test_words.txt");

            std::vector<std::string> possibleWords = { "apple", "banana", "cherry" };
            Assert::IsTrue(std::find(possibleWords.begin(), possibleWords.end(), word) != possibleWords.end(), L"getRandomWord did not return a word from the file.");

            // Clean up
            if (std::remove("test_words.txt") != 0) {
                // Optionally handle error if needed
            }
        }

        // Test the getRandomWord method when the file is not found
        TEST_METHOD(TestGetRandomWord_FileNotFound)
        {
            MockScreenBuffer mockScreenBuffer;
            WordScrambler game(&mockScreenBuffer);
            std::string word = game.getRandomWord("nonexistent_file.txt");

            Assert::AreEqual(std::string(""), word, L"getRandomWord should return empty string when file not found.");

            // Verify that the error message was displayed
            bool foundErrorMessage = false;
            for (const auto& output : mockScreenBuffer.outputs) {
                if (output.find(L"Error: Could not open file") != std::wstring::npos) {
                    foundErrorMessage = true;
                    break;
                }
            }
            Assert::IsTrue(foundErrorMessage, L"Error message was not found in outputs.");
        }

        // Test the getRandomWord method when the file is empty
        TEST_METHOD(TestGetRandomWord_EmptyFile)
        {
            // Create an empty file
            std::ofstream outFile("empty.txt");
            outFile.close();

            MockScreenBuffer mockScreenBuffer;
            WordScrambler game(&mockScreenBuffer);
            std::string word = game.getRandomWord("empty.txt");

            Assert::AreEqual(std::string(""), word, L"getRandomWord should return empty string when file is empty.");

            // Clean up
            if (std::remove("empty.txt") != 0) {
                // Optionally handle error if needed
            }
        }

        // Test the clearScreen method
        TEST_METHOD(TestClearScreen)
        {
            MockScreenBuffer mockScreenBuffer;
            WordScrambler game(&mockScreenBuffer);

            try {
                game.clearScreen();
                Assert::IsTrue(true);  // If no exceptions, the test passes
            }
            catch (...) {
                Assert::Fail(L"clearScreen threw an exception.");
            }
        }

        // Test the run method
        TEST_METHOD(TestRun)
        {
            // Create the "easy.txt" file with the word "apple"
            std::ofstream outFile("easy.txt");
            if (outFile.is_open()) {
                outFile << "apple\n";
                outFile.close();
            }
            else {
                Assert::Fail(L"Failed to create easy.txt file.");
            }

            MockScreenBuffer mockScreenBuffer;

            // Simulate user inputs
            mockScreenBuffer.inputQueue.push("testcode"); // Choose difficulty
            mockScreenBuffer.inputQueue.push("apple");    // Correct guess
            mockScreenBuffer.inputQueue.push("n");        // Do not play again

            WordScrambler game(&mockScreenBuffer);

            try {
                game.run();

                // Verify that the game displayed the winning message and exit message
                bool foundWinMessage = false;
                bool foundThanksMessage = false;
                for (const auto& output : mockScreenBuffer.outputs) {
                    if (output.find(L"Congratulations! You guessed the word: ") != std::wstring::npos) {
                        foundWinMessage = true;
                    }
                    if (output.find(L"Thanks for playing!") != std::wstring::npos) {
                        foundThanksMessage = true;
                    }
                }
                Assert::IsTrue(foundWinMessage, L"Winning message was not found in outputs.");
                Assert::IsTrue(foundThanksMessage, L"Exit message was not found in outputs.");
            }
            catch (const std::exception& ex) {
                std::string exMessage = ex.what();
                std::wstring errorMessage = L"Exception occurred during test execution: " + std::wstring(exMessage.begin(), exMessage.end());
                Assert::Fail(errorMessage.c_str());
            }

            // Clean up
            if (std::remove("easy.txt") != 0) {
                // Optionally handle error if needed
            }
        }

    };
}
