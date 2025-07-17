#pragma once

#include "Structs/FullData.h"

DWORD WINAPI MovementThread(LPVOID pData);
DWORD WINAPI DirectionThread(LPVOID pData);
DWORD WINAPI MainThread(LPVOID pData);
HANDLE NewThread(DWORD *threadID, LPTHREAD_START_ROUTINE func, LPVOID pData);
int main_biz_model();
