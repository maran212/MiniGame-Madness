#ifndef HANGMAN_H
#define HANGMAN_H

#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <cstring>

using namespace std;

// Function to clear the screen
void clearScreen();

// Function to display the hangman figure based on the number of wrong guesses
void displayHangman(int wrongGuesses);

// Function to get a random word from a file based on the difficulty level
string getRandomWord(const string& filename);

// Function to play the Hangman game
void playHangman(const string& difficulty);

// Helper function to check if the response is a "yes"
bool isYes(const string& response);

// Helper function to check if the response is a "no"
bool isNo(const string& response);

// Function to run the Hangman game
void hangman();

#endif // HANGMAN_H

