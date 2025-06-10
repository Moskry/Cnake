#pragma once

#include <stdbool.h>
#include "Shared.h"
#include "Apples.h"

typedef struct SharedContent SharedContent;
typedef struct IntTuple IntTuple;
extern bool GameOver;

typedef struct {
    bool left;
    bool right;
    bool up;
    bool down;
} KeyStates;

void InitSnake(SharedContent* content);
void WINAPI SnakeMove(SharedContent* content, bool* GameOver);
void WINAPI DirectionSelection(SharedContent* content, bool* GameOver);
void Overwrite(IntTuple pos, IntTuple endl, char z);