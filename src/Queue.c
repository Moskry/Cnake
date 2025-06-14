#include "Queue.h"

QueueBase* EnqueueBase(int X, int Y, QueueBase** current)
{
    QueueBase* a = (QueueBase*)malloc(sizeof(QueueBase));
    if (a)
    {
        a->xpos = X;
        a->ypos = Y;
        a->Next = NULL;
    }
    if (*current) (*current)->Next = a; 
    else *current = a;
    return a;
}
IntTuple DequeueBase(QueueBase** a)
{
    IntTuple t = {-1,-1};
    if (*a == NULL) return t;

    t.x = (*a)->xpos; 
    t.y = (*a)->ypos;
    
    QueueBase* FR = *a;
    if ((*a)->Next)
    {
        *a = (*a)->Next;
    } else *a = NULL;

    free(FR);
    return t;
}

void EnqueueF(int X, int Y, QueueBase** Latest)
{
    *Latest = EnqueueBase(X, Y, Latest);
}
IntTuple DequeueF(QueueBase** Eldest)
{
    IntTuple RV = DequeueBase(Eldest);
    return RV;
}
Queue* InitQueue()
{
    Queue* Init = (Queue*)malloc(sizeof(Queue));
    Init->Eldest = NULL;
    Init->Latest = NULL;
    Init->Enqueue = &EnqueueF;
    Init->Dequeue = &DequeueF;
    return Init;
}
void FreeQueue(Queue** Container)
{
    if (*Container == NULL) return;
    if ((*Container)->Eldest == (*Container)->Latest)
    {
        (*Container)->Latest = NULL; 
        (*Container)->Eldest->Next = NULL;
    }

    while ((*Container)->Eldest != NULL)
    {
        DequeueF(&(*Container)->Eldest);
    }   
    free(*Container);
}