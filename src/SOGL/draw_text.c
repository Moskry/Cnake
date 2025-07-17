#include "DisplayFuncs.h"

void draw_text(const char *text, float x, float y) {
  glRasterPos2f(x, y);
  for (const char *c = text; *c != 0; c++) {
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);
  }
}