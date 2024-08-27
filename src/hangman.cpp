#include "Hangman.h"

void Hangman::clearScreen() const {
    cout << '\033[2j';
}

void Hangman::displayHangman(int wrongGuesses) const {
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

std::string Hangman::getRandomWord(const std::string& filename) const {
    std::vector<std::string> words;
    std::ifstream file("../src/" + filename);

    if (!file.is_open()) {
        cerr << "Error: Could not open file " << filename << endl;
        return "";
    }

    std::string word;
    while (file >> word) {
        words.push_back(word);
    }
    file.close();

    if (words.empty()) {
        cerr << "Error: No words found in file " << filename << endl;
        return "";
    }

    srand(static_cast<unsigned int>(time(0)));
    int randomIndex = rand() % words.size();
    return words[randomIndex];
}

void Hangman::playHangman(const std::string& difficulty) {
    std::string filename;
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

    std::string word = getRandomWord(filename);
    std::string guessedWord(word.length(), '_');
    int wrongGuesses = 0;
    const int maxWrongGuesses = 6;
    std::vector<char> guessedLetters;

    while (wrongGuesses < maxWrongGuesses && guessedWord != word) {
        clearScreen(); // Clear the screen

        cout << "Guessed word: " << guessedWord << endl;
        displayHangman(wrongGuesses);
        cout << "Guess a letter (or type 'stop' to exit): ";
        std::string input;
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
        }
        else if (find(guessedLetters.begin(), guessedLetters.end(), guess) != guessedLetters.end()) {
            cout << "You already guessed that letter!" << endl;
            validInput = false;
        }

        if (!validInput) {
            cout << "Press Enter to continue...";
            cin.ignore();
            cin.get();
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
    }
    else {
        displayHangman(5);
        cout << "Sorry, you lost. The word was: " << word << endl;
    }
}

bool Hangman::isYes(const std::string& response) const {
    return response == "y" || response == "Y" || response == "yes" || response == "YES";
}

bool Hangman::isNo(const std::string& response) const {
    return response == "n" || response == "N" || response == "no" || response == "NO";
}

void Hangman::hangman() {
    std::string playAgain;

    do {
        clearScreen(); // Clear the screen at the start of each game
        cout << "Choose difficulty (1:easy, 2:medium, 3:hard) or type 'stop' to exit: ";
        std::string difficulty;
        cin >> difficulty;

        if (difficulty == "stop") {
            cout << "Game stopped. Exiting..." << endl;
            return;
        }

        playHangman(difficulty);

        cout << "Do you want to play again? (y/n or type 'stop' to exit): ";
        cin >> playAgain;

        if (playAgain == "stop") {
            cout << "Game stopped. Exiting..." << endl;
            return;
        }

    } while (isYes(playAgain));

    cout << "Thanks for playing!" << endl;
}
