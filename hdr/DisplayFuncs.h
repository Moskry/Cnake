#pragma once

#include "Graphics.h"
#include "Structs/SharedContent.h"
#include "State.h"

#define TOP_LEFT 20   
#define BOX_STEP 25

void display(void);
void orthogonalStart(void);
void orthogonalEnd(void);
void reshape(int w, int h);
void draw_triangle(void);
void draw_square();