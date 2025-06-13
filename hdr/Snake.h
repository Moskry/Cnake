#pragma once
#include <stdbool.h>
#include <conio.h>
#include <ctype.h>
#include "Structs/SharedContent.h"
#include "Map.h"
#include "Apples.h"
#include "Tail.h"
#include "Overwrite.h"
#include "Queue.h"

extern bool GameOver;

void InitSnake(SharedContent* content);
void WINAPI SnakeMove(SharedContent* content, bool* GameOver, Queue** Tail);
void WINAPI DirectionSelection(SharedContent* content, bool* GameOver);