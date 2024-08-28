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

        TEST_METHOD(TestClearScreen)
        {
            Hangman game;
            try {
                game.clearScreen();
                Assert::IsTrue(true);
            }
            catch (...) {
                Assert::Fail(L"clearScreen threw an exception.");
            }
        }

        TEST_METHOD(TestDisplayHangman)
        {
            Hangman game;
            try {
                for (int i = 0; i <= 5; ++i) {
                    game.displayHangman(i);
                }
                Assert::IsTrue(true);
            }
            catch (...) {
                Assert::Fail(L"displayHangman threw an exception.");
            }
        }

        TEST_METHOD(TestGetRandomWord)
        {
            Hangman game;
            std::ofstream testFile("test.txt");
            testFile << "apple\nbanana\ncherry";
            testFile.close();

            std::vector<std::string> possibleWords = { "apple", "banana", "cherry" };
            std::string word = game.getRandomWord("test.txt");

            Assert::IsTrue(std::find(possibleWords.begin(), possibleWords.end(), word) != possibleWords.end());
        }

        TEST_METHOD(TestIsYes)
        {
            Hangman game;
            Assert::IsTrue(game.isYes("yes"));
            Assert::IsTrue(game.isYes("y"));
            Assert::IsFalse(game.isYes("no"));
            Assert::IsFalse(game.isYes("n"));
        }

        TEST_METHOD(TestIsNo)
        {
            Hangman game;
            Assert::IsTrue(game.isNo("no"));
            Assert::IsTrue(game.isNo("n"));
            Assert::IsFalse(game.isNo("yes"));
            Assert::IsFalse(game.isNo("y"));
        }
    };
}
