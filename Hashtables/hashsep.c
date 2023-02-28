#include "fatal.h"
#include "hashsep.h"
#include <stdlib.h>
#include <string.h>


#define MinTableSize (10)

typedef unsigned int Index;

static int NextPrime( int N ){
    int i;
    if( N % 2 == 0 )
        N++;
    for( ; ; N += 2 ){
        for( i = 3; i * i <= N; i += 2 )
            if( N % i == 0 )
                goto ContOuter;
        return N;
    ContOuter: ;
        
    }
}

/* Hash function for strings */
int Hash(char *str, int tablesize){
    char *converted = RetConvert(normalize(str));
    return NewHash(converted, tablesize);
}


HashTable InitializeTable( int TableSize ){
    HashTable H;
    int i;

    /* Check TableSize */
    if( TableSize < MinTableSize ){
        Error( "Table size too small" );
        return NULL;
        
    }

    /* Allocate table */

    H = malloc( sizeof( struct HashTbl ) );
    if( H == NULL )
    FatalError( "Out of space!!!" );
    H->TableSize = NextPrime( TableSize );
    
    /* Allocate array of lists */
    
    H->TableSize = NextPrime( TableSize );
    H->TheLists = malloc( sizeof(List) * H->TableSize );
    if( H->TheLists == NULL )
        FatalError( "Out of space!!!" );


    /* Allocate list headers */
    
    for( i = 0; i < H->TableSize; i++ ){
        H->TheLists[ i ] = malloc( sizeof( struct ListNode ) );
        if( H->TheLists[ i ] == NULL )
            FatalError( "Out of space!!!" );
        else
            H->TheLists[ i ]->Next = NULL;
    }
    
    return H;
}


void DestroyTable( HashTable H ){
    int i;
    for( i = 0; i < H->TableSize; i++ )
    {
        Position P = H->TheLists[ i ];
        Position Tmp;
        
        while( P != NULL ){
            Tmp = P->Next;
            free( P );
            P = Tmp;
        }
    }
    free( H->TheLists );
    free( H );
}

Position Find( char *Key, HashTable H ){
    Position P;
    List L;
    L = H->TheLists[ Hash( Key, H->TableSize ) ];
    P = L->Next;
    while( P != NULL && strcmp(P->Element, Key))
        P = P->Next;
    return P;
}


void Insert( char *Key, HashTable H ){
    Position Pos, NewCell;
    List L;
    
    Pos = Find( Key, H );
    if( Pos == NULL )   /* Key is not found */{
        NewCell = malloc( sizeof( struct ListNode ) );
        if( NewCell == NULL )
            FatalError( "Out of space!!!" );
        else{
            L = H->TheLists[ Hash( Key, H->TableSize ) ];
            Position P = L;
            
            NewCell->Next = P->Next;
            strcpy(NewCell->Element, Key);
            P->Next = NewCell;
        }
    }
}

HashTable MakeEmpty(HashTable H){
    DestroyTable(H);
    HashTable Y = InitializeTable(tablesz);
    return Y;
}

char *Retrieve( Position P ){
    return P->Element;
}

