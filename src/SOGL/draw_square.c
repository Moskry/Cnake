#include "DisplayFuncs.h"

void draw_square(){
    glColor4f(0.0,0.8,0.0,1.0);  // Further work on this logic needed...
    glBegin(GL_QUADS);
    glVertex2f(TOP_LEFT, TOP_LEFT);
    glVertex2f(TOP_LEFT, TOP_LEFT + BOX_STEP);
    glVertex2f(TOP_LEFT + BOX_STEP, TOP_LEFT + BOX_STEP);
    glVertex2f(TOP_LEFT + BOX_STEP, TOP_LEFT);
    glEnd();
}