#ifndef SCREEN_H
#define SCREEN_H

// Include any necessary libraries here
#include <windows.h>
#include <utility>

// Define any constants or global variables here

// Declare any function prototypes here
void clearScreen(HANDLE screenHandle);
std::pair<short, short> getScreenSize(HANDLE screenHandle);
void setScreenSize(HANDLE screenHandle, short width, short height);
void setScreenBackgroundColour(HANDLE screenHandle, WORD backgroundColour);
void setScreenTextColour(HANDLE screenHandle, WORD textColour);

#endif // SCREEN_H