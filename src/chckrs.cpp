#include "chckrs.h"

using namespace std;

int checkersGrid[8][8];
int player1 = 1, player2 = 2, currentplaying = 1;
bool winnerquestionmark = false;

void populateCheckersGrid()
{
    for (int i = 0; i < 7; i++)
    {
        for (int j = 0; i < 7; i++)
        {
            if (i < 3 && j % 2 == 1)
            {
                checkersGrid[i][j] = 1;
            }
            else if (i > 4 && j % 2 == 0)
            {
                checkersGrid[i][j] = 2;
            }
            else
            {
                checkersGrid[i][j] = 0;
            }
        }
    }
}

void forcejump(int playerturn, string piece) // piece should be like x 1, y 0 as 10
{
    if (playerturn == 1)
    {
        if (/*piece is king && (checkersGrid[piecex - 1][piecey + 1] == 2 && checkersGrid[piecex - 2][piecey + 2] == 0) || (checkersGrid[piecex + 1][piecey + 1] == 2 && checkersGrid[piecex + 2][piecey + 2] == 0)*/true) // backward captures
        {

        }

        if (/*(checkersGrid[piecex - 1][piecey - 1] == 2 && checkersGrid[piecex - 2][piecey - 2] == 0) || (checkersGrid[piecex + 1][piecey - 1] == 2 && checkersGrid[piecex + 2][piecey - 2] == 0)*/true) // forward captures
        {

        }
    }
    else
    {
        if (/*(checkersGrid[piecex - 1][piecey - 1] == 2 && checkersGrid[piecex - 2][piecey - 2] == 0) || (checkersGrid[piecex + 1][piecey - 1] == 2 && checkersGrid[piecex + 2][piecey - 2] == 0)*/true) // backward captures
        {

        }

        if (/*piece is king && (checkersGrid[piecex - 1][piecey + 1] == 2 && checkersGrid[piecex - 2][piecey + 2] == 0) || (checkersGrid[piecex + 1][piecey + 1] == 2 && checkersGrid[piecex + 2][piecey + 2] == 0)*/true) // forward captures
        {

        }
    }
}

void checkwin()
{
    bool one = false, two = false;

    for (int i = 0; i < 7; i++)
    {
        for (int j = 0; i < 7; i++)
        {
            if (checkersGrid[i][j] == 1)
            {
                one = true;
            }
            else if (checkersGrid[i][j] == 2)
            {

            }

            cout << "\t " << (j + 1) << "shit";
        }
    }
}

void playerturn(int curre)
{

}

void move(int playerturn, string piece)
{
    if (playerturn == 1)
    {

    }
}

int randomstarter()
{
    return 1 + (rand() % 2);
}

void swapturn(int playert)
{
    if (playert == 1)
    {
        currentplaying = 2;
    }
    else {
        currentplaying = 1;
    }
}

void display()
{
    cout << "\t 1 \t 2 \t 3 \t 4 \t 5 \t 6 \t 7 \t 8 \n";

    for (int i = 0; i < 7; i++)
    {
        for (int j = 0; i < 7; i++)
        {
            cout << "\t " << (j + 1) << "shit";
        }
    }
}

void checkers()
{
    populateCheckersGrid();

    while (winnerquestionmark == false)
    {
        playerturn(currentplaying);

        checkwin();

        //checkdraw();

        swapturn(currentplaying);
    }

    string see = "seel";
    cout << see;
}