#include "listener.h"

/**
 * Implementation of listener.h
 */

/**
 * Listen for keyboard input (blocking)
 * @return char The character that was pressed
 */
char keyboardListener()
{
    while (true)
        ;
    {
        if (_kbhit())
        {
            return _getch();
        }
    }
}

/**
 * Listen for keyboard input (polling)
 * @return char The character that was pressed (or a space if no key was pressed)
 */
char keyboardListener(int count)
{
    for (int i = 0; i < count; i++)
    {
        if (_kbhit())
        {
            return _getch();
        }
    }

    return ' ';
}
