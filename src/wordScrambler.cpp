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
//#include <wordScrambler.h>

using namespace std;

// Clears the screen based on the operating system
void clearScreen1() {
    cout << '\033[2j';
}

// Retrieves a random word from a specified text file
string getRandomWord1(const string& filename) {
    vector<string> words;
    ifstream file(filename);
    string word;

    // Reads all words from the file and stores them in a vector
    while (file >> word) {
        words.push_back(word);
    }
    file.close();

    // Seed the random number generator and select a random word
    srand(static_cast<unsigned int>(time(0)));
    int randomIndex = rand() % words.size();
    return words[randomIndex];
}

// Scrambles the characters in a given word
string scrambleWord(const string& word) {
    string scrambled = word;
    random_shuffle(scrambled.begin(), scrambled.end());  // Randomly shuffle the characters
    return scrambled;
}

// Converts a string to lowercase
string toLowerCase(const string& str) {
    string lowerStr = str;
    // Transform each character to its lowercase equivalent
    transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), ::tolower);
    return lowerStr;
}

// Displays a hint with the first, middle, and last characters of the word
void displayHint(const string& word) {
    int length = word.length();
    char firstChar = word[0];
    char middleChar = word[length / 2];
    char lastChar = word[length - 1];

    // Display the hint to the player
    cout << "Hint: The first letter is '" << firstChar << "', the middle letter is '" << middleChar << "', and the last letter is '" << lastChar << "'." << endl;
}

// Main gameplay loop for the Word Scrambler game
void playWordScrambler(const string& difficulty) {
    const int maxGuesses = 10; // Fixed number of guesses
    string filename;

    // Determine the file to load based on the chosen difficulty
    if (difficulty == "1" || difficulty == "easy") {
        filename = "easy.txt";
    }
    else if (difficulty == "2" || difficulty == "medium") {
        filename = "medium.txt";
    }
    else if (difficulty == "3" || difficulty == "hard") {
        filename = "hard.txt";
    }
    else {
        cout << "Invalid difficulty level. Exiting game." << endl;
        return;
    }

    string word = getRandomWord1(filename);  // Get a random word from the selected file
    string scrambledWord = scrambleWord(word);  // Scramble the word
    string guess;
    bool guessedCorrectly = false;
    int attempts = 0;

    // Game loop: continues until the player guesses correctly or runs out of attempts
    while (attempts < maxGuesses && !guessedCorrectly) {
        clearScreen1();
        cout << "Scrambled word: " << scrambledWord << endl;
        cout << "Guess the word (or type 'stop' to exit, or 'hint' for a hint that costs 2 lives): ";
        cin >> guess;

        // If the player types 'stop', end the game
        if (guess == "stop") {
            cout << "Game stopped. Exiting..." << endl;
            return;
        }
        // If the player requests a hint
        else if (guess == "hint") {
            cout << "Are you sure? You will lose 2 lives (y/n): ";
            string response;
            cin >> response;
            // If the player confirms the hint
            if (response == "y" || response == "Y") {
                displayHint(word);  // Display the hint
                attempts += 2;  // Deduct 2 lives
                if (attempts >= maxGuesses) {
                    break;  // If lives run out, exit the loop
                }
            }
            cout << "Press Enter to continue...";
            cin.ignore(); // Ignore any leftover newline characters
            cin.get(); // Wait for Enter key press
            continue;
        }

        // Compare the player's guess to the actual word, ignoring case
        if (toLowerCase(guess) == toLowerCase(word)) {
            guessedCorrectly = true;
        }
        else {
            cout << "Incorrect! Try again." << endl;
            attempts++;  // Increment the number of attempts
            cout << "Attempts left: " << maxGuesses - attempts << endl;
            cout << "Press Enter to continue...";
            cin.ignore(); // Ignore any leftover newline characters
            cin.get(); // Wait for Enter key press
        }
    }

    clearScreen1();
    // If the player guesses the word correctly
    if (guessedCorrectly) {
        cout << "Congratulations! You guessed the word: " << word << endl;
    }
    else {
        // If the player runs out of attempts
        cout << "Sorry, you've run out of attempts. The word was: " << word << endl;
    }
}

// Test functions
void testToLowerCase() {
    assert(toLowerCase("Hello") == "hello");
    assert(toLowerCase("WORLD") == "world");
    assert(toLowerCase("TeSt") == "test");
    assert(toLowerCase("cOdE") == "code");
    cout << "toLowerCase() passed all tests!" << endl;
}

void testScrambleWord() {
    string word = "hello";
    string scrambled = scrambleWord(word);
    // Check that scrambled word is not the same as the original but contains the same letters
    assert(scrambled != word);
    sort(scrambled.begin(), scrambled.end());
    sort(word.begin(), word.end());
    assert(scrambled == word);
    cout << "scrambleWord() passed all tests!" << endl;
}

void testGetRandomWord() {
    string filename = "testWords.txt";
    ofstream outFile(filename);
    outFile << "apple banana cherry date" << endl;
    outFile.close();

    string word = getRandomWord1(filename);
    assert(word == "apple" || word == "banana" || word == "cherry" || word == "date");
    cout << "getRandomWord() passed all tests!" << endl;
}

void testDisplayHint() {
    string word = "testing";

    // Redirect output to a string stream
    ostringstream output;
    streambuf* oldCoutBuffer = cout.rdbuf(output.rdbuf());  // Redirect cout to output

    displayHint(word);  // Call the function to generate the hint output

    cout.rdbuf(oldCoutBuffer);  // Restore cout to its original buffer

    string expectedOutput = "Hint: The first letter is 't', the middle letter is 't', and the last letter is 'g'.\n";
    assert(output.str() == expectedOutput);  // Check if the generated output matches the expected string
    cout << "displayHint() passed the test!" << endl;
}

// Main function that can run either the game or tests based on the argument
int wordScrambler(int argc, char* argv[]) {
    if (argc > 1 && string(argv[1]) == "test") {
        // Run tests if "test" argument is provided
        testToLowerCase();
        testScrambleWord();
        testGetRandomWord();
        testDisplayHint();
        cout << "All tests passed!" << endl;
    }
    else {
        // Run the game if no argument or a different argument is provided
        string playAgain;

        do {
            clearScreen1(); // Clear the screen at the start of each game
            cout << "Choose difficulty (1: easy, 2: medium, 3: hard) or type 'stop' to exit: ";
            string difficulty;
            cin >> difficulty;

            // If the player types 'stop', end the program
            if (difficulty == "stop") {
                cout << "Game stopped. Exiting..." << endl;
                return 0;
            }

            // Start the game with the chosen difficulty
            playWordScrambler(difficulty);

            // Ask if the player wants to play again
            cout << "Do you want to play again? (y/n or type 'stop' to exit): ";
            cin >> playAgain;

            // If the player types 'stop', end the program
            if (playAgain == "stop") {
                cout << "Game stopped. Exiting..." << endl;
                return 0;
            }

        } while (playAgain == "y" || playAgain == "Y");  // Loop if the player wants to play again

        cout << "Thanks for playing!" << endl;
    }

    return 0;
}