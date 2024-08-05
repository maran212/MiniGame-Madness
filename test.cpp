#include <stdio.h>
#include <iostream>
#include <windows.h>

// Function to set text color
void setTextColor(int colorCode)
{
    std::cout << "\033[38;5;" << colorCode << "m";
}

// Function to set background color
void setBackgroundColor(int colorCode)
{
    std::cout << "\033[48;5;" << colorCode << "m";
}

// Function to reset colors
void resetColors()
{
    std::cout << "\033[0m";
}

// Function to move cursor to (row, col)
void moveCursor(int row, int col)
{
    std::cout << "\033[" << row << ";" << col << "H";
}

// Function to clear the screen
void clearScreen()
{
    std::cout << "\033[2J";
}

int main()
{
    // Example usage
    wprintf(L"\033[?1049h");
    wprintf(L"new screen");

    Sleep(5000);
    clearScreen();
    moveCursor(5, 10);
    setTextColor(82);       // Set text color to green
    setBackgroundColor(16); // Set background color to black
    std::cout << "Hello, colored world!" << std::endl;
    resetColors(); // Reset to default colors

    return 0;
}