#include "Tail.h"

void AddTailSegment(SharedContent* content, Queue** Tail)
{
    (*Tail)->Enqueue(content->pos->x, content->pos->y, &(*Tail)->Latest);
    if ((*Tail)->Eldest == NULL) (*Tail)->Eldest = (*Tail)->Latest; 
}

void RotateTail(SharedContent* content, IntTuple* position, Queue** Tail)
{
    if (!(*Tail)->Eldest) return;
    
    IntTuple Rotated = (*Tail)->Dequeue(&(*Tail)->Eldest);
    Overwrite(Rotated, (IntTuple){content->Width, content->Height}, '.');

    (*Tail)->Enqueue(position->x, position->y, &(*Tail)->Latest);
    Overwrite(*position, (IntTuple){content->Width, content->Height}, 'O');
}