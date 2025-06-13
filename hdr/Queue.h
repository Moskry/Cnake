#pragma once
#include <stdlib.h>
#include "Structs/Queue.h"

QueueBase* EnqueueBase(int X, int Y, QueueBase** current);
IntTuple DequeueBase(QueueBase** a);

void EnqueueF(int X, int Y, QueueBase** Latest);
IntTuple DequeueF(QueueBase** Eldest);

Queue* InitQueue();
void FreeQueue(Queue** Container);