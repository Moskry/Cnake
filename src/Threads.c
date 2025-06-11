#include <windows.h>
#include "Threads.h"

DWORD WINAPI MovementThread(LPVOID pData)
{
    FullData* data = (FullData*)pData;
    SnakeMove(data->content, data->GameOver, data->Tail);
    //Sleep(10000);
}

DWORD WINAPI DirectionThread(LPVOID pData)
{
    DataS* data = (DataS*)pData;
    DirectionSelection(data->content, data->GameOver);
    //Sleep(10000);
}


HANDLE NewThread(DWORD* threadID, LPTHREAD_START_ROUTINE func, LPVOID pData)
{
    HANDLE hThread;
    hThread = CreateThread(
        NULL,               // Security
        0,                  // Stack size
        func,               // func address
        pData,              // Passing parameter
        0,                  // Creation flags
        threadID                // Thread ID
    );

    return hThread;
}
