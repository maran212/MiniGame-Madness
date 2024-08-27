#include "WordScrambler.h"

void WordScrambler::clearScreen() const {
    std::cout << '\033[2j';
}

std::string WordScrambler::getRandomWord(const std::string& filename) const {
    std::vector<std::string> words;
    std::ifstream file(filename);
    std::string word;

    while (file >> word) {
        words.push_back(word);
    }
    file.close();

    srand(static_cast<unsigned int>(time(0)));
    int randomIndex = rand() % words.size();
    return words[randomIndex];
}

std::string WordScrambler::scrambleWord(const std::string& word) const {
    std::string scrambled = word;
    std::random_shuffle(scrambled.begin(), scrambled.end());
    return scrambled;
}

std::string WordScrambler::toLowerCase(const std::string& str) const {
    std::string lowerStr = str;
    std::transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), ::tolower);
    return lowerStr;
}

void WordScrambler::displayHint(const std::string& word) const {
    int length = word.length();
    char firstChar = word[0];
    char middleChar = word[length / 2];
    char lastChar = word[length - 1];

    std::cout << "Hint: The first letter is '" << firstChar << "', the middle letter is '" << middleChar << "', and the last letter is '" << lastChar << "'." << std::endl;
}

void WordScrambler::playWordScrambler(const std::string& difficulty) {
    const int maxGuesses = 10;
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
        std::cout << "Invalid difficulty level. Exiting game." << std::endl;
        return;
    }

    std::string word = getRandomWord(filename);
    std::string scrambledWord = scrambleWord(word);
    std::string guess;
    bool guessedCorrectly = false;
    int attempts = 0;

    while (attempts < maxGuesses && !guessedCorrectly) {
        clearScreen();
        std::cout << "Scrambled word: " << scrambledWord << std::endl;
        std::cout << "Guess the word (or type 'stop' to exit, or 'hint' for a hint that costs 2 lives): ";
        std::cin >> guess;

        if (guess == "stop") {
            std::cout << "Game stopped. Exiting..." << std::endl;
            return;
        }
        else if (guess == "hint") {
            std::cout << "Are you sure? You will lose 2 lives (y/n): ";
            std::string response;
            std::cin >> response;
            if (response == "y" || response == "Y") {
                displayHint(word);
                attempts += 2;
                if (attempts >= maxGuesses) {
                    break;
                }
            }
            std::cout << "Press Enter to continue...";
            std::cin.ignore();
            std::cin.get();
            continue;
        }

        if (toLowerCase(guess) == toLowerCase(word)) {
            guessedCorrectly = true;
        }
        else {
            std::cout << "Incorrect! Try again." << std::endl;
            attempts++;
            std::cout << "Attempts left: " << maxGuesses - attempts << std::endl;
            std::cout << "Press Enter to continue...";
            std::cin.ignore();
            std::cin.get();
        }
    }

    clearScreen();
    if (guessedCorrectly) {
        std::cout << "Congratulations! You guessed the word: " << word << std::endl;
    }
    else {
        std::cout << "Sorry, you've run out of attempts. The word was: " << word << std::endl;
    }
}

void WordScrambler::run() {
    WordScrambler game;

        std::string playAgain;
        do {
            game.clearScreen();
            std::cout << "Choose difficulty (1: easy, 2: medium, 3: hard) or type 'stop' to exit: ";
            std::string difficulty;
            std::cin >> difficulty;

            if (difficulty == "stop") {
                std::cout << "Game stopped. Exiting..." << std::endl;
                return;
            }

            game.playWordScrambler(difficulty);

            std::cout << "Do you want to play again? (y/n or type 'stop' to exit): ";
            std::cin >> playAgain;

            if (playAgain == "stop") {
                std::cout << "Game stopped. Exiting..." << std::endl;
                return;
            }

        } while (playAgain == "y" || playAgain == "Y");

        std::cout << "Thanks for playing!" << std::endl;
    

    return;
}
