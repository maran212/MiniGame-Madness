#ifndef SCREEN_H
#define SCREEN_H

// Include any necessary libraries here
#include <windows.h>
#include <utility>

// Define any constants or global variables here

// Declare any function prototypes here
void clearScreen();
std::pair<int, int> getScreenSize();
void setScreenSize(int width, int height);
void setScreenBackgroundColor(int color);

#endif // SCREEN_H