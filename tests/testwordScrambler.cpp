#include "pch.h"
#include "CppUnitTest.h"
#include <algorithm> // For std::sort
#include <fstream>   // For std::ofstream
#include <sstream>   // For std::ostringstream
#include "../src/WordScrambler.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace WordScramblerTests
{
    TEST_CLASS(WordScramblerTests)
    {
    public:
        TEST_METHOD(TestToLowerCase)
        {
            WordScrambler game;
            Assert::AreEqual(std::string("hello"), game.toLowerCase("Hello"), L"Failed on input 'Hello'");
            Assert::AreEqual(std::string("world"), game.toLowerCase("WORLD"), L"Failed on input 'WORLD'");
            Assert::AreEqual(std::string("test"), game.toLowerCase("TeSt"), L"Failed on input 'TeSt'");
            Assert::AreEqual(std::string("code"), game.toLowerCase("cOdE"), L"Failed on input 'cOdE'");
        }

        TEST_METHOD(TestScrambleWord)
        {
            WordScrambler game;
            std::string word = "hello";
            std::string scrambled = game.scrambleWord(word);

            Assert::AreNotEqual(word, scrambled, L"Scrambled word should not match the original word.");

            std::sort(scrambled.begin(), scrambled.end());
            std::sort(word.begin(), word.end());
            Assert::AreEqual(word, scrambled, L"Scrambled word should contain the same letters as the original.");
        }

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
            WordScrambler game;
            std::string word = "testing";

            std::ostringstream output;
            std::streambuf* oldCoutBuffer = std::cout.rdbuf(output.rdbuf());

            game.displayHint(word);

            std::cout.rdbuf(oldCoutBuffer);

            std::string expectedOutput = "Hint: The first letter is 't', the middle letter is 't', and the last letter is 'g'.\n";
            Assert::AreEqual(expectedOutput, output.str(), L"displayHint output did not match expected output.");
        }
    };
}
