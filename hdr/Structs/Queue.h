#pragma once
#include "Structs/QueueBase.h"
#include "Structs/IntTuple.h"

typedef struct Queue
{
    QueueBase* Latest;
    QueueBase* Eldest;
    void (*Enqueue)(int, int, QueueBase**);
    IntTuple (*Dequeue)(QueueBase**);
} Queue;