#include "pch.h"
#include "../src/NaughtsxCrossess.h"
#include <iostream>
#include <stdexcept>
#include <string>

// Assertion functions

bool assertEqual(const std::string &expected, const std::string &actual)
{
    if (expected != actual)
    {
        throw std::runtime_error("Expected: " + expected + " | Actual: " + actual);
    }
    return true;
}

bool assertEqual(const int expected, const int actual)
{
    if (expected != actual)
    {
        throw std::runtime_error("Expected: " + std::to_string(expected) + " | Actual: " + std::to_string(actual));
    }
    return true;
}

bool assertTrue(const bool actual)
{
    if (!actual)
    {
        throw std::runtime_error("Expected: true | Actual: false");
    }
    return true;
}

// Test functions

bool testEvaluateEmptyBoard()
{
    // Reset the board to an empty state
    for (int i = 0; i < SIZE; ++i)
        for (int j = 0; j < SIZE; ++j)
            board[i][j] = ' ';
    
    // Test that the evaluation of an empty board is 0
    return assertEqual(0, evaluate());
}

bool testEvaluateRowVictory()
{
    // Simulate a row victory for 'x'
    board[0][0] = board[0][1] = board[0][2] = 'x';
    return assertEqual(10, evaluate());
}

bool testEvaluateColumnVictory()
{
    // Reset the board and simulate a column victory for 'o'
    for (int i = 0; i < SIZE; ++i)
        for (int j = 0; j < SIZE; ++j)
            board[i][j] = ' ';
    
    board[0][1] = board[1][1] = board[2][1] = 'o';
    return assertEqual(-10, evaluate());
}

bool testEvaluateDiagonalVictory()
{
    // Reset the board and simulate a diagonal victory for 'x'
    for (int i = 0; i < SIZE; ++i)
        for (int j = 0; j < SIZE; ++j)
            board[i][j] = ' ';
    
    board[0][0] = board[1][1] = board[2][2] = 'x';
    return assertEqual(10, evaluate());
}

bool testFindBestMove()
{
    // Reset the board and set up a scenario
    for (int i = 0; i < SIZE; ++i)
        for (int j = 0; j < SIZE; ++j)
            board[i][j] = ' ';
    
    board[0][0] = 'x';
    board[0][1] = 'x';
    board[0][2] = ' ';
    
    auto bestMove = findBestMove(3);
    return assertEqual(std::make_pair(0, 2), bestMove);
}

int main()
{
    int passed = 0;
    int total = 5;

    std::cout << "Running tests..." << std::endl;

    std::cout << "Test 1: Evaluate Empty Board" << std::endl;
    try
    {
        testEvaluateEmptyBoard();
        passed++;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    std::cout << "Test 2: Evaluate Row Victory" << std::endl;
    try
    {
        testEvaluateRowVictory();
        passed++;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    std::cout << "Test 3: Evaluate Column Victory" << std::endl;
    try
    {
        testEvaluateColumnVictory();
        passed++;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    std::cout << "Test 4: Evaluate Diagonal Victory" << std::endl;
    try
    {
        testEvaluateDiagonalVictory();
        passed++;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    std::cout << "Test 5: Find Best Move" << std::endl;
    try
    {
        testFindBestMove();
        passed++;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    std::cout << "Passed " << passed << " of " << total << " tests" << std::endl;

    return 0;
}
