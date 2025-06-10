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

bool SnakeMoveLeft(SharedContent* content);
bool SnakeMoveRight(SharedContent* content);
bool SnakeMoveDown(SharedContent* content);
bool SnakeMoveUp(SharedContent* content);

void SnakeMoveV(SharedContent* content, IntTuple newPos);
void SnakeMoveH(SharedContent* content, IntTuple newPos);

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

void SnakeMove(SharedContent* content, bool* GameOver)
{
    DWORD clock = 500;
    bool end;
    while(*GameOver != true)
    {
        switch (content->direction)
        {
            case 'A': end = SnakeMoveLeft(content); break;
            case 'W': end = SnakeMoveUp(content); break;
            case 'S': end = SnakeMoveDown(content); break;
            case 'D': end = SnakeMoveRight(content); break;
        }
        WaitForSingleObject(content->mutex, INFINITE);
        *GameOver = end;
        ReleaseMutex(content->mutex);

        Sleep(clock);
        if (clock > 50) clock -= 5;
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
    bool IsApple = false;
    if (content->Map[newPos.y][newPos.x] == '+') IsApple = true;

    WaitForSingleObject(content->mutex, INFINITE);
    content->Map[newPos.y][newPos.x] = '@';
    content->Map[content->pos->y][content->pos->x] = '.';
    ReleaseMutex(content->mutex);

    if (IsApple) RandomNewApple(content, NULL, NULL);

    Overwrite(*(content->pos), (IntTuple){content->Width * 2, content->Height}, '.');
    Overwrite(newPos, (IntTuple){content->Width * 2, content->Height}, '@');

    WaitForSingleObject(content->mutex, INFINITE);
    content->pos->y = newPos.y;
    ReleaseMutex(content->mutex);
}

void SnakeMoveH(SharedContent* content, IntTuple newPos)
{
    bool IsApple = false;
    if (content->Map[newPos.y][newPos.x] == '+') IsApple = true;

    WaitForSingleObject(content->mutex, INFINITE);
    content->Map[newPos.y][newPos.x] = '@';
    content->Map[content->pos->y][content->pos->x] = '.';
    ReleaseMutex(content->mutex);

    if (IsApple) RandomNewApple(content, NULL, NULL);

    Overwrite(*(content->pos),(IntTuple){content->Width * 2, content->Height}, '.');
    Overwrite(newPos, (IntTuple){content->Width * 2, content->Height}, '@');
    
    WaitForSingleObject(content->mutex, INFINITE);
    content->pos->x = newPos.x;
    ReleaseMutex(content->mutex);
}

void Overwrite(IntTuple pos, IntTuple endl, char z)
{
     printf("\033[%d;%dH%c",pos.y + 1, pos.x + 1, z);
     printf("\033[%d;%dH",endl.y + 1, endl.x + 1);
}