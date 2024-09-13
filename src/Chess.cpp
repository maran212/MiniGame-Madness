#include "chess.h"


void Chess::generateBoard2Player() {
    const int BOARD_SIZE = 8;
    const std::string columnLabels = "ABCDEFGH";


    for (int row = 1; row <= BOARD_SIZE; ++row) {
        SquareColour rowStartColour = (row % 2 == 0) ? WHITE_SQUARE : BLACK_SQUARE;

        for (int col = 1; col <= BOARD_SIZE; ++col) {
            SquareColour colour = (col % 2 == 0) ? rowStartColour : (rowStartColour == WHITE_SQUARE ? BLACK_SQUARE : WHITE_SQUARE);

            std::unique_ptr<ChessSquare> square = std::make_unique<ChessSquare>(colour);

            // Generate the position key (e.g., "A1", "B1", etc.)
            std::string position = columnLabels[col - 1] + std::to_string(row);

			// Have to use std::move to transfer ownership of the unique_ptr
            boardMap[position] = std::move(square); 
        }
    }
}
