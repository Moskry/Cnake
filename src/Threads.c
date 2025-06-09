#include <windows.h>
#include "Threads.h"

DWORD WINAPI MovementThread(LPVOID lParam)
{
    
}

DWORD WINAPI DirectionThread(LPVOID lParam)
{

}

HANDLE NewThread(int threadId, TFunc func)
{
    HANDLE hThread;
    hThread = CreateThread(
        NULL,               // Security
        0,                  // Stack size
        func,               // Executing function
        &threadId,          // Passing parameter
        0,                  // Creation flags
        NULL                // Thread ID
    );

    return hThread;
}