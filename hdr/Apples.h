#pragma once

#include "Shared.h"
#include "Snake.h"

typedef struct SharedContent SharedContent;

void InitiateApples(SharedContent* shared);
void RandomNewApple(SharedContent* shared, int* h, int* w);