#ifndef SCREENBUFFER_H
#define SCREENBUFFER_H

#include <string>
#include <utility>
#include <vector>
#include <stdexcept>
#include <windows.h>

class screenBuffer
{
private:
    HANDLE screenHandle;
    const WORD NO_COLOUR = -1;

    /**
     * Throw an error if the result is false
     * @param result The result of the operation
     */
    void throwError(BOOL result, const std::string message) const;

    /**
     * Write to the screen buffer
     * @param x The x coordinate
     * @param y The y coordinate
     * @param text The text to write
     * @return result The result of the operation
     */
    BOOL writeToScreenBuffer(int x, int y, const std::string text);

    /**
     * Return the text and background colours to the default
     * @return void
     */
    void resetColours();

public:
    /**
     * Constructor for the screenBuffer class
     */
    screenBuffer();

    /**
     * Destructor for the screenBuffer class
     */
    ~screenBuffer();

    /**
     * Get the screen buffer handle
     * @return HANDLE The handle of the screen buffer
     */
    HANDLE getScreenHandle() const;

    /**
     * Check if the screen buffer is active
     * @return bool True if the screen buffer is active
     */
    bool isActive() const;

    /**
     * Get screen buffer info
     * @return CONSOLE_SCREEN_BUFFER_INFO The screen buffer info
     */
    CONSOLE_SCREEN_BUFFER_INFO getScreenBufferInfo() const;

    /**
     * Clears the screen buffer
     */
    void clearScreen();

    /**
     * Get the screen buffer width
     * @return int The width of the screen buffer
     */
    int getScreenWidth() const;

    /**
     * Get the screen buffer height
     * @return int The height of the screen buffer
     */
    int getScreenHeight() const;

    /**
     * Get the size of the screen buffer
     * @return int The size of the screen
     */
    int getScreenSize() const;

    /**
     * Set the size of the screen buffer and window
     * @param width The width of the screen
     * @param height The height of the screen
     */
    void setScreenSize(int width, int height);

    /**
     * Get the screen text and background colors
     * @param x The x coordinate
     * @param y The y coordinate
     * @param length The length of the text
     * @return std::pair<WORD, WORD> The text and background colors
     */
    std::pair<WORD, WORD> getScreenColours(int x, int y, int length) const;

    /**
     * Set the screen text
     * @param text The text to have its colour set
     * @param textColour The color of the text
     * @param backgroundColour The color of the background
     * @return void
     */
    std::string setTextColours(std::string text, WORD textColour, WORD backgroundColour);

    /**
     * Set cursor visibility
     * @param isVisible True to show the cursor, false to hide it
     */
    void setCursorVisibility(bool isVisible);

    /**
     * Move the cursor to the specified location
     * @param x The x coordinate
     * @param y The y coordinate
     */
    void setCursorPosition(int x, int y);

    /**
     * Get the current location of the cursor
     * @return std::pair<int, int> The x and y coordinates of the cursor
     */
    std::pair<int, int> getCursorPosition() const;

    /**
     * Get part of text in the screen buffer
     * @param x The x coordinate
     * @param y The y coordinate
     * @param length The length of the text
     * @return std::string The text at the specified location
     */
    std::string getScreenText(int x, int y, int length) const;

    /**
     * Get all of the text in the screen buffer
     * @return std::string The text in the screen buffer
     */
    std::string getAllScreenText() const;

    /**
     * Write text to the screen at a specific location
     * @param x The x coordinate
     * @param y The y coordinate
     * @param text The text to write
     */
    void writeToScreen(int x, int y, const std::string text);

    /**
     * Write text to the screen at a specific location with a specific color
     * @param x The x coordinate
     * @param y The y coordinate
     * @param text The text to write
     * @param textColour The color of the text
     * @param backgroundColour The color of the background
     */
    void writeToScreen(int x, int y, const std::string text, WORD textColour, WORD backgroundColour);

    /**
     * Fill the screen buffer with a specific character
     * @param character The character to write
     */
    void fillScreen(std::string text);

    /**
     * Fill the screen buffer with a specific character and color
     * @param character The character to write
     * @param textColour The color of the text
     * @param backgroundColour The color of the background
     */
    void fillScreen(std::string text, WORD textColour, WORD backgroundColour);
};

#endif // SCREENBUFFER_H

