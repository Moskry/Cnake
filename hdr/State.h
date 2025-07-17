#pragma once
#include "Structs/Queue.h"
#include "Structs/SharedContent.h"
#include <stdbool.h>
#include <windows.h>

extern int width;
extern int height;
extern int start_button_x;
extern int start_button_y;
extern int start_button_width;
extern int start_button_height;
extern bool start_flag;
extern HANDLE game_handle;
extern DWORD main_id;
extern bool button_blocker;
extern bool init_map;

// from main business logic
extern IntTuple pos;
extern SharedContent sContent;
extern Queue *sTail;