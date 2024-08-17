#include "hnefatafl.h"

int board[BOARD_SIZE][BOARD_SIZE] = { 0 };
int currentPlayer = BLACK;

/**
* Generates the board for the game (1 = white, 2 = black, 3 = king, 4 = king square's 0 = empty)
* @return void
*/
void populateBoard()
{
    populateBlackSquares();
    populateWhiteSquares();

    // Start square for the king
    board[5][5] = KING;

    // King's square
    board[0][0] = KING_SQUARE;
    board[10][10] = KING_SQUARE;
    board[0][10] = KING_SQUARE;
    board[10][0] = KING_SQUARE;
}

/**
* Populates the board with the black squares
* @return void
*/
void populateBlackSquares()
{
    // Set black squares
    for (int col = 3; col < 8; col++)
    {
        board[0][col] = BLACK;
        board[10][col] = BLACK;
    }

    for (int row = 3; row < 8; row++)
    {
        board[row][0] = BLACK;
        board[row][10] = BLACK;
    }

    // Set additional black squares
    board[1][5] = BLACK;
    board[9][5] = BLACK;
    board[5][1] = BLACK;
    board[5][9] = BLACK;
}

/**
* Populates the board with the white squares
* @return void
*/
void populateWhiteSquares()
{
    // Set white squares
    for (int col = 4; col < 7; col++)
    {
        board[4][col] = WHITE;
        board[5][col] = WHITE;
        board[6][col] = WHITE;
    }

    // Set additional white squares
    board[3][5] = WHITE;
    board[7][5] = WHITE;
    board[5][3] = WHITE;
    board[5][7] = WHITE;
}

/**
* Moves the piece
* @param std::pair<int, int> source
* @param std::pair<int, int> target
* @return std::pair<int, int> new position
*/
std::pair<int, int> move(std::pair<int, int> source, std::pair<int, int> target)
{
    // Get the source and target coordinates
    int sourceRow = source.first;
    int sourceCol = source.second;
    int targetRow = target.first;
    int targetCol = target.second;

	// Current player
	currentPlayer = board[sourceRow][sourceCol];

    // Current position
	int currentRow = sourceRow;
	int currentCol = sourceCol;

	// Move piece up if the target row is less than the current row
	if (currentRow > targetRow && currentCol == targetCol)
	{
		while (currentRow > targetRow)
		{
			if (board[currentRow-1][currentCol] == 0)
			{
				currentRow--;
			}
            else
            {
                break;
            }
		}
	}

	// Move piece down if the target row is greater than the current row
    if (currentRow < targetRow && currentCol == targetCol)
    {
        while (currentRow < targetRow)
        {
            if(board[currentRow+1][currentCol] == 0)
			{
				currentRow++;
			}
			else
			{
				break;
			}
		}
	}

	// Move piece left if the target column is less than the current column
	if (currentCol > targetCol && currentRow == targetRow)
	{
		while (currentCol > targetCol)
		{
			if (board[currentRow][currentCol - 1] == 0)
			{
				currentCol--;
			}
			else
			{
				break;
			}
		}
	}

	// Move piece right if the target column is greater than the current column
	if (currentCol < targetCol && currentRow == targetRow)
	{
		while (currentCol < targetCol)
		{
			if (board[currentRow][currentCol + 1] == 0)
			{
				currentCol++;
			}
			else
			{
				break;
			}
		}
	}

	// Set Current position to the piece of current player
	board[currentRow][currentCol] = currentPlayer;
	
    // Return the new postion of the piece 
    return std::make_pair(currentRow, currentCol);
}

/**
* Checks if pice is captured
* @param std::pair<int, int> source
* @return bool true if piece is captured
*/
bool isCaptured(std::pair<int, int> source)
{
	// Intialize neighbors of the piece
	int up, down, left, right;

	// Get the source coordinates
	int sourceRow = source.first;
	int sourceCol = source.second;

	// Player's piece
	currentPlayer = board[sourceRow][sourceCol];

	// Get Opponent's piece
	int opponentPlayer = (currentPlayer == WHITE) ? BLACK : WHITE;

	// Get the neighbors of the piece depending if the piece is on the edge of the board
	if (sourceRow == 0 || sourceRow == 10)
	{
		up = -1;
		down = -1;
		left = board[sourceRow][sourceCol - 1];
		right = board[sourceRow][sourceCol + 1];
	}
	else if (sourceCol == 0 || sourceCol == 10)
	{
		up = board[sourceRow - 1][sourceCol];
		down = board[sourceRow + 1][sourceCol];
		left = -1;
		right = -1;
	}
	else
	{
		up = board[sourceRow - 1][sourceCol];
		down = board[sourceRow + 1][sourceCol];
		left = board[sourceRow][sourceCol - 1];
		right = board[sourceRow][sourceCol + 1];
	}

	// Check if the piece is captured
	if ((up == opponentPlayer || up == KING_SQUARE) && (down == opponentPlayer || down == KING_SQUARE)) {
		return true;
	}
	else if ((left == opponentPlayer || left == KING_SQUARE) && (right == opponentPlayer || right == KING_SQUARE)) {
		return true;
	}

	return false;
}

/**
* Checks if the king is captured
* @return bool true if king is captured
*/
bool isKingCaptured()
{
	// Intialize position of the king and neighbors
	int kingRow, kingCol, up, down, left, right;

	// Get the king's position
	for (int row = 0; row < BOARD_SIZE; row++)
	{
		for (int col = 0; col < BOARD_SIZE; col++)
		{
			if (board[row][col] == KING)
			{
				kingRow = row;
				kingCol = col;
			}
		}
	}

	// Find neighbors of the king
	if (kingRow == 0)
	{
		up = -1;
		down = board[kingRow + 1][kingCol];
		left = board[kingRow][kingCol - 1];
		right = board[kingRow][kingCol + 1];
	}
	else if (kingRow == 10)
	{
		up = board[kingRow - 1][kingCol];
		down = -1;
		left = board[kingRow][kingCol - 1];
		right = board[kingRow][kingCol + 1];
	}
	else if (kingCol == 0)
	{
		up = board[kingRow - 1][kingCol];
		down = board[kingRow + 1][kingCol];
		left = -1;
		right = board[kingRow][kingCol + 1];
	}
	else if (kingCol == 10)
	{
		up = board[kingRow - 1][kingCol];
		down = board[kingRow + 1][kingCol];
		left = board[kingRow][kingCol - 1];
		right = -1;
	}
	else
	{
		up = board[kingRow - 1][kingCol];
		down = board[kingRow + 1][kingCol];
		left = board[kingRow][kingCol - 1];
		right = board[kingRow][kingCol + 1];
	}

	// Check if the king is captured
	if (up == BLACK && down == BLACK && left == BLACK && right == BLACK)
	{
		return true;
	}


	return false;
}

/**
* Checks if the game is over
* @return bool true if the game is over
*/
bool isGameOver()
{
	// Check if the king is captured
	if (isKingCaptured())
	{
		return true;
	}

	// Check if the king has reached the king's square
	for (int row = 0; row < BOARD_SIZE; row++)
	{
		for (int col = 0; col < BOARD_SIZE; col++)
		{
			if (board[row][col] == KING && (row == 0 || row == 10) && (col == 0 || col == 10))
			{
				return true;
			}
		}
	}

	return false;
}