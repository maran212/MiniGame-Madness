
#include "screenBuffer.h"



// Throws an error if the result is false
void screenBuffer::throwError(BOOL result, const std::string& message) const
{
    if (!result)
    {
        DWORD errorCode = GetLastError();
        std::string fullMessage = message + " Error Code: " + std::to_string(errorCode);
        throw std::runtime_error(fullMessage);
    }
}


// Write string to specified position in the screen buffer
BOOL screenBuffer::writeToScreenBuffer(int x, int y, const std::string& text)
{
    // Number of characters written
    DWORD written;

    // Move the cursor to the specified position
    setCursorPosition(x, y);

    return WriteConsole(
        screenHandle,  // Console screen buffer handle
        text.c_str(),  // Buffer containing the text to write
        text.length(), // Number of characters to write
        &written,      // Variable to receive the number of characters written
        nullptr        // Not using asynchronous writing
    );
}


//Return the text and background colours to the default
void screenBuffer::resetColours()
{
    // Set the text and background colours to the default
    BOOL result = writeToScreenBuffer(0, 0, "\033[0m");

    // Check if the colours were reset successfully
    throwError(result, "Error resetting colours");
}


// Constructor for the screenBuffer class
screenBuffer::screenBuffer()
{
    // Create a new screen buffer
    screenHandle = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);

    // Check if the screen buffer was created successfully
    throwError(screenHandle != INVALID_HANDLE_VALUE, "Error creating screen buffer");

    // clear the screen buffer
    clearScreen();

    // set screen buffer size to window size
    CONSOLE_SCREEN_BUFFER_INFO screenBufferInfo = getScreenBufferInfo();

    // Get console mod and set it to enable virtual terminal processing
    DWORD consoleModeOut;
    DWORD consoleModeIn;

    GetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), &consoleModeIn);
    GetConsoleMode(screenHandle, &consoleModeOut);

    consoleModeIn = ENABLE_VIRTUAL_TERMINAL_INPUT;
    consoleModeOut = ENABLE_VIRTUAL_TERMINAL_PROCESSING | DISABLE_NEWLINE_AUTO_RETURN;
    
    //SetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), consoleModeIn);
    SetConsoleMode(screenHandle, consoleModeOut);

    // Extract window size to set screen buffer size
    SMALL_RECT windowSize = screenBufferInfo.srWindow;
    int width = windowSize.Right - windowSize.Left + 1;
    int height = windowSize.Bottom - windowSize.Top + 1;

    setScreenSize(width, height);
}


// Destructor for the screenBuffer class
screenBuffer::~screenBuffer()
{
    // Close the screen buffer
    CloseHandle(screenHandle);
}


// Get the screen buffer handle
HANDLE screenBuffer::getScreenHandle() const
{
    return screenHandle;
}


// Is screen buffer active
bool screenBuffer::isActive() const
{
    HANDLE currentScreenHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    return screenHandle == currentScreenHandle;
}


// Get screen buffer info
CONSOLE_SCREEN_BUFFER_INFO screenBuffer::getScreenBufferInfo() const
{
    CONSOLE_SCREEN_BUFFER_INFO screenBufferInfo;
    BOOL result = GetConsoleScreenBufferInfo(screenHandle, &screenBufferInfo);

    // Check if the screen buffer info was retrieved successfully
    throwError(result, "Error getting screen buffer info");

    return screenBufferInfo;
}


// Clears the screen buffer
void screenBuffer::clearScreen()
{
    // Escape sequence to clear the screen and move cursor to the top left
    const char *clearScreenSequence = "\033[2J\033[H";

    // Write the escape sequence to the screen buffer
    BOOL result = writeToScreenBuffer(0, 0, clearScreenSequence);

    // Check if the screen buffer was cleared successfully
    throwError(result, "Error clearing screen buffer");
}


// Get the screen buffer width
int screenBuffer::getScreenWidth() const
{
    // Get the screen buffer info
    CONSOLE_SCREEN_BUFFER_INFO screenBufferInfo = getScreenBufferInfo();

    return screenBufferInfo.dwSize.X;
}


// Get the screen buffer height
int screenBuffer::getScreenHeight() const
{
    // Get the screen buffer info
    CONSOLE_SCREEN_BUFFER_INFO screenBufferInfo = getScreenBufferInfo();

    return screenBufferInfo.dwSize.Y;
}


// Gets the size of the screen buffer
int screenBuffer::getScreenSize() const
{
    // Get the screen buffer info
    CONSOLE_SCREEN_BUFFER_INFO screenBufferInfo = getScreenBufferInfo();

    return screenBufferInfo.dwSize.X * screenBufferInfo.dwSize.Y;
}


// Sets the size of the screen buffer and window
void screenBuffer::setScreenSize(int width, int height)
{
    // Making screen size smaller than current screen size (screen buffer can't be smaller than the window)
    if (width < getScreenWidth() || height < getScreenHeight())
    {
        // Set the window size to the specified size and converting to shorts for the functions
        SMALL_RECT windowSize = {0, 0, static_cast<SHORT>(width) - 1, static_cast<SHORT>(height) - 1};
        BOOL result2 = SetConsoleWindowInfo(screenHandle, TRUE, &windowSize);

        // check if the screen buffer size was set successfully
        throwError(result2, "Error setting console window size");

        // Set the screen buffer size to the specified size and converting to shorts for the functions
        COORD size = {static_cast<SHORT>(width), static_cast<SHORT>(height)};
        BOOL result1 = SetConsoleScreenBufferSize(screenHandle, size);

        // Check if the screen buffer size was set successfully
        throwError(result1, "Error setting screen buffer size");
    }
    else
    {
        // Set the screen buffer size to the specified size and converting to shorts for the functions
        COORD size = {static_cast<SHORT>(width), static_cast<SHORT>(height)};
        BOOL result1 = SetConsoleScreenBufferSize(screenHandle, size);

        // Check if the screen buffer size was set successfully
        throwError(result1, "Error setting screen buffer size");

        // Set the window size to the specified size and converting to shorts for the functions
        SMALL_RECT windowSize = {0, 0, static_cast<SHORT>(width) - 1, static_cast<SHORT>(height) - 1};
        BOOL result2 = SetConsoleWindowInfo(screenHandle, TRUE, &windowSize);

        // check if the screen buffer size was set successfully
        throwError(result2, "Error setting console window size");
    }
}


// Get the screen text and background colours
std::pair<WORD, WORD> screenBuffer::getScreenColours(int x, int y, int length) const
{
    // Start coordiante based on x and y
    COORD position = {static_cast<SHORT>(x), static_cast<SHORT>(y)};

    // Declare the attributes vector
    std::vector<WORD> attributes(length);

    // number of attributes read
    DWORD read;

    // Read the attributes from the console buffer at the specified position
    BOOL result = ReadConsoleOutputAttribute(
        screenHandle,      // Console screen buffer handle
        attributes.data(), // Buffer to store the attributes
        length,            // Number of attributes to read
        position,          // Coordinates where to start reading
        &read              // Variable to receive the number of attributes read
    );

    // Check if the attributes were read successfully
    throwError(result, "Error getting screen colours");

    return std::make_pair(attributes[0] & 0x0F, attributes[0] >> 4);
}


// Set the screen text colour and background colour
std::string screenBuffer::setTextColours(const std::string& text, WORD textColour, WORD backgroundColour)
{
    // String to hold the VT sequence
    std::string vtSequence = "\033[";

    // Apply text color if specified

    if (textColour != NO_COLOUR)
    {
        vtSequence += std::to_string(30 + textColour);
    }

    // Apply background color if specified
    if (backgroundColour != NO_COLOUR)
    {
        if (textColour != NO_COLOUR)
        {
            vtSequence += ";";
        }
        vtSequence += std::to_string(40 + backgroundColour);
    }

    vtSequence += "m" + text + "\033[0m"; // Append text and reset sequence

    return vtSequence;
}


// Change curser visablitly
void screenBuffer::setCursorVisibility(bool isVisible)
{
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = isVisible;
    BOOL result = SetConsoleCursorInfo(screenHandle, &info);

    // Check if the cursor visibility was set successfully
    throwError(result, "Error setting cursor visibility");
}


// Moves the curser to the specified location
void screenBuffer::setCursorPosition(int x, int y)
{
    COORD coord;
    coord.X = static_cast<SHORT>(x);
    coord.Y = static_cast<SHORT>(y);
    BOOL result = SetConsoleCursorPosition(screenHandle, coord);

    // Check if the cursor position was set successfully
    throwError(result, "Error setting cursor position");
}


// Gets the current location of the curse
std::pair<int, int> screenBuffer::getCursorPosition() const
{
    // Get the screen buffer info
    CONSOLE_SCREEN_BUFFER_INFO screenBufferInfo = getScreenBufferInfo();

    return std::make_pair(screenBufferInfo.dwCursorPosition.X, screenBufferInfo.dwCursorPosition.Y);
}


// Get text from a section of the screen buffer
std::string screenBuffer::getScreenText(int x, int y, int length) const
{

    // Start coordiante based on x and y
    COORD position = {static_cast<SHORT>(x), static_cast<SHORT>(y)};

    // Create a buffer to store the text
    std::string text(length, ' ');

    // Number of characters read
    DWORD read;

    // Read the text from the console buffer at the specified position
    BOOL result = ReadConsoleOutputCharacterA(
        screenHandle, // Console screen buffer handle
        &text[0],     // Buffer to store the text
        length,       // Number of characters to read
        position,     // Coordinates where to start reading
        &read         // Variable to receive the number of characters read
    );
    // Check if the text was read successfully
    throwError(result, "Error getting screen text");

    return text;
}


// Get all of the text from the screen buffer
std::string screenBuffer::getAllScreenText() const
{
    // Get the text from the screen buffer
    return getScreenText(0, 0, getScreenSize());
}


// Writes text to the screen at a specific location
void screenBuffer::writeToScreen(int x, int y, const std::string& text)
{
    // Write the text to the screen
    BOOL result = writeToScreenBuffer(x, y, text);

    // Check if the text was written successfully
    throwError(result, "Error writing to screen");
}


// Writes text to the screen at a specific location with a specific colour
void screenBuffer::writeToScreen(int x, int y, const std::string& text, WORD textColour, WORD backgroundColour)
{
    // write the text to the screen
    writeToScreen(x, y, setTextColours(text, textColour, backgroundColour));

    // Reset the text and background colours to defaults
    // resetColours();
}

