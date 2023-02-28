typedef char ElementType;
typedef unsigned int Index;

#ifndef _HashSep_H
#define _HashSep_H

typedef struct ListNode *Position;

struct ListNode{
    char Element[100];
    Position Next;
};
typedef Position List;

struct HashTbl{
    int TableSize;
    List *TheLists;
};

typedef struct HashTbl *HashTable;

int Hash(char *str, int tablesize);

HashTable InitializeTable( int TableSize );
void DestroyTable( HashTable H );

Position Find( ElementType *Key, HashTable H );

void Insert( ElementType *Key, HashTable H );
ElementType *Retrieve( Position P );

HashTable Delete( ElementType X, HashTable T );
HashTable MakeEmpty(HashTable H);

#endif
