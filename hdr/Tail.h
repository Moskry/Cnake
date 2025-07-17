#pragma once
#include "Overwrite.h"
#include "Structs/Queue.h"
#include "Structs/SharedContent.h"


void RotateTail(SharedContent *content, Queue **Tail);
void AddTailSegment(SharedContent *content, Queue **Tail);