// IScreenBuffer.h
#ifndef ISCREENBUFFER_H
#define ISCREENBUFFER_H

#include <string>
#include <Windows.h>

class IScreenBuffer {
public:
    virtual ~IScreenBuffer() {}
    virtual void writeToScreen(int x, int y, const std::wstring& text) = 0;
    virtual std::string getBlockingInput() = 0;
    virtual void clearScreen() = 0;
    virtual void setActive() = 0;
    // Add other methods if they are used by Hangman
};

#endif // ISCREENBUFFER_H
