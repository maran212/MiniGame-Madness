#ifndef WORDSCRAMBLER_H
#define WORDSCRAMBLER_H

#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <limits>
#include <cctype>
#include <cassert>
#include <sstream>

/// @brief Class representing the Word Scrambler game.
class WordScrambler {
public:
    /// @brief Clears the screen based on the operating system.
    void clearScreen() const;

    /// @brief Retrieves a random word from a specified text file.
    /// @param filename The name of the file containing the words.
    /// @return A randomly selected word from the file.
    std::string getRandomWord(const std::string& filename) const;

    /// @brief Scrambles the characters in a given word.
    /// @param word The word to be scrambled.
    /// @return A scrambled version of the word.
    std::string scrambleWord(const std::string& word) const;

    /// @brief Converts a string to lowercase.
    /// @param str The string to be converted.
    /// @return The lowercase version of the string.
    std::string toLowerCase(const std::string& str) const;

    /// @brief Displays a hint with the first, middle, and last characters of the word.
    /// @param word The word for which the hint is generated.
    void displayHint(const std::string& word) const;

    /// @brief Main gameplay loop for the Word Scrambler game.
    /// @param difficulty The difficulty level selected by the player.
    void playWordScrambler(const std::string& difficulty);

    /// @brief Runs the Word Scrambler game.
    void run();

};

#endif // WORDSCRAMBLER_H
