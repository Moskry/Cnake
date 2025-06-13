#pragma once
#include "Structs/DataS.h"
#include "Structs/Queue.h"

typedef struct FullData
{
    SharedContent* content;
    bool* GameOver;
    Queue** Tail;
} FullData;