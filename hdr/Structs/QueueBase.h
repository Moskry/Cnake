#pragma once

typedef struct QueueBase
{
    int xpos;
    int ypos;
    struct QueueBase* Next;
} QueueBase;