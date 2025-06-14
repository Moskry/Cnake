#include "Snake.h"
#include "Threads.h"
#include "Queue.h"

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
    SharedContent Shared = {20, 20, 'W', &pos, 0};
    Queue* Tail = InitQueue();
    bool GameOver = false;
    Shared.mutex = CreateMutex(NULL, false, NULL);

    if (Shared.mutex == NULL) 
    {
        printf("Mutex creation failed: %d\n", GetLastError());
        return 1;
    }
    
    DataS data = {&Shared,&GameOver};
    FullData fdata = {&Shared, &GameOver, &Tail};
    InitSnake(&Shared);
    DWORD threadMID;
    DWORD threadSDID;

    HANDLE hMovement = NewThread(&threadMID, MovementThread, &fdata);
    HANDLE hDirection = NewThread(&threadSDID, DirectionThread, &data);

     WaitForSingleObject(hMovement, INFINITE);
     WaitForSingleObject(hDirection, INFINITE);

    CloseHandle(hMovement);
    CloseHandle(hDirection);
    FreeMap(&Shared);
    FreeQueue(&Tail);

    printf("Game over!");

    return 0;
}