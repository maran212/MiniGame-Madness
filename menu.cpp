#include <iostream>
#include <windows.h>
#include "curser.h"

int main()
{
    // TODO: Add your code here
    hideCurser(GetStdHandle(STD_OUTPUT_HANDLE));
    Sleep(2000);
    std::cout << "Hello, World!" << std::endl;
    showCurser(GetStdHandle(STD_OUTPUT_HANDLE));

    return 0;
}