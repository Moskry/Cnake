#include "Tail.h"

void AddTailSegment(SharedContent* content, Queue** Tail)
{
    (*Tail)->Enqueue(content->pos->x, content->pos->y, &(*Tail)->Latest);
    if ((*Tail)->Eldest == NULL) (*Tail)->Eldest = (*Tail)->Latest; 
}

void RotateTail(SharedContent* content, Queue** Tail)
{
    if (!(*Tail)->Eldest) return;

    IntTuple Rotated = (*Tail)->Dequeue(&(*Tail)->Eldest);
    Overwrite(Rotated, (IntTuple){content->Width, content->Height}, '.');

    AddTailSegment(content, Tail);
    //Overwrite(*position, (IntTuple){content->Width, content->Height}, 'O');
}