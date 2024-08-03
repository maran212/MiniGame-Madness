#include <iostream>
#include <windows.h>
#include "curser.h"
#include "screen.h"

void writeToBuffer(HANDLE hConsole, int x, int y, std::string text)
{
    // Start coordiante based on x and y
    COORD position = {x, y};
    DWORD written;
    // Write the text to the console buffer at the specified position
    BOOL result = WriteConsoleOutputCharacterA(
        hConsole,      // Console screen buffer handle
        text.c_str(),  // Buffer containing the text to write
        text.length(), // Number of characters to write
        position,      // Coordinates where to start writing
        &written       // Variable to receive the number of characters written
    );
}

int main()
{
    // Get the handle to the console
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    clearScreen(hConsole);
    if (hConsole == INVALID_HANDLE_VALUE)
    {
        std::cerr << "Error getting console handle" << std::endl;
        return 1;
    }

    // Define the position and text to write
    COORD position1 = {10, 5};  // x = 10, y = 5
    COORD position2 = {30, 10}; // x = 30, y = 10

    // Write text at specific positions
    writeToBuffer(hConsole, 10, 5, "Hello at (10,5)!");
    writeToBuffer(hConsole, 30, 10, "Hello at (30,10)!");

    // Wait for user input
    std::cout << "Press any key to exit..." << std::endl;
    std::cin.get();
    clearScreen(hConsole);
    return 0;
}