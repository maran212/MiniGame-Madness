
#ifndef SCREENBUFFER_H
#define SCREENBUFFER_H

/*!
 * @file screenBuffer.h
 * @brief Contains the declaration of the screenBuffer class and its member functions.
 * @author Angus Martin
 */

#include <string>
#include <utility>
#include <vector>
#include <stdexcept>
#include <windows.h>
#include <iostream>
#include <conio.h>

/*!
 * @class screenBuffer
 * @brief A class that represents the screen buffer.
 *
 * This class provides methods to interact with the screen buffer, such as writing text to the screen,
 * changing the cursor position, and setting text and background colors.
 */
class ScreenBuffer
{
private:
    HANDLE screenHandle = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
    const WORD NO_COLOUR = -1;

    /*!
     * @brief Throw an error if the result is false
     * @param result The result of the operation
     */
    void throwError(BOOL result, const std::string& message) const;

    /*!
	 * @brief Write to the screen buffer at a specific location
     * @param x The x coordinate
     * @param y The y coordinate
     * @param text The text to write
     * @return result The result of the operation
     */
    BOOL writeToScreenBuffer(int x, int y, const std::wstring& text);

	/*!
	 * @brief Write to the screen buffer at current cursor position
	 * @param text The text to write
	 * @return result The result of the operation
	 */
	BOOL writeToScreenBuffer(const std::wstring& text);

    /*!
     * @brief Set the screen text
     * @param text The text to have its colour set
     * @param textColour The color of the text
     * @param backgroundColour The color of the background
     */
    std::wstring setTextColours(const std::wstring& text, WORD textColour, WORD backgroundColour);

    /*!
	 * @brief Covert from windows console 16 colours to ANSI VT 8 colours
	 * @param Colour The windows console colour
	 * @return The ANSI VT colour
	 */
	WORD convertColour(WORD colour) const;



public:
	// Constants for text and background colours
	static const WORD FOREGROUND_NORMAL = -3;
	static const WORD BACKGROUND_NORMAL = -13;
	static const WORD BLACK = 0;
	static const WORD RED = 1;
	static const WORD GREEN = 2;
	static const WORD YELLOW = 3;
	static const WORD BLUE = 4;
	static const WORD MAGENTA = 5;
	static const WORD CYAN = 6;
	static const WORD WHITE = 7;

    /*!
     * @brief Constructor for the screenBuffer class
     */
    ScreenBuffer();

	/*!
	 * @brief Constructor for the screenBuffer class
	 * @param width The width of the screen buffer
	 * @param height The height of the screen buffer
	 */
	ScreenBuffer(int width, int height);

    /*!
     * @brief Destructor for the screenBuffer class
     */
    ~ScreenBuffer();

    /*!
     * @brief Get the screen buffer handle
     * @return HANDLE The handle of the screen buffer
     */
    HANDLE getScreenHandle() const;

    /*!
     * @brief Check if the screen buffer is active
     * @return bool True if the screen buffer is active
     */
    bool isActive() const;

	/*!
	 * @brief Set the screen buffer to active
	 */
	void setActive();

    /*!
     * @brief Get screen buffer info
     * @return CONSOLE_SCREEN_BUFFER_INFO The screen buffer info
     */
    CONSOLE_SCREEN_BUFFER_INFO getScreenBufferInfo() const;

    /*!
     * @brief Clears the screen buffer
     */
    void clearScreen();

    /*!
     * @brief Get the screen buffer width
     * @return int The width of the screen buffer
     */
    int getScreenWidth() const;

    /*!
     * @brief Get the screen buffer height
     * @return int The height of the screen buffer
     */
    int getScreenHeight() const;

    /*!
     * @brief Set the size of the screen buffer and window
     * @param width The width of the screen
     * @param height The height of the screen
     */
    void setScreenSize(int width, int height);

    /*!
     * @brief Get the screen text and background colors
     * @param x The x coordinate
     * @param y The y coordinate
     * @param length The length of the text
     * @return std::pair<WORD, WORD> The text and background colors
     */
    std::pair<WORD, WORD> getScreenColours(int x, int y, int length) const;

    /*!
     * @brief Set cursor visibility
     * @param isVisible True to show the cursor, false to hide it
     */
    void setCursorVisibility(bool isVisible);

    /*!
     * @brief Move the cursor to the specified location
     * @param x The x coordinate
     * @param y The y coordinate
     */
    void setCursorPosition(int x, int y);

    /*!
     * @brief Get the current location of the cursor
     * @return std::pair<int, int> The x and y coordinates of the cursor
     */
    std::pair<int, int> getCursorPosition() const;

    /*!
     * @brief Get part of text in the screen buffer
     * @param x The x coordinate
     * @param y The y coordinate
     * @param length The length of the text
     * @return std::string The text at the specified location
     */
    std::wstring readScreenText(int x, int y, int length) const;

    /*!
     * @brief Get all of the text in the screen buffer
     * @return std::string The text in the screen buffer
     */
    std::wstring readAllScreenText() const;

    /*!
     * @brief Write text to the screen at a specific location
     * @param x The x coordinate
     * @param y The y coordinate
     * @param text The text to write
     */
    void writeToScreen(int x, int y, const std::wstring& text);

    /*!
     * @brief Write text to the screen at a specific location with a specific color
     * @param x The x coordinate
     * @param y The y coordinate
     * @param text The text to write
     * @param textColour The color of the text
     * @param backgroundColour The color of the background
     */
    void writeToScreen(int x, int y, const std::wstring& text, WORD textColour, WORD backgroundColour);

    /*!
	 * @brief get blocking input from the user
	 * @return std::wstring The input from the user
	 */
	std::string getBlockingInput();

	/*!
	 * @brief get non-blocking input from the user
	 * @return std::wstring The input from the user
	 */ 
	std::string getNonBlockingInput();
};

#endif // SCREENBUFFER_H
