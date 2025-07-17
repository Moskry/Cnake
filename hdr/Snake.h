#pragma once
#include "Apples.h"
#include "Graphics.h"
#include "Map.h"
#include "Overwrite.h"
#include "Queue.h"
#include "State.h"
#include "Structs/SharedContent.h"
#include "Tail.h"
#include <conio.h>
#include <ctype.h>
#include <stdbool.h>


extern bool GameOver;

void InitSnake(SharedContent *content);
void WINAPI SnakeMove(SharedContent *content, bool *GameOver, Queue **Tail);
void WINAPI DirectionSelection(SharedContent *content, bool *GameOver);
void arrow_handle(int key, int x, int y);