#include "DisplayFuncs.h"

void orthogonalEnd(void)
{
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
}