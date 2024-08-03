
/**
 * Helper functions for controlling console screen.
 * @author Angus Martin
 */

#include <windows.h>
#include <utility>

/**
 * Clears the screen
 * @param screenHandle The handle of the screen buffer
 * @return void
 */
void clearScreen(HANDLE screenHandle)
{
    // Get the console screen buffer info
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(screenHandle, &csbi);

    // The number of cells in the buffer
    DWORD cellCount = csbi.dwSize.X * csbi.dwSize.Y;

    // Fill the entire buffer with spaces
    COORD home = {0, 0};
    DWORD count;

    FillConsoleOutputCharacter(screenHandle, TEXT(' '), cellCount, home, &count);
    FillConsoleOutputAttribute(screenHandle, csbi.wAttributes, cellCount, home, &count);

    // Move the cursor to the home position
    SetConsoleCursorPosition(screenHandle, home);
}

/**
 * Gets the size of the screen
 * @param screenHandle The handle of the screen buffer
 * @return std::pair<short, short> The width and height of the screen
 */
std::pair<short, short> getScreenSize(HANDLE screenHandle)
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(screenHandle, &csbi);
    return std::make_pair(csbi.srWindow.Right - csbi.srWindow.Left + 1, csbi.srWindow.Bottom - csbi.srWindow.Top + 1);
}

/**
 * Sets the size of the screen
 * @param screenHandle The handle of the screen buffer
 * @param width The width of the screen
 * @param height The height of the screen
 * @return void
 */
void setScreenSize(HANDLE screenHandle, short width, short height)
{
    // Set the screen buffer size to the specified size
    COORD size = {width, height};
    SetConsoleScreenBufferSize(screenHandle, size);

    // Set the window size to the specified size
    SMALL_RECT windowSize = {0, 0, width - 1, height - 1};
    SetConsoleWindowInfo(screenHandle, TRUE, &windowSize);
}

/**
 * set screen background colour
 * @param screenHandle The handle of the screen buffer
 * @param backgroundColour The colour of the background
 * @return void
 */
void setScreenBackgroundColour(HANDLE screenHandle, WORD backgroundColour)
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(screenHandle, &csbi);
    WORD attributes = (csbi.wAttributes & 0x0F) | (backgroundColour << 4);
    SetConsoleTextAttribute(screenHandle, backgroundColour);
}

/**
 * set screen text colour
 * @param screenHandle The handle of the screen buffer
 * @param textColour The colour of the text
 * @return void
 */
void setScreenTextColour(HANDLE screenHandle, WORD textColour)
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(screenHandle, &csbi);
    WORD attributes = (csbi.wAttributes & 0xF0) | textColour;
    SetConsoleTextAttribute(screenHandle, textColour);
}