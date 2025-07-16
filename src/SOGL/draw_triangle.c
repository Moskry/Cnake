#include "DisplayFuncs.h"

void draw_triangle(void)
{
    glColor4f(0.0,0.0,0.8,1.0);
    glBegin(GL_TRIANGLES);
        glVertex2f(100.0, 200.0);
        glVertex2f(150.0, 100.0);
        glVertex2f(200.0, 200.0);
    glEnd();
}