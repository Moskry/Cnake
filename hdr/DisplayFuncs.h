#pragma once

#include "Graphics.h"
#include "State.h"
#include "Structs/SharedContent.h"


#define TOP_LEFT 20
#define BOX_STEP 25

void display(void);
void orthogonalStart(void);
void orthogonalEnd(void);
void reshape(int w, int h);
void draw_triangle(void);
void draw_square(int i, int j);
void draw_map(void);
void draw_text(const char* text, float x, float y);