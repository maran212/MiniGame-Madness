#include "pch.h"
#include "CppUnitTest.h"
#include "../src/hnefatafl.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace HnefataflTests
{
    TEST_CLASS(HnefataflGameTest)
    {
    public:
        
		const int KING = 3;
		const int KING_SQUARE = 4;
		const int WHITE = 1;
		const int BLACK = 2;

        // Test board initialization
        TEST_METHOD(BoardInitialization)
        {
            Hnefatafl game;

            // Check the king's position
            Assert::AreEqual(KING, game.getPiece(5, 5));

            // Check the king's squares
            Assert::AreEqual(KING_SQUARE, game.getPiece(0, 0));
            Assert::AreEqual(KING_SQUARE, game.getPiece(10, 10));
            Assert::AreEqual(KING_SQUARE, game.getPiece(0, 10));
            Assert::AreEqual(KING_SQUARE, game.getPiece(10, 0));

            // Check black pieces
            Assert::AreEqual(BLACK, game.getPiece(0, 3));
            Assert::AreEqual(BLACK, game.getPiece(10, 3));
            Assert::AreEqual(BLACK, game.getPiece(1, 5));
            Assert::AreEqual(BLACK, game.getPiece(5, 1));

            // Check white pieces
            Assert::AreEqual(WHITE, game.getPiece(4, 4));
            Assert::AreEqual(WHITE, game.getPiece(5, 4));
            Assert::AreEqual(WHITE, game.getPiece(6, 4));
            Assert::AreEqual(WHITE, game.getPiece(3, 5));
        }

        // Test moving a piece
        TEST_METHOD(MovePiece)
        {
            Hnefatafl game;

            std::pair<int, int> source = std::make_pair(4, 4);
            std::pair<int, int> target = std::make_pair(4, 6);
            game.move(source, target);

            Assert::AreEqual(0, game.getPiece(4, 4));
            Assert::AreEqual(WHITE, game.getPiece(4, 6));
        }

		// Test capturing a piece vertically
        TEST_METHOD(CapturePieceVertical)
        {
            Hnefatafl game;

            // Move black pieces to surround a white piece
            game.move(std::make_pair(0, 3), std::make_pair(4, 3));
            game.move(std::make_pair(10, 3), std::make_pair(6, 3));
           
            // Check if the white piece is captured
            Assert::IsTrue(game.isCaptured(std::make_pair(5, 3)));
        }

		// Test capturing a piece horizontally
		TEST_METHOD(CapturePieceHorizontal)
		{
            Hnefatafl game;

			// Move black pieces to surround a white piece
			game.move(std::make_pair(5, 3), std::make_pair(5, 2));
			game.move(std::make_pair(0, 3), std::make_pair(5, 3));

			// Check if the white piece is captured
			Assert::IsTrue(game.isCaptured(std::make_pair(5, 2)));
		}

        // Test if the king is captured
        TEST_METHOD(KingCaptured)
        {
            Hnefatafl game;

            // Move White out of the way
            game.move(std::make_pair(5, 3), std::make_pair(9, 3));
			game.move(std::make_pair(5, 4), std::make_pair(5, 2));

            // Move King
			game.move(std::make_pair(5, 5), std::make_pair(5, 3));
			game.move(std::make_pair(5, 3), std::make_pair(1, 3));

            // Move black pieces to surround the king
            game.move(std::make_pair(1, 5), std::make_pair(1, 4));
            game.move(std::make_pair(3, 0), std::make_pair(3, 3));
            game.move(std::make_pair(3, 3), std::make_pair(2, 3));
            game.move(std::make_pair(5, 1), std::make_pair(1, 1));
			game.move(std::make_pair(1, 1), std::make_pair(1, 2));

            // Check if the king is captured
            Assert::IsTrue(game.isKingCaptured());
        }

        // Test if the game is over
        TEST_METHOD(GameOver)
        {
            Hnefatafl game;

			Assert::IsFalse(game.isGameOver());

            // Move White out of the way
            game.move(std::make_pair(5, 3), std::make_pair(9, 3));
            game.move(std::make_pair(5, 4), std::make_pair(5, 2));

            // Move King
            game.move(std::make_pair(5, 5), std::make_pair(5, 3));
            game.move(std::make_pair(5, 3), std::make_pair(1, 3));
			game.move(std::make_pair(1, 3), std::make_pair(1, 0));
			game.move(std::make_pair(1, 0), std::make_pair(0, 0));

            // Check if the game is over
            Assert::IsTrue(game.isGameOver());
        }

		// Test if getPiece returns the correct piece
        TEST_METHOD(GetPiece)
        {
            Hnefatafl game;

            // Each type
            Assert::AreEqual(KING, game.getPiece(5, 5));
            Assert::AreEqual(KING_SQUARE, game.getPiece(0, 0));
            Assert::AreEqual(BLACK, game.getPiece(0, 3));
            Assert::AreEqual(WHITE, game.getPiece(4, 4));
			Assert::AreEqual(0, game.getPiece(3, 3));

			// Out of bounds
			Assert::AreEqual(-1, game.getPiece(-1, 0));
			Assert::AreEqual(-1, game.getPiece(0, -1));
			Assert::AreEqual(-1, game.getPiece(11, 0));
			Assert::AreEqual(-1, game.getPiece(0, 11));

        }

		// Test if covertMove returns the correct pair
        TEST_METHOD(ConvertMove)
        {
            Hnefatafl game;
			std::pair<int, int> test = game.covertMove("A1");
            Assert::AreEqual(0, test.first);
			Assert::AreEqual(0, test.second);
        }

		// Test if isValidInput returns the correct boolean
        TEST_METHOD(IsValidInput)
        {
            Hnefatafl game;

            // Valid input
            Assert::IsTrue(game.isValidInput("A1 B1"));

            // Invalid input
            Assert::IsFalse(game.isValidInput("A12 A9"));
            Assert::IsFalse(game.isValidInput("A"));
            Assert::IsFalse(game.isValidInput("11 22"));
            Assert::IsFalse(game.isValidInput("AA BB"));
            Assert::IsFalse(game.isValidInput("a1 B1"));
        }
    };
}