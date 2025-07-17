#include "DisplayFuncs.h"

void reshape(int w, int h) // Deprecated
{
    if (w != width || h != height)
    {
        glutReshapeWindow(width, height);  
    }
}