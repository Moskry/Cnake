#pragma once
#include "Structs/SharedContent.h"
#include "Structs/Queue.h"
#include "Overwrite.h"

void RotateTail(SharedContent* content, Queue** Tail);
void AddTailSegment(SharedContent* content, Queue** Tail);