#include <stdlib.h>
#include "Shared.h"

void InitMap(SharedContent* Content)
{
    Content->Map = (char**)malloc(Content->Height * sizeof(char*));
    if (Content->Map)
    {
        for(int i = 0; i < Content->Height; i++)
        {
            Content->Map[i] = (char*)malloc(Content->Width * 2 * sizeof(char));
            for(int j = 0; j < Content->Width; j++)
            {
                Content->Map[i][j * 2] = '.';
                Content->Map[i][j * 2 + 1] = ' ';
            }
            Content->Map[i][Content->Width * 2 - 1] = 0;
        }
    }
}
void FreeMap(SharedContent* Content)
{
    for(int i = 0; i < Content->Height; i++)
    {
        free(Content->Map[i]);
    }
    free(Content->Map);
}