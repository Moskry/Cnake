#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "Shared.h"
#include "Snake.h"

void enableAnsiEscCodes()
{
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    SetConsoleMode(hOut, dwMode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
}

int main()
{
    enableAnsiEscCodes();
    IntTuple pos;
    SharedContent Shared = {20,20,'u',&pos};
    InitSnake(&Shared);
    bool GameOver = false;
    while(GameOver != true)
        SnakeMove(&Shared, &GameOver);
    FreeMap(&Shared);
    //Queue* Tail = InitQueue();
    //FreeQueue(&Tail);
    return 0;
}