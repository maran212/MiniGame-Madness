#include <iostream>
#include <windows.h>
#include "curser.h"
#include "screenBuffer.h"

int main()
{
    // Get the handle to the console
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    if (hConsole == INVALID_HANDLE_VALUE)
    {
        std::cerr << "Error getting console handle" << std::endl;
        return 1;
    }

    // Define the position and text to write
    COORD position1 = {10, 5};  // x = 10, y = 5
    COORD position2 = {30, 10}; // x = 30, y = 10

    // Wait for user input
    std::cout << "Press any key to exit..." << std::endl;
    std::cin.get();

    return 0;
}