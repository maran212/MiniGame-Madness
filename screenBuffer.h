#ifndef SCREENBUFFER_H
#define SCREENBUFFER_H

#include <windows.h>
#include <utility>
#include <string>

class screenBuffer
{

private:
    HANDLE screenHandle;
    WORD SAME_COLOUR = 0xFFFF; // No change in  text or background colour

    // throw Errors if result is false
    void throwError(BOOL result, std::string message) const;

public:
    // Constructor
    screenBuffer();

    // Destructor
    ~screenBuffer();

    // Get the screen handle
    HANDLE getScreenHandle() const;

    // Is active
    bool isActive() const;

    // Clear the screen buffer
    void clearScreen();

    // Get the screen buffer width
    int getScreenWidth() const;

    // Get the screen buffer height
    int getScreenHeight() const;

    // Get the screen buffer size
    int getScreenSize() const;

    // Get screen buffer text and bacgoround colours
    std::pair<WORD, WORD> getScreenColours(int x, int y, int length) const;

    // Set screen buffer text and background colours
    void setScreenColours(int x, int y, int length, WORD textColour, WORD backgroundColour);

    // Set curser visibility
    void setCursorVisibility(bool visible);

    // Get cursor position
    std::pair<int, int> getCursorPosition() const;

    // Change cursor position
    void setCursorPosition(int x, int y);

    // Get text from screen buffer
    std::string getScreenText(int x, int y, int length);

    // Get all text from screen buffer
    std::string getAllScreenText() const;

    // Write text to the screen buffer at a specific position
    void writeToScreen(int x, int y, std::string text);

    // Write text to the screen buffer at a specific position with a specific colour
    void writeToScreen(int x, int y, std::string text, WORD textColour, WORD backgroundColour);

    // Fill the screen buffer with a specific character
    void fillScreen(char character);

    // Copy old screen buffer to new screen buffer
    static screenBuffer copyScreenBufferCopy(const screenBuffer &screenBufferOld);
};

#endif // SCREENBUFFER_H