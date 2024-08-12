#include "screenBuffer.h"
#include <iostream>
#include <stdexcept>
#include <string>

// Assertion functions

/**
 * Asserts that two strings are equal
 * @param expected The expected string
 * @param actual The actual string
 * @param testName The name of the test
 * @return bool True if the strings are equal
 */
bool assertEqual(const std::string &expected, const std::string &actual)
{
    if (expected != actual)
    {
        throw std::runtime_error("Expected: " + expected + "| Actual: " + actual);
    }

    return expected == actual;
}

/**
 * Asserts that two integers are equal
 * @param expected The expected integer
 * @param actual The actual integer
 * @param testName The name of the test
 * @return bool True if the integers are equal
 */
bool assertEqual(const int expected, const int actual)
{
    if (expected != actual)
    {
        throw std::runtime_error("Expected: " + std::to_string(expected) + "| Actual: " + std::to_string(actual));
    }

    return expected == actual;
}

/**
 * Asserts that two pairs of WORDs are equal
 * @param expected The expected pair of WORDs
 * @param actual The actual pair of WORDs
 * @param testName The name of the test
 * @return bool True if the pairs of WORDs are equal
 */
bool assertEqual(const std::pair<WORD, WORD> &expected, const std::pair<WORD, WORD> &actual)
{
    if (expected != actual)
    {
        throw std::runtime_error("Expected: (" + std::to_string(expected.first) + ", " + std::to_string(expected.second) + ")| Actual: (" + std::to_string(actual.first) + ", " + std::to_string(actual.second) + ")");
    }

    return expected == actual;
}

/**
 * Asserts if a comparison is true
 * @param actual The actual boolean
 * @param testName The name of the test
 * @return bool True if the booleans are equal
 */
bool assertTrue(const bool actual)
{
    if (!actual)
    {
        throw std::runtime_error("Expected: true | Actual: false");
    }

    return actual;
}

// Test functions
bool testConstructor()
{
    screenBuffer buffer;
    return assertTrue(buffer.getScreenHandle() != INVALID_HANDLE_VALUE);
}

bool testDestructor()
{
    screenBuffer buffer;
    HANDLE handle = buffer.getScreenHandle();
    buffer.~screenBuffer();
    return assertTrue(!CloseHandle(handle));
}

bool testIsActive()
{
    screenBuffer buffer;
    return assertTrue(!buffer.isActive());
}

bool testGetScreenBufferWidth()
{
    screenBuffer buffer;
    CONSOLE_SCREEN_BUFFER_INFO info;
    GetConsoleScreenBufferInfo(buffer.getScreenHandle(), &info);
    return assertEqual(info.dwSize.X, buffer.getScreenWidth());
}

bool testGetScreenBufferHeight()
{
    screenBuffer buffer;
    CONSOLE_SCREEN_BUFFER_INFO info;
    GetConsoleScreenBufferInfo(buffer.getScreenHandle(), &info);
    return assertEqual(info.dwSize.Y, buffer.getScreenHeight());
}

bool testGetScreenSize()
{
    screenBuffer buffer;
    CONSOLE_SCREEN_BUFFER_INFO info;
    GetConsoleScreenBufferInfo(buffer.getScreenHandle(), &info);
    return assertEqual(info.dwSize.X * info.dwSize.Y, buffer.getScreenSize());
}

bool testSetScreenSizeSmaller()
{
    screenBuffer buffer;
    buffer.setScreenSize(10, 10);
    return assertTrue(buffer.getScreenWidth() == 10 && buffer.getScreenHeight() == 10);
}

bool testSetScreenSizeLarger()
{
    screenBuffer buffer;
    buffer.setScreenSize(500, 500);
    return assertTrue(buffer.getScreenWidth() == 500 && buffer.getScreenHeight() == 500);
}

bool testWriteToScreen()
{
    screenBuffer buffer;

    buffer.setScreenText(0, 13, "Hello, World!");
    return assertEqual("Hello, World!", buffer.getScreenText(0, 13, 13));
}

bool testSetScreenColours()
{
    screenBuffer buffer;
    std::pair<WORD, WORD> colours(FOREGROUND_GREEN, BACKGROUND_BLUE);

    buffer.setScreenColours(25, 10, 13, FOREGROUND_GREEN, BACKGROUND_BLUE);
    return assertEqual(colours, buffer.getScreenColours(25, 10, 13));
}

int main()
{
    int passed = 0;
    int total = 10;
    std::cout << "Running tests..." << std::endl;

    std::cout << "Test 1: Constructor" << std::endl;
    try
    {
        testConstructor();
        passed++;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    std::cout << "Test 2: Destructor" << std::endl;
    try
    {
        testDestructor();
        passed++;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    std::cout << "Test 3: isActive" << std::endl;
    try
    {
        testIsActive();
        passed++;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    std::cout << "Test 4: getScreenBufferWidth" << std::endl;
    try
    {
        testGetScreenBufferWidth();
        passed++;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    std::cout << "Test 5: getScreenBufferHeight" << std::endl;
    try
    {
        testGetScreenBufferHeight();
        passed++;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    std::cout << "Test 6: getScreenSize" << std::endl;
    try
    {
        testGetScreenSize();
        passed++;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    std::cout << "Test 7: setScreenSizeSmaller" << std::endl;
    try
    {
        testSetScreenSizeSmaller();
        passed++;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    std::cout << "Test 8: setScreenSizeLarger" << std::endl;
    try
    {
        testSetScreenSizeLarger();
        passed++;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    std::cout << "Test 9: writeToScreen" << std::endl;
    try
    {
        testWriteToScreen();
        passed++;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    std::cout << "Test 10: setScreenColours" << std::endl;
    try
    {
        testSetScreenColours();
        passed++;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    std::cout << "Passed " << passed << " of " << total << " tests" << std::endl;

    return 0;
}