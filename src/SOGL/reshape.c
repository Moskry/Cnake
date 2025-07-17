#include "DisplayFuncs.h"

void reshape(int w, int h)
{
    if (w != width || h != height)
    {
        glutReshapeWindow(width, height);  // Deprecated
    }
}