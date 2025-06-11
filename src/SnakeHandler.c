#include <stdio.h>
#include <conio.h>
#include <ctype.h>
#include "Snake.h"
#include "Apples.h"

void InitSnake(SharedContent* content)
{
    InitMap(content);

    content->pos->x = content->Width;
    content->pos->y = content->Height / 2;
    content->Map[content->pos->y][content->pos->x] = '@';
    
    InitiateApples(content);

    printf("\033[2J\033[H");
    for(int i = 0; i < content->Height; i++)
    {
        printf("%s\n",content->Map[i]);
        fflush(stdout);
    }
}

bool SnakeMoveLeft(SharedContent* content, Queue** Tail);
bool SnakeMoveRight(SharedContent* content, Queue** Tail);
bool SnakeMoveDown(SharedContent* content, Queue** Tail);
bool SnakeMoveUp(SharedContent* content, Queue** Tail);

void SnakeMoveV(SharedContent* content, IntTuple newPos, Queue** Tail);
void SnakeMoveH(SharedContent* content, IntTuple newPos, Queue** Tail);

void DirectionSelection(SharedContent* content, bool* GameOver)
{
    char bufferKey;
    while(*GameOver != true)
    {

        do
        {
            bufferKey = _getch();
            bufferKey = toupper(bufferKey);
        } while(bufferKey != 'A' &&
            bufferKey != 'W' &&
            bufferKey != 'S' &&
            bufferKey != 'D');

        WaitForSingleObject(content->mutex, INFINITE);
        content->direction = bufferKey;
        ReleaseMutex(content->mutex);
    }
}

void SnakeMove(SharedContent* content, bool* GameOver, Queue** Tail)
{
    DWORD clock = 500;
    bool end;
    while(*GameOver != true)
    {
        switch (content->direction)
        {
            case 'A': end = SnakeMoveLeft(content, Tail); break;
            case 'W': end = SnakeMoveUp(content, Tail); break;
            case 'S': end = SnakeMoveDown(content, Tail); break;
            case 'D': end = SnakeMoveRight(content, Tail); break;
        }
        WaitForSingleObject(content->mutex, INFINITE);
        *GameOver = end;
        ReleaseMutex(content->mutex);

        Sleep(clock);
        if (clock > 50) clock -= 5;
    }
}

bool SnakeMoveUp(SharedContent* content, Queue** Tail)
{
    if (content->pos->y == 0) return true;
    
    IntTuple newPos = {content->pos->x, content->pos->y - 1};

    SnakeMoveV(content, newPos, Tail);
    return false;
}

bool SnakeMoveDown(SharedContent* content, Queue** Tail)
{
    if (content->pos->y == content->Height - 1) return true;
    
    IntTuple newPos = {content->pos->x, content->pos->y + 1};
    
    SnakeMoveV(content, newPos, Tail);
    return false;
}

bool SnakeMoveRight(SharedContent* content, Queue** Tail)
{
    if (content->pos->x == content->Width * 2 - 2) return true;

    IntTuple newPos = {content->pos->x + 2, content->pos->y};

    SnakeMoveH(content, newPos, Tail);
    return false;
}

bool SnakeMoveLeft(SharedContent* content, Queue** Tail)
{
    if (content->pos->x == 0) return true;

    IntTuple newPos = {content->pos->x - 2, content->pos->y};

    SnakeMoveH(content, newPos, Tail);
    return false;
}

void SnakeMoveV(SharedContent* content, IntTuple newPos, Queue** Tail)
{
    bool IsApple = false;
    bool HasTail = false;
    
    if (content->Map[newPos.y][newPos.x] == '+')
    {
        IsApple = true;
        AddTailSegment(content, Tail);
    }

    if ((*Tail)->Eldest) HasTail = true;

    WaitForSingleObject(content->mutex, INFINITE);
    content->Map[newPos.y][newPos.x] = '@';
    if (!HasTail) content->Map[content->pos->y][content->pos->x] = '.';
    else content->Map[content->pos->y][content->pos->x] = 'O';
    ReleaseMutex(content->mutex);

    if (IsApple) RandomNewApple(content, NULL, NULL);

    if (!HasTail) Overwrite(*(content->pos), (IntTuple){content->Width * 2, content->Height}, '.');
    else Overwrite(*(content->pos), (IntTuple){content->Width * 2, content->Height}, 'O');
    Overwrite(newPos, (IntTuple){content->Width * 2, content->Height}, '@');

    if (!IsApple) RotateTail(content, Tail); 

    WaitForSingleObject(content->mutex, INFINITE);
    content->pos->y = newPos.y;
    ReleaseMutex(content->mutex);
}

void SnakeMoveH(SharedContent* content, IntTuple newPos, Queue** Tail)
{
    bool IsApple = false;
    bool HasTail = false;
    
    if (content->Map[newPos.y][newPos.x] == '+')
    {
        IsApple = true;
        AddTailSegment(content, Tail);
    }

    if ((*Tail)->Eldest) HasTail = true;

    WaitForSingleObject(content->mutex, INFINITE);
    content->Map[newPos.y][newPos.x] = '@';
    if (!HasTail) content->Map[content->pos->y][content->pos->x] = '.';
    else content->Map[content->pos->y][content->pos->x] = 'O';
    ReleaseMutex(content->mutex);

    if (IsApple) RandomNewApple(content, NULL, NULL);

    if (!HasTail) Overwrite(*(content->pos),(IntTuple){content->Width * 2, content->Height}, '.');
    else Overwrite(*(content->pos),(IntTuple){content->Width * 2, content->Height}, 'O');
    Overwrite(newPos, (IntTuple){content->Width * 2, content->Height}, '@');
    
    if (!IsApple) RotateTail(content, Tail);

    WaitForSingleObject(content->mutex, INFINITE);
    content->pos->x = newPos.x;
    ReleaseMutex(content->mutex);
}

void Overwrite(IntTuple pos, IntTuple endl, char z)
{
     printf("\033[%d;%dH%c",pos.y + 1, pos.x + 1, z);
     printf("\033[%d;%dH",endl.y + 1, endl.x + 1);
}