#include "stackar.h"
#include "fatal.h"
#include <stdlib.h>


#define EmptyTOS ( -1 )
#define MinStackSize ( 5 )


struct StackRecord{
    int Capacity;
    int TopOfStack;
    ElementType *Array;
};



Stack CreateStack( int MaxElements ){

    Stack S;	

	if( MaxElements < MinStackSize )
		Error( "Stack size is too small" );

	S = malloc( sizeof( struct StackRecord ) );
	if( S == NULL )
		FatalError( "Out of space!!!" );

	S->Array = malloc( sizeof( ElementType ) * MaxElements );
	if( S->Array == NULL )
		FatalError( "Out of space!!!" );

	S->Capacity = MaxElements;
	MakeEmpty( S );

	return S;
}



void DisposeStack( Stack S ){
    if( S != NULL )
    {
        free( S->Array );
        free( S );
    }
}


int IsEmpty( Stack S ){
    if(S->TopOfStack == -1){
        return 1;
    }
    else
        return 0;
}


int IsFull( Stack S ){
    if(S->TopOfStack >= S->Capacity){
        return 1;
    }
    else
        return 0;
}


void MakeEmpty( Stack S ){
    while(S->TopOfStack != EmptyTOS){
        Pop(S);
    }
}


void Push( ElementType X, Stack S ){
    if(!IsFull(S)){
        S->TopOfStack +=1;
        S->Array[S->TopOfStack] = X;
    }
    else
        printf("\nA Stack está cheia.\n");
}


ElementType Top( Stack S ){
    if(!IsEmpty(S)){
        return S->Array[S->TopOfStack];
    }
    else
        return EmptyTOS;
}


ElementType Pop( Stack S ){
    if(!IsEmpty(S)){
        int x = S->TopOfStack;
        S->TopOfStack -= 1;
        return S->Array[x];
    }
    else
        return EmptyTOS;
}
