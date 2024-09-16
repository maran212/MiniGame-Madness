#include "Hangman.h"
#include <cctype>  // For std::tolower
#include <thread>  // For sleep
#include <chrono>  // For setting sleep duration

void Hangman::clearScreen() {
    screenBuffer->clearScreen(); // Use ScreenBuffer to clear the screen
}

void Hangman::displayHangman(int wrongGuesses) {
    std::wstring hangmanArt[] = {
        L"  +---+\n      |\n      |\n      |\n     ===",
        L"  +---+\n  O   |\n      |\n      |\n     ===",
        L"  +---+\n  O   |\n  |   |\n      |\n     ===",
        L"  +---+\n  O   |\n /|\\  |\n      |\n     ===",
        L"  +---+\n  O   |\n /|\\  |\n /    |\n     ===",
        L"  +---+\n  O   |\n /|\\  |\n / \\  |\n     ==="
    };
    if (wrongGuesses >= 0 && wrongGuesses < 7) {
        screenBuffer->writeToScreen(0, 2, hangmanArt[wrongGuesses]); // Output hangman art starting from row 2
    }
}

std::string Hangman::getRandomWord(const std::string& filename) {
    std::vector<std::string> words;
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::wstring errorMessage = L"Error: Could not open file " + std::wstring(filename.begin(), filename.end());
        screenBuffer->writeToScreen(0, 0, errorMessage);
        return "";
    }

    std::string word;
    while (file >> word) {
        words.push_back(word);
    }
    file.close();

    if (words.empty()) {
        std::wstring errorMessage = L"Error: No words found in file " + std::wstring(filename.begin(), filename.end());
        screenBuffer->writeToScreen(0, 0, errorMessage);
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
        screenBuffer->writeToScreen(0, 0, L"Invalid difficulty level. Exiting game.");
        return;
    }

    std::string word = getRandomWord(filename);
    std::string guessedWord(word.length(), '_');
    int wrongGuesses = 0;
    const int maxWrongGuesses = 6;
    std::vector<char> guessedLetters;

    screenBuffer->writeToScreen(0, 1, L"The word to guess is: " + std::wstring(word.begin(), word.end()));  // For testing, will remove later
    //screenBuffer->getBlockingInput();  // Pause for testing

    while (wrongGuesses < maxWrongGuesses && guessedWord != word) {
        clearScreen();

        // Display the current guessed word (with guessed letters in place)
        screenBuffer->writeToScreen(0, 0, std::wstring(guessedWord.begin(), guessedWord.end()));

        // Display hangman figure
        displayHangman(wrongGuesses);

        screenBuffer->writeToScreen(0, 8, L"Guess a letter (or type 'stop' to exit): ");
        std::string input = screenBuffer->getBlockingInput();

        if (input == "stop") {
            screenBuffer->writeToScreen(0, 9, L"Game stopped. Exiting...");
            return;
        }

        // Convert the guess to lowercase for case-insensitive comparison
        char guess = std::tolower(input[0]);
        bool validInput = true;

        if (input.length() != 1 || !isalpha(guess)) {
            screenBuffer->writeToScreen(0, 9, L"Invalid input. Please enter a single letter.");
            validInput = false;
        }
        else if (find(guessedLetters.begin(), guessedLetters.end(), guess) != guessedLetters.end()) {
            screenBuffer->writeToScreen(0, 9, L"You already guessed that letter!");
            validInput = false;
        }

        if (!validInput) {
            screenBuffer->writeToScreen(0, 10, L"Invalid guess, try again.");
            std::this_thread::sleep_for(std::chrono::milliseconds(700));  // Pause for 1.5 seconds
            continue;
        }

        guessedLetters.push_back(guess);
        bool correctGuess = false;

        // Update guessed word based on the current guess, handling case-insensitive matching
        for (size_t i = 0; i < word.length(); ++i) {
            if (std::tolower(word[i]) == guess) {
                guessedWord[i] = word[i];  // Keep the original case of the word
                correctGuess = true;
            }
        }

        // Display feedback to the user
        if (correctGuess) {
            screenBuffer->writeToScreen(0, 9, L"Correct guess!");
        }
        else {
            screenBuffer->writeToScreen(0, 9, L"Wrong guess!");
        }

        // Pause for 1.5 seconds before continuing
        std::this_thread::sleep_for(std::chrono::milliseconds(700));

        if (!correctGuess) {
            ++wrongGuesses;
        }
    }

    clearScreen();
    if (guessedWord == word) {
        screenBuffer->writeToScreen(0, 0, L"Congratulations! You guessed the word: " + std::wstring(word.begin(), word.end()));
    }
    else {
        displayHangman(5);
        screenBuffer->writeToScreen(0, 7, L"Sorry, you lost. The word was: " + std::wstring(word.begin(), word.end()));
    }
}

bool Hangman::isYes(const std::string& response) {
    return response == "y" || response == "Y" || response == "yes" || response == "YES";
}

bool Hangman::isNo(const std::string& response) {
    return response == "n" || response == "N" || response == "no" || response == "NO";
}

void Hangman::hangman() {
    screenBuffer->setActive();
    std::string playAgain;

    do {
        clearScreen();
        screenBuffer->writeToScreen(0, 0, L"Choose difficulty (1:easy, 2:medium, 3:hard) or type 'stop' to exit: ");
        std::string difficulty = screenBuffer->getBlockingInput();

        if (difficulty == "stop") {
            screenBuffer->writeToScreen(0, 1, L"Game stopped. Exiting...");
            return;
        }

        playHangman(difficulty);

        screenBuffer->writeToScreen(0, 12, L"Do you want to play again? (y/n or type 'stop' to exit): ");
        playAgain = screenBuffer->getBlockingInput();

        if (playAgain == "stop") {
            screenBuffer->writeToScreen(0, 13, L"Game stopped. Exiting...");
            return;
        }

    } while (isYes(playAgain));

    screenBuffer->writeToScreen(0, 14, L"Thanks for playing!");
}
