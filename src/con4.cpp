#include <iostream>
#include "con4.h"
#include "screenBuffer.h"
/*
int grid[6][7] = { 0 };
int player1 = 1, player2 = 2; //1 for player 1, 2 for 2, 0 for empty space.*/
int currentplayer;
bool winquestionmark = false;

const wstring win = L"w";
const wstring surrender = L"s";
const wstring draw = L"d";

Con4::Con4()
{
	populategrid();
}

void Con4::endgame(wstring letter) // end game
{
    if (letter == win)
    {
        screenBuffer.writeToScreen(0, 16, L"player " + to_wstring(currentplayer) + L" wins.");

        screenBuffer.getBlockingInput();
    }
    else if (letter == surrender)
    {
        screenBuffer.writeToScreen(0, 16, L"player " + to_wstring(currentplayer) + L" surrenders.");

        screenBuffer.getBlockingInput();
    }
    else if (letter == draw)
    {
        screenBuffer.writeToScreen(0, 16, L"Draw.");

        screenBuffer.getBlockingInput();
    }

    winquestionmark = true;
}

void Con4::playerturn(int player)
{
    string diff = "0";

    do
    {
        screenBuffer.writeToScreen(0, 14, L"player " + to_wstring(player) + L"'s turn. Select a column to drop a coin.  ");

        diff = screenBuffer.getBlockingInput();

        if (grid[0][stoi(diff) - 1] != 0)
        {
            screenBuffer.writeToScreen(0, 18, L"Column is full. choose another.");
        }
    } while (grid[0][stoi(diff) - 1] != 0);

    bool repeat = true;

    while(repeat)
    {
        if (stoi(diff) == 9)
        {
            repeat = false;

            endgame(surrender);
        }
        else if (stoi(diff) >= 1 && stoi(diff) <= 7)
        {
            repeat = false;

            dropcoin(stoi(diff), player);
        }
        else
        {
            screenBuffer.writeToScreen(0, 16, L"Invalid input. Choose between 1 and 7.");

            screenBuffer.getBlockingInput();
        }
    }
}

void Con4::dropcoin(int column, int playercoin)
{
    for (int i = 5; i >= 0; i--)
    {
        if (grid[i][column - 1] == 0)
        {
            grid[i][column - 1] = playercoin;

            break;
        }
    }
}

void Con4::populategrid()
{
    for(int i = 0; i < 6; i++)
    {
        for(int j = 0; j < 7; j++)
        {
            grid[i][j] = 0;
        }
    }
}

void Con4::checkdraw()
{
    if(grid[0][0] != 0 && grid[0][1] != 0 &&grid[0][2] != 0 && grid[0][3] != 0 && grid[0][4] != 0 && grid[0][5] != 0 && grid[0][6] != 0)
    {
        endgame(draw);
    }
}

void Con4::setnum(int player, int xval, int yval)
{
    grid[yval][xval] = player;
}

void Con4::checkwin()
{
    for(int i = 0; i < 6; i++)
    {
        for(int j = 0; j < 7; j++)
        {
            if (j < 4 && grid[i][j] == grid[i][j + 1] && grid[i][j] == grid[i][j + 2] && grid[i][j] == grid[i][j + 3] && grid[i][j] != 0) // horizontal
            {
                endgame(win);
            }
            
            if (i < 3 && grid[i][j] == grid[i + 1][j] && grid[i][j] == grid[i + 2][j] && grid[i][j] == grid[i + 3][j] && grid[i][j] != 0) // vertical
            {
                endgame(win);
            }

            if (i < 3 && j < 4 && grid[i][j] == grid[i + 1][j + 1] && grid[i][j] == grid[i + 2][j + 2] && grid[i][j] == grid[i + 3][j + 3] && grid[i][j] != 0) // diagonal down right
            {
                endgame(win);
            }

            if (i > 3 && j < 4 && grid[i][j] == grid[i - 1][j + 1] && grid[i][j] == grid[i - 2][j + 2] && grid[i][j] == grid[i - 3][j + 3] && grid[i][j] != 0) // diagonal down left
            {
                endgame(win);
            }
        }
    }
}

int Con4::randomstarter()
{
    return 1 + (rand() % 2);
}

int Con4::swapturn(int playert)
{
    if (playert == 1)
    {
        return 2;
    }
    else 
    {
        return 1;
    }
}

void Con4::display()
{
    screenBuffer.writeToScreen(5, 0, L"1   2   3   4   5   6   7");
    screenBuffer.writeToScreen(3, 1, L"_____________________________");

    int offset = 2;

    for (int i = 0; i < 6; i++)
    {
        std::wstring row = L" |";

        for (int o = 0; o < 7; o++)
        {
            wstring value = to_wstring(grid[i][o]);

            if (value == L"0")
            {
                row += L"   |";
            }
            else
            {
                row += L" " + to_wstring(grid[i][o]) + L" |";
            }
        }
        
        screenBuffer.writeToScreen(2, offset++, row);

        screenBuffer.writeToScreen(3, offset++, L"-----------------------------");
    }
}

int Con4::connect4()
{
    winquestionmark = false;

    screenBuffer.setActive();

    populategrid();

    currentplayer = randomstarter();

    display();
    
    do
    {
        currentplayer = swapturn(currentplayer);

        playerturn(currentplayer);
        
        screenBuffer.clearScreen();

        display();

        checkdraw();
        
        checkwin();

    } while (winquestionmark == false);

    screenBuffer.clearScreen();

    return 0;
}