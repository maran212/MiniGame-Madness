#ifndef GAME_H
#define GAME_H

/*!
 * @file Game.h
 * @brief Contains the declaration of the Game class and its member functions.
 * @author Angus Martin
 */

#include "screenBuffer.h"

 /*!
  * @class Game
  * @brief A parent class that represents a general game.
  */
class Game {
private:
	/*!
	 * @brief Throw an error if the result is false
	 * @param result The result of the operation
	 * @param message The message to display
	 */
	void throwError(BOOL result, const std::string& message) const
	{
		if (!result)
		{
			DWORD errorCode = GetLastError();
			std::string fullMessage = message + " Error Code: " + std::to_string(errorCode);
			throw std::runtime_error(fullMessage);
		}
	}

public:

	/*!
	 * @brief Run the game
	 * @return Whether should return to the main menu (0) or exit the program (1)
	 */
	virtual int run();
};

#endif // GAME_H