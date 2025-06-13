#include "Overwrite.h"

void Overwrite(IntTuple pos, IntTuple endl, char z)
{
     printf("\033[%d;%dH%c",pos.y + 1, pos.x + 1, z);
     printf("\033[%d;%dH",endl.y + 1, endl.x + 1);
}