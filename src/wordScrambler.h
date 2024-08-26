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

using namespace std;

// Clears the screen based on the operating system
void clearScreen1();

// Retrieves a random word from a specified text file
string getRandomWord1(const string& filename);

// Scrambles the characters in a given word
string scrambleWord(const string& word);

// Converts a string to lowercase
string toLowerCase(const string& str);

// Displays a hint with the first, middle, and last characters of the word
void displayHint(const string& word);

// Main gameplay loop for the Word Scrambler game
void playWordScrambler(const string& difficulty);

// Test functions
void testToLowerCase();
void testScrambleWord();
void testGetRandomWord();
void testDisplayHint();

#endif // WORDSCRAMBLER_H
