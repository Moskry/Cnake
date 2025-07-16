#pragma once
#include "DisplayFuncs.h"
#include <stdbool.h>

extern int start_button_x;
extern int start_button_y;
extern int start_button_width;
extern int start_button_height;
extern bool triangle_flag;

void start_button(void);
void start_button_click(int button, int state, int x, int y);