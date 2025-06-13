#pragma once
#include "Structs/FullData.h"

DWORD WINAPI MovementThread(LPVOID pData);
DWORD WINAPI DirectionThread(LPVOID pData);
HANDLE NewThread(DWORD* threadID, LPTHREAD_START_ROUTINE func, LPVOID pData);
