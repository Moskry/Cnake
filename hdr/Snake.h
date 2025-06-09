#pragma once

#include <stdbool.h>
#include "Shared.h"

typedef struct SharedContent SharedContent;
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