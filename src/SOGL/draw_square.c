#include "DisplayFuncs.h"

void draw_square(SharedContent* content, int x, int y){
    //if (sContent == NULL) return;
    WaitForSingleObject(content->mutex, INFINITE);
    //glColor4f(0.0,0.8,0.0,1.0);  // Further work on this logic needed...
    glBegin(GL_QUADS);
    glVertex2f(TOP_LEFT + BOX_STEP * x/2, TOP_LEFT + BOX_STEP * y);
    glVertex2f(TOP_LEFT + BOX_STEP * x/2, (TOP_LEFT + BOX_STEP) + BOX_STEP* y);
    glVertex2f((TOP_LEFT + BOX_STEP) + BOX_STEP * x/2,(TOP_LEFT + BOX_STEP) + BOX_STEP * y);
    glVertex2f((TOP_LEFT + BOX_STEP) + BOX_STEP * x/2, TOP_LEFT + BOX_STEP * y);
    glEnd();
    ReleaseMutex(content->mutex);
}