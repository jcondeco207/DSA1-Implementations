#include "btree.h"
#include <stdlib.h>
#include "fatal.h"

struct TreeNode{
    ElementType Element;
    BTree  Left;
    BTree  Right;
};


BTree MakeEmpty( BTree T ){
    if (T!=NULL)
    {
        MakeEmpty(T->Left);
        MakeEmpty(T->Right);
        free(T);
    }
    return NULL;

}


BTree SetTree( ElementType X, BTree left, BTree right ){
    struct TreeNode *aux;

    aux=malloc(sizeof(aux));
    if (aux==NULL)
        FatalError("Out of memory");
    aux->Element=X;
    aux->Right=right;
    aux->Left=left;
}


BTree GetLeft (BTree T){
    // Assumes T != Null
    return T->Left;
}

BTree GetRight (BTree T){
    return T->Right;
}

Position Find( ElementType X, BTree T ){
    Position P;

    if (T==NULL)
        return NULL;
    if (X==T->Element)
        return T;
    P=Find(X,T->Left);

    if (P!=NULL)
        return P;
    else
        return Find(X,T->Right);
    
}


ElementType Retrieve( Position P ){
    return P->Element;
}
