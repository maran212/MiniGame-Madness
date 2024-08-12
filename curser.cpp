
/**
 * Helpper functions for manipulating the curser.
 * @author Angus Martin
 */

#include <windows.h>
#include <utility>


/**
 * Hides the curser
 * @param screenHandle The handle of the screen buffer
 * @return void
 */
void hideCurser(HANDLE screenHandle)
{
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(screenHandle, &info);
}

/**
 * Shows the curser
 * @param screenHandle The handle of the screen buffer
 * @return void
 */
void showCurser(HANDLE screenHandle)
{
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = TRUE;
    SetConsoleCursorInfo(screenHandle, &info);
}

/**
 * Moves the curser to the specified location
 * @param screenHandle The handle of the screen buffer
 * @param x The x coordinate
 * @param y The y coordinate
 * @return void
 */
void moveCurser(HANDLE screenHandle, int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(screenHandle, coord);
}

/**
 * Gets the current location of the curser
 * @param screenHandle The handle of the screen buffer
 * @return std::pair<int, int> The x and y coordinates of the curser
 */
std::pair<int, int> getCurserLocation(HANDLE screenHandle)
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(screenHandle, &csbi);
    return std::make_pair(csbi.dwCursorPosition.X, csbi.dwCursorPosition.Y);
}