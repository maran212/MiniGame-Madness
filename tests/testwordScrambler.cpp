#include "pch.h"
#include <iostream>
#include <cassert>
#include <algorithm> // For std::sort
#include <fstream>   // For std::ofstream
#include <sstream>   // For std::ostringstream
#include "wordScrambler.h"  // Include your header file

using namespace std;

// Test function for toLowerCase
void testToLowerCase() {
    assert(toLowerCase("Hello") == "hello");
    assert(toLowerCase("WORLD") == "world");
    assert(toLowerCase("TeSt") == "test");
    assert(toLowerCase("cOdE") == "code");
    cout << "toLowerCase() passed all tests!" << endl;
}

// Test function for scrambleWord
void testScrambleWord() {
    string word = "hello";
    string scrambled = scrambleWord(word);
    // Check that scrambled word is not the same as the original but contains the same letters
    assert(scrambled != word);
    sort(scrambled.begin(), scrambled.end());  // Sort for comparison
    sort(word.begin(), word.end());
    assert(scrambled == word);
    cout << "scrambleWord() passed all tests!" << endl;
}

// Test function for getRandomWord
void testGetRandomWord() {
    string filename = "testWords.txt";
    ofstream outFile(filename);
    outFile << "apple banana cherry date" << endl;
    outFile.close();
    
    string word = getRandomWord(filename);
    assert(word == "apple" || word == "banana" || word == "cherry" || word == "date");
    cout << "getRandomWord() passed all tests!" << endl;
}

// Test function for displayHint
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

// Test runner
int main() {
    // Run all the tests
    testToLowerCase();
    testScrambleWord();
    testGetRandomWord();
    testDisplayHint();
    
    cout << "All tests passed!" << endl;
    return 0;
}
