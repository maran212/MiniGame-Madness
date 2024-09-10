#include "pch.h"
#include "CppUnitTest.h"
#include "../src/Hangman.h"
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
#include <fstream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace HangmanTests
{
    TEST_CLASS(HangmanTests)
    {
    public:

        // Test clearScreen method
        TEST_METHOD(TestClearScreen)
        {
            Hangman game;
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
            Hangman game;
            try {
                for (int i = 0; i <= 6; ++i) {  // Test all valid wrong guesses (0-6)
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
            Hangman game;
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
            Hangman game;
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
            Hangman game;
            Assert::IsTrue(game.isNo("no"));
            Assert::IsTrue(game.isNo("n"));
            Assert::IsTrue(game.isNo("NO"));
            Assert::IsTrue(game.isNo("N"));
            Assert::IsFalse(game.isNo("yes"));
            Assert::IsFalse(game.isNo("y"));
        }
    };
}
