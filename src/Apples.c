#include "Apples.h"

short countDigits(int num);

void InitiateApples(SharedContent* shared)
{
    int counter = sqrt(shared->Height * shared->Width)/2;
    while (counter > 0)
    {
        srand(time(NULL));
        int h = rand() % shared->Height;
        int w = rand() % shared->Width;
        if (shared->Map[h][w*2] == '.')
        {
            RandomNewApple(shared, h, w);
            counter--;
        }
    }
}

void RandomNewApple(SharedContent* shared, int h, int w)
{
    if (shared->Map[h][w*2] == '.')
        {
            shared->Map[h][w*2] = '+';
        }
}

short countDigits(int num)
{
    short counter = 1;
    num /= 10;
    while(num > 0)
    {
        counter++;
        num /= 10;
    }
    return counter;
}