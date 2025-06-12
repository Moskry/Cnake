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
    printf("Score: %d",content->Score);
}

bool SnakeMoveLeft(SharedContent* content, Queue** Tail);
bool SnakeMoveRight(SharedContent* content, Queue** Tail);
bool SnakeMoveDown(SharedContent* content, Queue** Tail);
bool SnakeMoveUp(SharedContent* content, Queue** Tail);

bool SnakeMoveV(SharedContent* content, IntTuple newPos, Queue** Tail);
bool SnakeMoveH(SharedContent* content, IntTuple newPos, Queue** Tail);

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
    int TSC = 0;

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
        if (TSC != content->Score)
        {
            if (content->Score <= 10) clock -= 10;
            else if (content->Score <= 20) clock -= 9;
            else if (content->Score <= 30) clock -= 8;
            else if (content->Score <= 40) clock -= 7;
            else if (content->Score <= 50) clock -= 6;
            else clock -= 1;
            TSC = content->Score;
        }
        Sleep(clock);
    }
}

bool SnakeMoveUp(SharedContent* content, Queue** Tail)
{
    if (content->pos->y == 0) return true;
    
    IntTuple newPos = {content->pos->x, content->pos->y - 1};

    return SnakeMoveV(content, newPos, Tail);
}

bool SnakeMoveDown(SharedContent* content, Queue** Tail)
{
    if (content->pos->y == content->Height - 1) return true;
    
    IntTuple newPos = {content->pos->x, content->pos->y + 1};
    
    return SnakeMoveV(content, newPos, Tail);
}

bool SnakeMoveRight(SharedContent* content, Queue** Tail)
{
    if (content->pos->x == content->Width * 2 - 2) return true;

    IntTuple newPos = {content->pos->x + 2, content->pos->y};

    return SnakeMoveH(content, newPos, Tail);
}

bool SnakeMoveLeft(SharedContent* content, Queue** Tail)
{
    if (content->pos->x == 0) return true;

    IntTuple newPos = {content->pos->x - 2, content->pos->y};

    return SnakeMoveH(content, newPos, Tail);
}

void OverwriteS(IntTuple pos, IntTuple endl, char* z);

bool SnakeMoveV(SharedContent* content, IntTuple newPos, Queue** Tail)
{
    bool IsApple = false;
    bool HasTail = false;
    
    if (content->Map[newPos.y][newPos.x] == 'O') return true;

    if (content->Map[newPos.y][newPos.x] == '+')
    {
        IsApple = true;
        AddTailSegment(content, Tail);
        WaitForSingleObject(content->mutex, INFINITE);
        content->Score++;
        ReleaseMutex(content->mutex);
        char score[5];
        sprintf(score, "%d", content->Score);
        OverwriteS((IntTuple){ 7, content->Height }, (IntTuple){ 7, content->Height }, score);
    }

    if ((*Tail)->Eldest) HasTail = true;

    WaitForSingleObject(content->mutex, INFINITE);
    content->Map[newPos.y][newPos.x] = '@';
    if (!HasTail) content->Map[content->pos->y][content->pos->x] = '.';
    else content->Map[content->pos->y][content->pos->x] = 'O';
    ReleaseMutex(content->mutex);

    if (IsApple) RandomNewApple(content, NULL, NULL);

    if (!HasTail) Overwrite(*(content->pos), (IntTuple){ 7, content->Height}, '.');
    else Overwrite(*(content->pos), (IntTuple){ 7, content->Height}, 'O');
    Overwrite(newPos, (IntTuple){ 7, content->Height }, '@');

    if (!IsApple) RotateTail(content, Tail); 

    WaitForSingleObject(content->mutex, INFINITE);
    content->pos->y = newPos.y;
    ReleaseMutex(content->mutex);
    
    return false;
}

bool SnakeMoveH(SharedContent* content, IntTuple newPos, Queue** Tail)
{
    bool IsApple = false;
    bool HasTail = false;
    
    if (content->Map[newPos.y][newPos.x] == 'O') return true;

    if (content->Map[newPos.y][newPos.x] == '+')
    {
        IsApple = true;
        AddTailSegment(content, Tail);
        WaitForSingleObject(content->mutex, INFINITE);
        content->Score++;
        ReleaseMutex(content->mutex);
        char score[5];
        sprintf(score, "%d", content->Score);
        OverwriteS((IntTuple){ 7, content->Height }, (IntTuple){ 7, content->Height }, score);
    }

    if ((*Tail)->Eldest) HasTail = true;

    WaitForSingleObject(content->mutex, INFINITE);
    content->Map[newPos.y][newPos.x] = '@';
    if (!HasTail) content->Map[content->pos->y][content->pos->x] = '.';
    else content->Map[content->pos->y][content->pos->x] = 'O';
    ReleaseMutex(content->mutex);

    if (IsApple) RandomNewApple(content, NULL, NULL);

    if (!HasTail) Overwrite(*(content->pos),(IntTuple){ 7, content->Height }, '.');
    else Overwrite(*(content->pos),(IntTuple){ 7, content->Height }, 'O');
    Overwrite(newPos, (IntTuple){ 7, content->Height + 1 }, '@');
    
    if (!IsApple) RotateTail(content, Tail);

    WaitForSingleObject(content->mutex, INFINITE);
    content->pos->x = newPos.x;
    ReleaseMutex(content->mutex);

    return false;
}

void Overwrite(IntTuple pos, IntTuple endl, char z)
{
     printf("\033[%d;%dH%c",pos.y + 1, pos.x + 1, z);
     printf("\033[%d;%dH",endl.y + 1, endl.x + 1);
}
void OverwriteS(IntTuple pos, IntTuple endl, char* z)
{
     printf("\033[%d;%dH%s",pos.y + 1, pos.x + 1, z);
     printf("\033[%d;%dH",endl.y + 1, endl.x + 1);
}