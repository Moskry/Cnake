#pragma once

#include "Shared.h"

typedef struct Queue Queue;
typedef struct IntTuple IntTuple;

void RotateTail(SharedContent* content, Queue** Tail);
void AddTailSegment(SharedContent* content, Queue** Tail);