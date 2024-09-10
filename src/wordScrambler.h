#ifndef WORDSCRAMBLER_H
#define WORDSCRAMBLER_H

#include <iostream>
#include <string>
#include <vector>
#include "ScreenBuffer.h"

/// @brief Class representing the Word Scrambler game.
class WordScrambler {
private:
    /// @brief ScreenBuffer pointer used to manage screen output (to allow external injection or internal creation).
    ScreenBuffer* screenBuffer;

    /// @brief If we create an internal ScreenBuffer, we need to manage its lifecycle.
    bool ownsScreenBuffer;

public:
    /// @brief Default constructor.
    WordScrambler();

    /// @brief Constructor that accepts an external ScreenBuffer.
    explicit WordScrambler(ScreenBuffer* buffer);

    /// @brief Destructor to clean up internal ScreenBuffer if we own it.
    ~WordScrambler();

    /// @brief Sets the ScreenBuffer to be used by the game.
    void setScreenBuffer(ScreenBuffer* buffer);

    /// @brief Clears the screen using the ScreenBuffer class.
    void clearScreen();

    /// @brief Retrieves a random word from a specified text file.
    /// @param filename The name of the file containing the words.
    /// @return A randomly selected word from the file.
    std::string getRandomWord(const std::string& filename);

    /// @brief Scrambles the characters in a given word.
    /// @param word The word to be scrambled.
    /// @return A scrambled version of the word.
    std::string scrambleWord(const std::string& word);

    /// @brief Converts a string to lowercase.
    /// @param str The string to be converted.
    /// @return The lowercase version of the string.
    std::string toLowerCase(const std::string& str);

    /// @brief Displays a hint with the first, middle, and last characters of the word.
    /// @param word The word for which the hint is generated.
    void displayHint(const std::string& word);

    /// @brief Main gameplay loop for the Word Scrambler game.
    /// @param difficulty The difficulty level selected by the player.
    void playWordScrambler(const std::string& difficulty);

    /// @brief Runs the Word Scrambler game.
    void run();
};

#endif // WORDSCRAMBLER_H
