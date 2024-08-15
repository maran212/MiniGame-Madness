#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <cstring> // For std::strcmp

using namespace std;

void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void displayHangman(int wrongGuesses) {
    string hangmanArt[] = {
        "  +---+\n      |\n      |\n      |\n     ===",
        "  +---+\n  O   |\n      |\n      |\n     ===",
        "  +---+\n  O   |\n  |   |\n      |\n     ===",
        "  +---+\n  O   |\n /|\\  |\n      |\n     ===",
        "  +---+\n  O   |\n /|\\  |\n /    |\n     ===",
        "  +---+\n  O   |\n /|\\  |\n / \\  |\n     ==="
    };
    if (wrongGuesses >= 0 && wrongGuesses < 7) {
        cout << hangmanArt[wrongGuesses] << endl;
    }
}

string getRandomWord(const string& filename) {
    vector<string> words;
    ifstream file(filename);
    string word;
    while (file >> word) {
        words.push_back(word);
    }
    file.close();
    srand(time(0));
    int randomIndex = rand() % words.size();
    return words[randomIndex];
}

void playHangman(const string& difficulty) {
    string filename;
    if (difficulty == "1" || difficulty == "easy") {
        filename = "easy.txt";
    } else if (difficulty == "2" || difficulty == "medium") {
        filename = "medium.txt";
    } else if (difficulty == "3" || difficulty == "hard") {
        filename = "hard.txt";
    } else {
        cout << "Invalid difficulty level. Exiting game." << endl;
        return;
    }
string word = getRandomWord(filename);
    string guessedWord(word.length(), '_');
    int wrongGuesses = 0;
    const int maxWrongGuesses = 6;
    vector<char> guessedLetters;

    while (wrongGuesses < maxWrongGuesses && guessedWord != word) {
        clearScreen(); // Clear the screen

        cout << "Guessed word: " << guessedWord << endl;
        displayHangman(wrongGuesses);
        cout << "Guess a letter (or type 'stop' to exit): ";
        string input;
        cin >> input;

        if (input == "stop") {
            cout << "Game stopped. Exiting..." << endl;
            return;
        }

        char guess = input[0];
        bool validInput = true;

        if (input.length() != 1 || !isalpha(guess)) {
            cout << "Invalid input. Please enter a single letter." << endl;
            validInput = false;
        } else if (find(guessedLetters.begin(), guessedLetters.end(), guess) != guessedLetters.end()) {
            cout << "You already guessed that letter!" << endl;
            validInput = false;
        }

        if (!validInput) {
            // Wait for user to acknowledge the message
            cout << "Press Enter to continue...";
            cin.ignore(); // Ignore any leftover newline characters
            cin.get(); // Wait for Enter key press
            continue;
        }

        guessedLetters.push_back(guess);
        bool correctGuess = false;
        for (size_t i = 0; i < word.length(); ++i) {
            if (word[i] == guess) {
                guessedWord[i] = guess;
                correctGuess = true;
            }
        }

        if (!correctGuess) {
            ++wrongGuesses;
        }
    }

    clearScreen(); // Clear the screen before ending the game
    if (guessedWord == word) {
        cout << "Congratulations! You guessed the word: " << word << endl;
    } else {
        displayHangman(5);
        cout << "Sorry, you lost. The word was: " << word << endl;
    }
}


bool isYes(const string& response) {
    return response == "y" || response == "Y" || response == "yes" || response == "YES";
}

bool isNo(const string& response) {
    return response == "n" || response == "N" || response == "no" || response == "NO";
}

void hangman() {
    string playAgain;

    do {
        clearScreen(); // Clear the screen at the start of each game
        cout << "Choose difficulty (1:easy, 2:medium, 3:hard) or type 'stop' to exit: ";
        string difficulty;
        cin >> difficulty;

        if (difficulty == "stop") {
            cout << "Game stopped. Exiting..." << endl;
        }

        playHangman(difficulty);

        cout << "Do you want to play again? (y/n or type 'stop' to exit): ";
        cin >> playAgain;

        if (playAgain == "stop") {
            cout << "Game stopped. Exiting..." << endl;
        }

    } while (isYes(playAgain));

    cout << "Thanks for playing!" << endl;
}
