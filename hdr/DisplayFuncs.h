#pragma once
#include "Graphics.h"

extern int width;
extern int height;

void display(void);
void orthogonalStart(void);
void orthogonalEnd(void);
void reshape(int w, int h);
void draw_triangle(void);