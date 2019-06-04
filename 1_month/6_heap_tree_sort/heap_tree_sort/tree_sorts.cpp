#include "tree_sorts.h"


int heapLeft(int index)
{
    return 2*index + 1;
}

int heapRight(int index)
{
    return 2*index + 2;
}

int heapParent(int index)
{
    return index / 2;
}


