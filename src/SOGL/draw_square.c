#include "DisplayFuncs.h"

void draw_square(SharedContent* content){
    glColor4f(0.0,0.8,0.0,1.0);  // Further work on this logic needed...
    glBegin(GL_QUADS);
    glVertex2f(TOP_LEFT * content->pos->x/2, TOP_LEFT * content->pos->y);
    glVertex2f(TOP_LEFT * content->pos->x/2, (TOP_LEFT + BOX_STEP)* content->pos->y);
    glVertex2f((TOP_LEFT + BOX_STEP) * content->pos->x/2,(TOP_LEFT + BOX_STEP)* content->pos->y);
    glVertex2f((TOP_LEFT + BOX_STEP) * content->pos->x/2, TOP_LEFT * content->pos->y);
    glEnd();
}