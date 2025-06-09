#include <windows.h>
#include "Snake.h"
#include "Shared.h"

typedef struct DataS
{
    SharedContent* content;
    bool* GameOver;
} DataS;

DWORD WINAPI MovementThread(LPVOID pData);
DWORD WINAPI DirectionThread(LPVOID pData);
HANDLE NewThread(DWORD* threadID, LPTHREAD_START_ROUTINE func, LPVOID pData);
