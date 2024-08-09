#include <iostream>

int grid[7][6];
int player1 = 1, player2 = 2; //1 for player 1, 2 for 2, 0 for empty space.
int currentplayer;
bool winquestionmark = false;

bool endgame() // 
{
    return false;
}

void playerturn(int player)
{
    
}

void populategrid()
{
    for(int i = 0; i < 7; i++)
    {
        for(int j = 0; i < 6; i++)
        {
            grid[i][j] = 0;
        }
    }
}

void dropcoin(int column, int playercoin)
{
    for (int i = 0; i < 6; i++)
    {
        if (grid[column][i-1] != 0 || i == 6)
        {
            grid[column][i] = playercoin;
            
            break;
        }
    }
}

void checkdraw()
{
    bool full = true;

    for(int i = 0; i < 6; i++)
    {
        if(grid[i][0] == 0)
        {
            full = false;
        }
    }

    if(full == true)
    {
        endgame();
    }
}

void checkwin()
{
    for(int i = 0; i < 7; i++)
    {
        for(int j = 0; i < 6; i++)
        {
            if(i < 5) // horizontal, diagonal right
            {
                if (grid[i][j] == grid[i + 1][j] && grid[i + 1][j] == grid[i + 2][j] && grid[i + 2][j] == grid[i + 3][j])
                {

                }

                if (j < 3) // vertical
                {
                    if (grid[i][j] == grid[i + 1][j + 1] && grid[i + 1][j + 1] == grid[i + 2][j + 2] && grid[i + 2][j + 2] == grid[i + 3][j + 3])
                    {

                    }
                }
            }

            if (i > 3 && j < 3) // diagonal left
            {
                if (grid[i][j] == grid[i - 1][j + 1] && grid[i - 1][j + 1] == grid[i - 2][j + 2] && grid[i - 2][j + 2] == grid[i - 3][j + 3])
                {

                }
            }

            if (j < 3) // vertical
            {
                if (grid[i][j] == grid[i][j + 1] && grid[i][j + 1] == grid[i][j + 2] && grid[i][j + 2] == grid[i][j + 3])
                {

                }
            }
        }
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
        currentplayer = 2;
    }
    else {
        currentplayer = 1;
    }
}

int main()
{
    std::cout << "Hello World" << std::endl;

    populategrid();

    currentplayer = randomstarter;

    do
    {
        playerturn(currentplayer);

        checkwin();

        checkdraw(); 

        swapturn();

    } while (winquestionmark == false);

    // sysout player # wins
}

//https://codereview.stackexchange.com/questions/184809/connect-4-in-c