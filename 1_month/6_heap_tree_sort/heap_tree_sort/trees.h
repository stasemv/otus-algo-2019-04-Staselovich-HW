#ifndef TREES_H
#define TREES_H

#include "stddef.h"

template<class T>
class clsBinTreeItem
{
protected:
    T data;
    clsBinTreeItem<T> *left;
    clsBinTreeItem<T> *right;
public:
    clsBinTreeItem() {
        left = right = NULL;
    }
    clsBinTreeItem(T data) {
        data = data;
        left = right = NULL;
    }
    ~clsBinTreeItem() {
        if(left)
            delete left;
        if(right)
            delete right;
    }

    clsBinTreeItem<T> *getLeft() {
        return left;
    }

    clsBinTreeItem<T> *getRight() {
        return right;
    }
    T getItem() {
        return data;
    }
};

#endif // TREES_H
