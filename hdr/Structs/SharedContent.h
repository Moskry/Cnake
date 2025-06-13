#pragma once
#include "Structs/IntTuple.h"
#include <windows.h>

typedef struct SharedContent
{
    int Width;
    int Height;
    char direction;
    IntTuple* pos;
    int Score;
    char** Map;
    HANDLE mutex;
} SharedContent;