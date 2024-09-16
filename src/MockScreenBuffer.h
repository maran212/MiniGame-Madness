#pragma once
// MockScreenBuffer.h
#ifndef MOCKSCREENBUFFER_H
#define MOCKSCREENBUFFER_H

#include "IScreenBuffer.h"
#include <queue>
#include <vector>

class MockScreenBuffer : public IScreenBuffer {
public:
    std::queue<std::string> inputQueue;  // Simulated user inputs
    std::vector<std::wstring> outputs;   // Captured outputs

    virtual void writeToScreen(int x, int y, const std::wstring& text) override {
        outputs.push_back(text);
    }

    virtual std::string getBlockingInput() override {
        if (inputQueue.empty()) {
            return "";
        }
        std::string input = inputQueue.front();
        inputQueue.pop();
        return input;
    }

    virtual void clearScreen() override {
        // Optionally track clear screen calls
    }

    virtual void setActive() override {
        // Do nothing for the mock
    }

    // Implement other methods if needed
};

#endif // MOCKSCREENBUFFER_H
