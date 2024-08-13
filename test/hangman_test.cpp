#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <cstring>
#include <sstream> // For std::ostringstream

using namespace std;

// Function prototypes
void clearScreen();
void displayHangman(int wrongGuesses);
string getRandomWord(const string& filename);
void playHangman(const string& difficulty);+
bool isYes(const string& response);
bool isNo(const string& response);

// Test function prototypes
void testClearScreen();
void testDisplayHangman();
void testGetRandomWord();
void testIsYes();
void testIsNo();

// Helper function to capture output of displayHangman
string captureDisplayHangmanOutput(int wrongGuesses) {
    ostringstream output;
    streambuf* oldCoutStreamBuf = cout.rdbuf();
    cout.rdbuf(output.rdbuf()); // Redirect cout to the ostringstream
    displayHangman(wrongGuesses);
    cout.rdbuf(oldCoutStreamBuf); // Restore the original cout stream buffer
    return output.str();
}

int main() {
    // Seed the random number generator
    srand(time(0));

    // Run tests
    testClearScreen();
    testDisplayHangman();
    testGetRandomWord();
    testIsYes();
    testIsNo();

    cout << "All tests completed." << endl;
    return 0;
}

void testClearScreen() {
    cout << "Testing clearScreen()..." << endl;
    clearScreen();
    cout << "Screen should be cleared." << endl;
}

void testDisplayHangman() {
    cout << "Testing displayHangman()..." << endl;
    string expectedOutputs[] = {
        "  +---+\n      |\n      |\n      |\n     ===",
        "  +---+\n  O   |\n      |\n      |\n     ===",
        "  +---+\n  O   |\n  |   |\n      |\n     ===",
        "  +---+\n  O   |\n /|\\  |\n      |\n     ===",
        "  +---+\n  O   |\n /|\\  |\n /    |\n     ===",
        "  +---+\n  O   |\n /|\\  |\n / \\  |\n     ==="
    };

    for (int i = 0; i <= 5; ++i) {
        string actualOutput = captureDisplayHangmanOutput(i);
        if (actualOutput == expectedOutputs[i] + "\n") {
            cout << "Wrong guesses: " << i << " - Pass" << endl;
        } else {
            cout << "Wrong guesses: " << i << " - Fail" << endl;
            cout << "Expected:\n" << expectedOutputs[i] << endl;
            cout << "Actual:\n" << actualOutput << endl;
        }
    }
}

void testGetRandomWord() {
    cout << "Testing getRandomWord()..." << endl;
    cout << "The text file contains these words: apple, banana, cherry" << endl;
    // Create a test file
    ofstream testFile("test_words.txt");
    testFile << "apple\nbanana\ncherry\n";
    testFile.close();
    
    // Test the function multiple times
    for (int i = 0; i < 10; ++i) {
        string word = getRandomWord("test_words.txt");
        cout << "Test " << (i + 1) << ": " << "Random word: " << word << endl;
    }
    
    // Clean up
    remove("test_words.txt");
}

void testIsYes() {
    cout << "Testing isYes()..." << endl;
    cout << "Test 1: " << (isYes("y") ? "Passed" : "Failed") << endl;
    cout << "Test 2: " << (isYes("Y") ? "Passed" : "Failed") << endl;
    cout << "Test 3: " << (isYes("yes") ? "Passed" : "Failed") << endl;
    cout << "Test 4: " << (isYes("YES") ? "Passed" : "Failed") << endl;
    cout << "Test 5: " << (isYes("n") ? "Failed" : "Passed") << endl;
}

void testIsNo() {
    cout << "Testing isNo()..." << endl;
    cout << "Test 1: " << (isNo("n") ? "Passed" : "Failed") << endl;
    cout << "Test 2: " << (isNo("N") ? "Passed" : "Failed") << endl;
    cout << "Test 3: " << (isNo("no") ? "Passed" : "Failed") << endl;
    cout << "Test 4: " << (isNo("NO") ? "Passed" : "Failed") << endl;
    cout << "Test 5: " << (isNo("y") ? "Failed" : "Passed") << endl;
}

// Function implementations
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
    int randomIndex = rand() % words.size(); // Use the already seeded random number generator
    return words[randomIndex];
}

void playHangman(const string& difficulty) {
    // Implement this method if needed for testing
}

bool isYes(const string& response) {
    return response == "y" || response == "Y" || response == "yes" || response == "YES";
}

bool isNo(const string& response) {
    return response == "n" || response == "N" || response == "no" || response == "NO";
}
