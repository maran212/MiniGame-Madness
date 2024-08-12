#ifndef LISTENER_H
#define LISTENER_H

#include <conio.h>
#include <iostream>

/**
 * Listening for user input from mouse or keyboard
 */

/**
 * Listen for keyboard input (blocking)
 * @return char The character that was pressed
 */
char keyboardListener();

/**
 * Listen for keyboard input (polling)
 * @return char The character that was pressed (or a space if no key was pressed)
 */
char keyboardListener(int count);

#endif // LISTENER_H