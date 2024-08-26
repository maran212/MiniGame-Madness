#include "pch.h"
#include "../src/hangman.h"
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

// Assertion functions

bool assertEqual(const std::string& expected, const std::string& actual) {
    if (expected != actual) {
        throw std::runtime_error("Expected: " + expected + " | Actual: " + actual);
    }
    return expected == actual;
}

bool assertEqual(const int expected, const int actual) {
    if (expected != actual) {
        throw std::runtime_error("Expected: " + std::to_string(expected) + " | Actual: " + std::to_string(actual));
    }
    return expected == actual;
}

bool assertTrue(const bool actual) {
    if (!actual) {
        throw std::runtime_error("Expected: true | Actual: false");
    }
    return actual;
}

// Test functions

bool testClearScreen() {
    // This function clears the screen, so there's no direct return value to check.
    // A basic test could be to ensure it doesn't throw an error.
    try {
        clearScreen();
        return true;
    }
    catch (...) {
        return false;
    }
}

bool testDisplayHangman() {
    // Test with different wrongGuesses values to ensure it runs without error
    try {
        for (int i = 0; i <= 5; ++i) {
            displayHangman(i);
        }
        return true;
    }
    catch (...) {
        return false;
    }
}

bool testGetRandomWord() {
    // Create a test file with known words
    std::ofstream testFile("test.txt");
    testFile << "apple\nbanana\ncherry";
    testFile.close();

    std::vector<std::string> possibleWords = { "apple", "banana", "cherry" };
    std::string word = getRandomWord("test.txt");

    // Check if the returned word is in the possible words
    return assertTrue(std::find(possibleWords.begin(), possibleWords.end(), word) != possibleWords.end());
}

bool testIsYes() {
    return assertTrue(isYes("yes") && isYes("y") && !isYes("no") && !isYes("n"));
}

bool testIsNo() {
    return assertTrue(isNo("no") && isNo("n") && !isNo("yes") && !isNo("y"));
}

// Note: `playHangman` and `hangman` functions involve user input/output, making them difficult to unit test directly.
// One approach would be to refactor them for easier testing, but here we'll focus on the isolated functions.

int main() {
    int passed = 0;
    int total = 5;

    std::cout << "Running tests..." << std::endl;

    std::cout << "Test 1: ClearScreen" << std::endl;
    try {
        testClearScreen();
        passed++;
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
    }

    std::cout << "Test 2: DisplayHangman" << std::endl;
    try {
        testDisplayHangman();
        passed++;
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
    }

    std::cout << "Test 3: GetRandomWord" << std::endl;
    try {
        testGetRandomWord();
        passed++;
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
    }

    std::cout << "Test 4: IsYes" << std::endl;
    try {
        testIsYes();
        passed++;
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
    }

    std::cout << "Test 5: IsNo" << std::endl;
    try {
        testIsNo();
        passed++;
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
    }

    std::cout << "Passed " << passed << " of " << total << " tests" << std::endl;

    return 0;
}
