#include "WordScrambler.h"
#include <fstream>
#include <algorithm>
#include <random>

// Default constructor, initializes its own ScreenBuffer
WordScrambler::WordScrambler() : screenBuffer(nullptr), ownsScreenBuffer(true) {
    screenBuffer = new RealScreenBuffer();  // Create a new RealScreenBuffer
}

// Constructor that accepts an external IScreenBuffer
WordScrambler::WordScrambler(IScreenBuffer* buffer) : screenBuffer(buffer), ownsScreenBuffer(false) {}

// Destructor to clean up internal ScreenBuffer if owned
WordScrambler::~WordScrambler() {
    if (ownsScreenBuffer && screenBuffer) {
        delete screenBuffer;
        screenBuffer = nullptr;
    }
}

// Method to set external IScreenBuffer
void WordScrambler::setScreenBuffer(IScreenBuffer* buffer) {
    if (ownsScreenBuffer && screenBuffer) {
        delete screenBuffer;  // Clean up internal buffer if we are replacing it
    }
    screenBuffer = buffer;
    ownsScreenBuffer = false;  // External buffer means we don't own it
}

void WordScrambler::clearScreen() {
    if (screenBuffer) {
        screenBuffer->clearScreen();
    }
}

std::string WordScrambler::getRandomWord(const std::string& filename) {
    std::vector<std::string> words;
    std::ifstream file(filename);
    if (!file.is_open()) {
        if (screenBuffer) {
            screenBuffer->writeToScreen(0, 0, L"Error: Could not open file");
        }
        return "";
    }

    std::string word;
    while (file >> word) {
        words.push_back(word);
    }
    file.close();

    if (words.empty()) {
        if (screenBuffer) {
            screenBuffer->writeToScreen(0, 0, L"Error: No words found in file");
        }
        return "";
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<std::size_t> dist(0, words.size() - 1);
    std::size_t randomIndex = dist(gen);
    return words[randomIndex];
}

std::string WordScrambler::scrambleWord(const std::string& word) {
    std::string scrambled = word;

    // Use std::shuffle
    std::random_device rd;
    std::mt19937 g(rd()); // Random number generator
    std::shuffle(scrambled.begin(), scrambled.end(), g);

    return scrambled;
}

std::string WordScrambler::toLowerCase(const std::string& str) {
    std::string lowerStr = str;

    // Ensure <algorithm> is included for std::transform
    std::transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), ::tolower);

    return lowerStr;
}

void WordScrambler::displayHint(const std::string& word) {
    if (!screenBuffer) return;

    size_t length = word.length();
    char firstChar = word[0];
    char middleChar = word[length / 2];
    char lastChar = word[length - 1];

    std::wstring hint = L"Hint: The first letter is '" + std::wstring(1, firstChar) +
        L"', the middle letter is '" + std::wstring(1, middleChar) +
        L"', and the last letter is '" + std::wstring(1, lastChar) + L"'.";
    screenBuffer->writeToScreen(0, 1, hint);
}

void WordScrambler::displayGuessedWords(const std::vector<std::string>& guessedWords) {
    if (!screenBuffer) return;

    std::wstring guessedWordsStr = L"Guessed words: ";
    for (const auto& word : guessedWords) {
        guessedWordsStr += std::wstring(word.begin(), word.end()) + L", ";
    }
    // Remove the trailing comma and space
    if (guessedWords.size() > 0) {
        guessedWordsStr.resize(guessedWordsStr.length() - 2);
    }

    screenBuffer->writeToScreen(0, 7, guessedWordsStr+L" | Type Next Guess Here:");
}

void WordScrambler::playWordScrambler(const std::string& difficulty) {
    if (!screenBuffer) return;

    const int maxGuesses = 10;
    std::string filename;

    if (difficulty == "1" || difficulty == "easy") {
        filename = "../MiniGame-Madness/src/easy.txt";
    }
    else if (difficulty == "2" || difficulty == "medium") {
        filename = "../MiniGame-Madness/src/medium.txt";
    }
    else if (difficulty == "3" || difficulty == "hard") {
        filename = "../MiniGame-Madness/src/hard.txt";
    }
    else if (difficulty == "testcode") {
        filename = "easy.txt";
    }
    else {
        screenBuffer->writeToScreen(0, 1, L"Invalid difficulty level. Exiting game.");
        return;
    }

    std::string word = getRandomWord(filename);
    if (word.empty()) {
        // Error already handled in getRandomWord
        return;
    }
    std::string scrambledWord = scrambleWord(word);
    std::string guess;
    bool guessedCorrectly = false;
    int attempts = 0;

    std::vector<std::string> guessedWords;  // **Vector to store guessed words**

    while (attempts < maxGuesses && !guessedCorrectly) {
        clearScreen();
        screenBuffer->writeToScreen(0, 0, L"Scrambled word: " + std::wstring(scrambledWord.begin(), scrambledWord.end()));
        screenBuffer->writeToScreen(0, 2, L"Guess the word (or type 'stop' to exit, or 'hint' for a hint that costs 2 lives): ");

        // Display the guessed words so far
        displayGuessedWords(guessedWords);

        guess = screenBuffer->getBlockingInput();

        if (guess == "stop") {
            screenBuffer->writeToScreen(0, 3, L"Game stopped. Exiting...");
            return;
        }
        else if (guess == "hint") {
            clearScreen();
            screenBuffer->writeToScreen(0, 1, L"Are you sure? You will lose 2 lives (y/n): ");
            std::string response = screenBuffer->getBlockingInput();
            clearScreen();
            if (response == "y" || response == "Y") {
                displayHint(word);
                attempts += 2;
                if (attempts >= maxGuesses) break;
            }
            screenBuffer->writeToScreen(0, 2, L"Press Enter to continue...");
            screenBuffer->getBlockingInput();  // Pause for user to continue
            continue;
        }

        // **Add the guess to the guessedWords vector**
        guessedWords.push_back(guess);

        if (toLowerCase(guess) == toLowerCase(word)) {
            guessedCorrectly = true;
        }
        else {
            clearScreen();
            screenBuffer->writeToScreen(0, 1, L"Incorrect! Try again.");
            attempts++;
            screenBuffer->writeToScreen(0, 2, L"Attempts left: " + std::to_wstring(maxGuesses - attempts));
            screenBuffer->writeToScreen(0, 3, L"Press Enter to continue...");
            screenBuffer->getBlockingInput();  // Pause for user to continue
        }
    }

    clearScreen();
    if (guessedCorrectly) {
        screenBuffer->writeToScreen(0, 0, L"Congratulations! You guessed the word: " + std::wstring(word.begin(), word.end()));
    }
    else {
        screenBuffer->writeToScreen(0, 0, L"Sorry, you've run out of attempts. The word was: " + std::wstring(word.begin(), word.end()));
    }
}

void WordScrambler::run() {
    if (!screenBuffer) return;

    screenBuffer->setActive();  // Activate the ScreenBuffer
    std::string playAgain;

    do {
        clearScreen();
        screenBuffer->writeToScreen(0, 0, L"Choose difficulty (1: easy, 2: medium, 3: hard) or type 'stop' to exit: ");
        std::string difficulty = screenBuffer->getBlockingInput();

        if (difficulty == "stop") {
            screenBuffer->writeToScreen(0, 1, L"Game stopped. Exiting...");
            return;
        }

        playWordScrambler(difficulty);

        screenBuffer->writeToScreen(0, 12, L"Do you want to play again? (y/n or type 'stop' to exit): ");
        playAgain = screenBuffer->getBlockingInput();

        if (playAgain == "stop") {
            screenBuffer->writeToScreen(0, 13, L"Game stopped. Exiting...");
            return;
        }

    } while (playAgain == "y" || playAgain == "Y");

    screenBuffer->writeToScreen(0, 14, L"Thanks for playing!");
}
