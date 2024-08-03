#ifndef CURSER_H
#define CURSER_H

// Add any necessary includes here
#include <windows.h>
#include <utility>

// Declare your class or functions here
void hideCurser(HANDLE screenHandle);
void showCurser(HANDLE screenHandle);
void moveCurser(HANDLE screenHandle, int x, int y);
std::pair<int, int> getCurserLocation(HANDLE screenHandle);

#endif // CURSER_H