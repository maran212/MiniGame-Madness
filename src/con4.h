#ifndef CON4_H
#define CON4_H

#include "screenBuffer.h"

using namespace std;

/*!
 * @file con4.h
 * @brief Contains the declaration of the Connect4 class and its member functions.
 */

/*!
 * @class Con4
 * @brief Class to handle the Connect 4 game logic.
 */
class Con4 {
private:
    int grid[6][7];
	int player1 = 1, player2 = 2; //1 for player 1, 2 for 2, 0 for empty space.
    int currentplayer;
    bool winquestionmark = false;

    ScreenBuffer screenBuffer;

    /*!
     * @brief Ends game when called with specific values.
     * @param s for surrender, w for win, d for draw.
     */
    void endgame(wstring letter);

public:
    /*!
     * @brief Constructor for the Connect4 class.
     */
    Con4();

    /*!
     * @brief Populates the game grid with initial values.
     */
    void populategrid();

    /*!
     * @brief Drops a coin into the specified column.
     * @param column The column to drop the coin into.
     * @param playercoin The coin of the player.
     */
    void dropcoin(int column, int playercoin);

    /*!
     * @brief Checks if the game is a draw.
     */
    void checkdraw();

    /*!
    * @brief Manually sets a position as a value given.
    * @param player The player coin dropped
    * @param xval The x coordinate of the value to be changed
    * @param yval The y coordinate of the value to be changed
    */
    void setnum(int player, int xval, int yval);

    /*!
     * @brief Checks if there is a winning condition on the board.
     */
    void checkwin();

    /*!
     * @brief Randomly selects the starting player.
     * @return int The starting player (1 or 2).
     */
    int randomstarter();

    /*!
     * @brief Swaps the turn between players.
     * @param playert The current player.
     */
    int swapturn(int playert);

    /*!
     * @brief Handles the player's turn.
     * @param player The current player.
     */
    void playerturn(int player);

    /*!
     * @brief Handles the display of the grid.
     */
    void display();

    /*!
     * @brief Main function to run the Connect 4 game.
     */
    int connect4();
};

#endif // CON4_H
