#include <windows.h>
#include "Snake.h"
#include "Shared.h"

typedef DWORD(WINAPI* TFunc)(LPVOID);

DWORD WINAPI MovementThread(LPVOID lParam);
DWORD WINAPI DirectionThread(LPVOID lParam);
HANDLE NewThread(int threadId, TFunc func);
