#include <math.h>
#include <time.h>
#include "Apples.h"
#include "Shared.h"

void InitiateApples(SharedContent* shared)
{
    int counter = sqrt(shared->Height * shared->Width)/2;
    int h,w;
    srand(time(NULL));

    while (counter > 0)
    {
        do{
        h = rand() % shared->Height;
        w = rand() % shared->Width;
        } while(!(w % 2 == 0 && shared->Map[h][w*2] == '.'));

        RandomNewApple(shared, &h, &w);
        counter--;
    }
}

void RandomNewApple(SharedContent* shared, int* h, int* w)
{
    int a,b;
    if (h == NULL || w == NULL)
    {
        h = &a; w = &b;
        srand(time(NULL));
        do{
        *h = rand() % shared->Height;
        *w = rand() % shared->Width;
        } while (!(*w % 2 == 0 && shared->Map[*h][*w * 2] == '.'));
    }

    WaitForSingleObject(shared->mutex, INFINITE);
    shared->Map[*h][*w * 2] = '+';
    Overwrite((IntTuple){*w * 2, *h}, (IntTuple){shared->Width, shared->Height}, '+');
    ReleaseMutex(shared->mutex);
}
