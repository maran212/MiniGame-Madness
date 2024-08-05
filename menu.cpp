#include <iostream>
#include "screenBuffer.h"

int main()
{
    try
    {
        // Declare and create a new console screen buffer dynamically
        screenBuffer *newBuffer = new screenBuffer();

        // Set the new buffer as the active screen buffer
        if (!SetConsoleActiveScreenBuffer(newBuffer->getScreenHandle()))
        {
            throw std::runtime_error("Failed to set active screen buffer.");
        }

        std::cout << "New screen buffer activated." << std::endl;

        // Use the new buffer to clear and fill the screen
        newBuffer->clearScreen();
        newBuffer->fillScreen('x');
        std::cout << "Screen buffer cleared and filled with 'x'." << std::endl;

        // Wait for user input to exit
        std::cout << "Press Enter to exit..." << std::flush;
        std::cin.get();

        // Clean up
        delete newBuffer;
    }
    catch (const std::exception &e)
    {
        std::cerr << "An error occurred: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
