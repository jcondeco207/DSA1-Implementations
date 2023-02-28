#include <stdlib.h>
#include <stdbool.h>
#include "queue.h"
#include "fatal.h"
#include <stdbool.h>
#include "functions.h"

#define MinQueueSize (0)

// Checks if the queue is empty
int IsEmpty(Queue Q){
    return Q->Size == 0;
}

// Checks if the queue is full
int IsFull(Queue Q){
    return Q->Size == Q->Capacity;
}

// Creates a new queue of size MaxElements
Queue CreateQueue(int MaxElements){
    Queue Q;
    
    if(MaxElements < MinQueueSize)
        Error("O tamanho definido é demasiado reduzido");
    
    Q = malloc(sizeof(struct QueueRecord));
    
    if(Q == NULL)
        FatalError("Sem espaço disponível");
    Q->Array = malloc(sizeof(ElementType) * MaxElements);
    
    if(Q->Array == NULL)
        FatalError("Sem espaço disponível");
    Q->Capacity = MaxElements;
    MakeEmpty( Q );
    return Q;
}

// Makes the queue empty
void MakeEmpty(Queue Q){
    Q->Size = 0;
    Q->Front = 1;
    Q->Rear = 0;
}

// Eliminates the queue
void DisposeQueue(Queue Q){
    if(Q != NULL){
        free(Q->Array);
        free(Q);
        
    }
}

// Returns the successor of Value
static int Succ(int Value, Queue Q){
    if(++Value == Q->Capacity)
        Value = 0;
    return Value;
}

// Inserts X in the queue Q
void Enqueue(ElementType X, Queue Q){
    if(!IsFull(Q)){
        Q->Size++;
        Q->Rear = Succ(Q->Rear, Q);
        Q->Array[Q->Rear] = X;
    }
}

ElementType Front(Queue Q){
    if(!IsEmpty(Q))
        return Q->Array[Q->Front];
    return 0;
}

// Removes the first element from the queue Q
void Dequeue(Queue Q){
    if(!IsEmpty(Q)){
        Q->Size--;
        Q->Front = Succ(Q->Front, Q);
    }
}

// Returns the value at a certain position
int returnAt(int i, Queue Q){
    return Q->Array[i];
}