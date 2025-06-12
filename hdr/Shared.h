#pragma once
#include <windows.h>
#include "Snake.h"
#include "Apples.h"
#include "Tail.h"

// Forward declarations
typedef struct Queue Queue;
typedef struct QueueBase QueueBase;
typedef struct IntTuple IntTuple;

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

typedef struct Queue
{
    QueueBase* Latest;
    QueueBase* Eldest;
    void (*Enqueue)(int, int, QueueBase**);
    IntTuple (*Dequeue)(QueueBase**);
} Queue;

typedef struct QueueBase
{
    int xpos;
    int ypos;
    struct QueueBase* Next;
} QueueBase;

typedef struct IntTuple
{
    int x;
    int y;
}IntTuple;

// Queue-based methods
QueueBase* EnqueueBase(int X, int Y, QueueBase** current);
IntTuple DequeueBase(QueueBase** a);

void EnqueueF(int X, int Y, QueueBase** Latest);
IntTuple DequeueF(QueueBase** Eldest);

Queue* InitQueue();
void FreeQueue(Queue** Container);

// Map-based methods
void InitMap(SharedContent* Content);
void FreeMap(SharedContent* Content);