// RealScreenBuffer.h
#ifndef REALSCREENBUFFER_H
#define REALSCREENBUFFER_H

#include "IScreenBuffer.h"
#include "ScreenBuffer.h"

class RealScreenBuffer : public IScreenBuffer {
private:
    ScreenBuffer screenBuffer;
public:
    virtual void writeToScreen(int x, int y, const std::wstring& text) override {
        screenBuffer.writeToScreen(x, y, text);
    }

    virtual std::string getBlockingInput() override {
        return screenBuffer.getBlockingInput();
    }

    virtual void clearScreen() override {
        screenBuffer.clearScreen();
    }

    virtual void setActive() override {
        screenBuffer.setActive();
    }

    // Implement other methods if needed
};

#endif // REALSCREENBUFFER_H
