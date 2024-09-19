#include "pch.h"
#include "CppUnitTest.h"
#include <algorithm> // For std::sort
#include <fstream>   // For std::ofstream
#include <sstream>   // For std::ostringstream
#include "../src/WordScrambler.h"
#include "../src/ScreenBuffer.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace WordScramblerTests
{
    TEST_CLASS(WordScramblerTests)
    {
    public:

        // Test the toLowerCase method
        TEST_METHOD(TestToLowerCase)
        {
            WordScrambler game;
            Assert::AreEqual(std::string("hello"), game.toLowerCase("Hello"), L"Failed on input 'Hello'");
            Assert::AreEqual(std::string("world"), game.toLowerCase("WORLD"), L"Failed on input 'WORLD'");
            Assert::AreEqual(std::string("test"), game.toLowerCase("TeSt"), L"Failed on input 'TeSt'");
            Assert::AreEqual(std::string("code"), game.toLowerCase("cOdE"), L"Failed on input 'cOdE'");
        }

        // Test scrambling of words
        TEST_METHOD(TestScrambleWord)
        {
            WordScrambler game;
            std::string word = "hello";
            std::string scrambled = game.scrambleWord(word);

            // Scrambled word should not match the original word.
            Assert::AreNotEqual(word, scrambled, L"Scrambled word should not match the original word.");

            // Both the scrambled and original word should have the same characters.
            std::sort(scrambled.begin(), scrambled.end());
            std::sort(word.begin(), word.end());
            Assert::AreEqual(word, scrambled, L"Scrambled word should contain the same letters as the original.");
        }

        // Test retrieving a random word from a file
        TEST_METHOD(TestGetRandomWord)
        {
            WordScrambler game;
            std::string filename = "testWords.txt";
            std::ofstream outFile(filename);
            outFile << "apple banana cherry date" << std::endl;
            outFile.close();

            std::string word = game.getRandomWord(filename);
            Assert::IsTrue(word == "apple" || word == "banana" || word == "cherry" || word == "date", L"getRandomWord returned an unexpected word.");
        }
        TEST_METHOD(TestDisplayHint)
        {
            // Create a single instance of ScreenBuffer
            ScreenBuffer buffer;

            // Pass the same buffer to WordScrambler
            WordScrambler game;
            game.setScreenBuffer(&buffer);

            // Set the screen buffer to active (optional, depending on implementation)
            buffer.setActive();

            // Set up a word for which a hint will be generated
            std::string word = "testing";

            // Call the displayHint method, which will write to the ScreenBuffer
            game.displayHint(word);

            // Use the readScreenText method to verify the written output
            // We assume the hint is written at row 5, starting from column 0
            std::wstring hintOutput = buffer.readScreenText(0, 5, 84);  // Read a long enough section

            // Expected hint output
            std::wstring expectedOutput = L"Hint: The first letter is 't', the middle letter is 't', and the last letter is 'g'.";

            // Check if the hint output matches the expected output
            Assert::AreEqual(expectedOutput, hintOutput.substr(0, expectedOutput.length()), L"displayHint output did not match expected output.");
        }

        // Test WordScrambler gameplay - ensuring the word scramble behaves as expected
        TEST_METHOD(TestPlayWordScramblerEasyMode)
        {
            // Create a WordScrambler instance
            WordScrambler game;

            // Simulate playing in easy mode
            std::string difficulty = "1"; // Easy mode

        }
    };
}
