#include "pch.h"
#include "CppUnitTest.h"
#include <iostream>
#include <cstdio>
#include "../src/ScreenBuffer.h" 

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace testScreenBuffer
{
    TEST_CLASS(testScreenBuffer)
    {
    public:
        HANDLE handle;

        TEST_METHOD(Constructor)
        {
            ScreenBuffer buffer;
            Assert::AreNotEqual(INVALID_HANDLE_VALUE, buffer.getScreenHandle());
        }

        TEST_METHOD(IsActive)
        {
            ScreenBuffer buffer;
            Assert::IsFalse(buffer.isActive());
        }

        TEST_METHOD(GetScreenBufferWidth)
        {
            ScreenBuffer buffer;
            CONSOLE_SCREEN_BUFFER_INFO info;
            GetConsoleScreenBufferInfo(buffer.getScreenHandle(), &info);

            int width = static_cast<int>(info.dwSize.X);
            Assert::AreEqual(width, buffer.getScreenWidth());
        }

        TEST_METHOD(GetScreenBufferHeight)
        {
            ScreenBuffer buffer;
            CONSOLE_SCREEN_BUFFER_INFO info;
            GetConsoleScreenBufferInfo(buffer.getScreenHandle(), &info);

            int height = static_cast<int>(info.dwSize.Y);
            Assert::AreEqual(height, buffer.getScreenHeight());
        }

        TEST_METHOD(SetScreenSizeSmaller)
        {
			ScreenBuffer buffer;
            
            buffer.setScreenSize(120, 20);
			Assert::AreEqual(120, buffer.getScreenWidth());
		    Assert::AreEqual(20, buffer.getScreenHeight());

			buffer.setScreenSize(140, 20); // Minimum screen buffer width is 120 in testing framework
			buffer.setScreenSize(120, 20);
			Assert::AreEqual(120, buffer.getScreenWidth());
			Assert::AreEqual(20, buffer.getScreenHeight());
        }

		TEST_METHOD(SetScreenSizeLarger)
		{
			ScreenBuffer buffer;

			buffer.setScreenSize(120, 40);
			Assert::AreEqual(120, buffer.getScreenWidth());
			Assert::AreEqual(40, buffer.getScreenHeight());

			buffer.setScreenSize(140, 40);
			Assert::AreEqual(140, buffer.getScreenWidth());
			Assert::AreEqual(40, buffer.getScreenHeight());
		}

        TEST_METHOD(SetCursorVisibility)
        {
			ScreenBuffer buffer;
			CONSOLE_CURSOR_INFO info;

			GetConsoleCursorInfo(buffer.getScreenHandle(), &info);
			Assert::AreEqual(TRUE, info.bVisible);

			buffer.setCursorVisibility(false);
			GetConsoleCursorInfo(buffer.getScreenHandle(), &info);
			Assert::AreEqual(FALSE, info.bVisible);
        }

        TEST_METHOD(CursorPosition)
		{
			ScreenBuffer buffer;
			buffer.setCursorPosition(7, 0);

			std::pair<int, int> pos = buffer.getCursorPosition();
			Assert::AreEqual(7, pos.first);
			Assert::AreEqual(0, pos.second);
		}

        TEST_METHOD(WriteToScreen)
        {
            ScreenBuffer buffer;
            std::wstring text = L"Hello world"; 

			buffer.writeToScreen(0, 0, text);

            // Verify the written text
            Assert::AreEqual(text, buffer.readScreenText(0,0, static_cast<int>(text.length())));
        }

		TEST_METHOD(ReadScreenText)
		{
			ScreenBuffer buffer;
			std::wstring text = L"Hello world";

			buffer.writeToScreen(0, 0, text);

			// Verify the written text
			Assert::AreEqual(text, buffer.readScreenText(0, 0, static_cast<int>(text.length())));
		}

		TEST_METHOD(GetScreenColours)
		{
			ScreenBuffer buffer;
			std::wstring text = L"Hello world";

			buffer.writeToScreen(0, 0, text, ScreenBuffer::BLUE, ScreenBuffer::RED);

			std::pair<WORD, WORD> colours = buffer.getScreenColours(0, 0, static_cast<int>(text.length()));
			Assert::AreEqual(ScreenBuffer::BLUE, colours.first);
		}

        TEST_METHOD(ClearScreen)
        {
            ScreenBuffer buffer;
            std::wstring text = L"Hello world";
            buffer.writeToScreen(0, 0, text);

            // Clear the screen
            buffer.clearScreen();

            // Verify that the screen is cleared
            std::wstring clearedText = buffer.readScreenText(0, 0, static_cast<int>(text.length()));
            Assert::AreEqual(std::wstring(text.length(), L' '), clearedText);
        }
    };
}