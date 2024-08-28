#ifndef CON4_H
#define CON4_H

/*!
 * @file con4.h
 * @brief Contains the declaration of the Connect4 class and its member functions.
 */

/*!
 * @class Connect4
 * @brief Class to handle the Connect 4 game logic.
 */
class Con4 {
private:
    int grid[7][6];
	int player1 = 1, player2 = 2; //1 for player 1, 2 for 2, 0 for empty space.
    int currentplayer;
    bool winquestionmark = false;

    /*!
     * @brief Checks if the game has ended.
     * @return bool True if the game has ended, false otherwise.
     */
    bool endgame();

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
    void swapturn(int playert);

    /*!
     * @brief Handles the player's turn.
     * @param player The current player.
     */
    void playerturn(int player);

    /*!
     * @brief Main function to run the Connect 4 game.
     */
    void connect4();
};

#endif // CON4_H
