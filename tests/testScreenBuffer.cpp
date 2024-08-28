#include "pch.h"
#include "CppUnitTest.h"
#include "../src/screenBuffer.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace testScreenBuffer
{
    TEST_CLASS(testScreenBuffer)
    {
    public:
        HANDLE handle;

        TEST_METHOD(Constructor)
        {
            screenBuffer buffer;
            Assert::AreNotEqual(INVALID_HANDLE_VALUE, buffer.getScreenHandle());
        }

        TEST_METHOD(IsActive)
        {
            screenBuffer buffer;
            Assert::IsFalse(buffer.isActive());
        }

        TEST_METHOD(GetScreenBufferWidth)
        {
            screenBuffer buffer;
            CONSOLE_SCREEN_BUFFER_INFO info;
            GetConsoleScreenBufferInfo(buffer.getScreenHandle(), &info);

            int width = static_cast<int>(info.dwSize.X);
            Assert::AreEqual(width, buffer.getScreenWidth());
        }

        TEST_METHOD(GetScreenBufferHeight)
        {
            screenBuffer buffer;
            CONSOLE_SCREEN_BUFFER_INFO info;
            GetConsoleScreenBufferInfo(buffer.getScreenHandle(), &info);

            int height = static_cast<int>(info.dwSize.Y);
            Assert::AreEqual(height, buffer.getScreenHeight());
        }

    };
}