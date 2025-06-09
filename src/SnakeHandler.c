#include <stdio.h>
#include <conio.h>
#include <ctype.h>
#include "Snake.h"

void InitSnake(SharedContent* content)
{
    InitMap(content);
    content->pos->x = content->Width;
    content->pos->y = content->Height / 2;
    content->Map[content->pos->y][content->pos->x] = '@';
    for(int i = 0; i < content->Height; i++)
    {
        printf("%s\n",content->Map[i]);
    }
}

bool SnakeMoveLeft(SharedContent* content);
bool SnakeMoveRight(SharedContent* content);
bool SnakeMoveDown(SharedContent* content);
bool SnakeMoveUp(SharedContent* content);

void SnakeMoveV(SharedContent* content, IntTuple newPos);
void SnakeMoveH(SharedContent* content, IntTuple newPos);
void Overwrite(IntTuple pos, IntTuple endl, char z);

void SnakeMove(SharedContent* content, bool* GameOver)
{
    char bufferKey;
    do
    {
        bufferKey = _getch();
        bufferKey = toupper(bufferKey);
    } while(bufferKey != 'A' &&
        bufferKey != 'W' &&
        bufferKey != 'S' &&
        bufferKey != 'D');

    switch (bufferKey)
    {
        case 'A': *GameOver = SnakeMoveLeft(content); break;
        case 'W': *GameOver = SnakeMoveUp(content); break;
        case 'S': *GameOver = SnakeMoveDown(content); break;
        case 'D': *GameOver = SnakeMoveRight(content); break;
    }
}

bool SnakeMoveUp(SharedContent* content)
{
    if (content->pos->y == 0) return true;
    
    IntTuple newPos = {content->pos->x, content->pos->y - 1};

    SnakeMoveV(content, newPos);
    return false;
}

bool SnakeMoveDown(SharedContent* content)
{
    if (content->pos->y == content->Height - 1) return true;
    
    IntTuple newPos = {content->pos->x, content->pos->y + 1};
    
    SnakeMoveV(content, newPos);
    return false;
}

bool SnakeMoveRight(SharedContent* content)
{
    if (content->pos->x == content->Width * 2 - 2) return true;

    IntTuple newPos = {content->pos->x + 2, content->pos->y};

    SnakeMoveH(content, newPos);
    return false;
}

bool SnakeMoveLeft(SharedContent* content)
{
    if (content->pos->x == 0) return true;

    IntTuple newPos = {content->pos->x - 2, content->pos->y};

    SnakeMoveH(content, newPos);
    return false;
}

void SnakeMoveV(SharedContent* content, IntTuple newPos)
{
    content->Map[newPos.y][newPos.x] = '@';
    content->Map[content->pos->y][content->pos->x] = '.';
    
    Overwrite(*(content->pos), (IntTuple){content->Width * 2, content->Height}, '.');
    Overwrite(newPos, (IntTuple){content->Width * 2, content->Height}, '@');

    content->pos->y = newPos.y;
}

void SnakeMoveH(SharedContent* content, IntTuple newPos)
{
    content->Map[newPos.y][newPos.x] = '@';
    content->Map[content->pos->y][content->pos->x] = '.';
    
    Overwrite(*(content->pos),(IntTuple){content->Width * 2, content->Height}, '.');
    Overwrite(newPos, (IntTuple){content->Width * 2, content->Height}, '@');
    
    content->pos->x = newPos.x;
}

void Overwrite(IntTuple pos, IntTuple endl, char z)
{
     printf("\033[%d;%dH%c",pos.y + 1, pos.x + 1, z);
     printf("\033[%d;%dH",endl.y + 1, endl.x + 1);
}