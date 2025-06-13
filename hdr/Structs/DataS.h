#pragma once
#include <windows.h>
#include <stdbool.h>
#include "Structs/SharedContent.h"

typedef struct DataS
{
    SharedContent* content;
    bool* GameOver;
} DataS;