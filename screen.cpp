
/**
 * Helper functions for controlling console screen.
 * @author Angus Martin
 */

#include <windows.h>
#include <utility>

/**
 * Clears the screen
 * @return void
 */
void clearScreen()
{
    system("cls");
}

/**
 * Gets the size of the screen
 * @param screenHandle The handle of the screen buffer
 * @return std::pair<int, int> The width and height of the screen
 */
std::pair<int, int> getScreenSize(HANDLE screenHandle)
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
void setScreenSize(HANDLE screenHandle, int width, int height)
{
    SMALL_RECT windowSize = {0, 0, width - 1, height - 1};
    SetConsoleWindowInfo(screenHandle, TRUE, &windowSize);
}

/**
 * set screen background color
 * @param screenHandle The handle of the screen buffer
 * @param color The color of the background
 * @return void
 */
void setScreenBackgroundColor(HANDLE screenHandle, int color)
{
    SetConsoleTextAttribute(screenHandle, color);
}