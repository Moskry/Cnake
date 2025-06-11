#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "Shared.h"
#include "Snake.h"
#include "Threads.h"

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
    SharedContent Shared = {20,20,'W',&pos};
    Queue* Tail = InitQueue();
    bool GameOver = false;
    Shared.mutex = CreateMutex(NULL, false, NULL);

    if (Shared.mutex == NULL) 
    {
    printf("Mutex creation failed: %d\n", GetLastError());
    return 1;
    }
    DataS data = {&Shared,&GameOver};
    InitSnake(&Shared);
    DWORD threadMID;
    DWORD threadSDID;

    HANDLE hMovement = NewThread(&threadMID, MovementThread, &data);
    HANDLE hDirection = NewThread(&threadSDID, DirectionThread, &data);

     WaitForSingleObject(hMovement, INFINITE);
     WaitForSingleObject(hDirection, INFINITE);

    CloseHandle(hMovement);
    CloseHandle(hDirection);
    FreeMap(&Shared);
    //Queue* Tail = InitQueue();
    //FreeQueue(&Tail);
    return 0;
}