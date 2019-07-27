#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include <stddef.h>
#include <cstring>
#include <stdio.h>
#include <math.h>

#include "../../6_heap_tree_sort/heap_tree_sort/tree_sorts.h"

template<class T>
class clsBinTreeItem
{
protected:
    T _data;
    clsBinTreeItem<T> *_left;
    clsBinTreeItem<T> *_right;
public:
    clsBinTreeItem() {
        memset(&_data, 0, sizeof(T));
        _left = _right = NULL;
    }
    clsBinTreeItem(T __data) {
        _data = __data;
        _left = _right = NULL;
    }
    ~clsBinTreeItem() {
        if(_left)
            delete _left;
        if(_right)
            delete _right;
    }

    clsBinTreeItem<T> *left() {
        return _left;
    }

    clsBinTreeItem<T> *right() {
        return _right;
    }
    T data() {
        return _data;
    }

    void setData(T __data) {
        _data = __data;
    }
    clsBinTreeItem* find(T __key) {
        if(__key == _data)
            return this;
        clsBinTreeItem* direction = NULL;
        if(__key < _data)
            direction = _left;
        else
            direction = _right;
        if(direction)
            return _left->find(__key);
        else
            return NULL;
    }
};

template<template<class> class T_item, class T_data>
class clsBinaryTree
{
protected:
    T_item<T_data> *_root;
public:
    clsBinaryTree() {
        _root = NULL;
    }
    clsBinaryTree(T_data __data) {
        _root = new T_item<T_data>(__data);
    }
    void insert(T_data __data) {
        T_item<T_data> *item = new T_item<T_data>(__data);
        if(!_root)
            _root = item;
        else
            _root = _root->insert(item);
    }
    void remove(T_data __data) {
        if(_root)
            _root = _root->remove(__data);
    }
    void printTree(FILE* fout, const char *title, int length = 4) {
        fprintf(fout, "%s:\n", title);
        char *emptyValue = new char[length+3];
        char *dashValue = new char[length+3];
        for(int i=0; i < length+2; ++i) {
            emptyValue[i] = ' ';
            dashValue[i] = '_';
        }
        emptyValue[length+2] = dashValue[length+2] = '\0';

        // формирование массива-кучи
        int depth = _root->height();
        fprintf(fout, "height = %i\n", depth);
        int idx = 0;
        int dim = pow(2, depth+1) - 1;
        T_item<T_data> **nodes = new T_item<T_data>*[dim];
        memset(nodes, 0, dim * sizeof(void*));
        nodes[0] = _root;
        int count = 0;
        while(count < dim) {
            int idx = heapParent(++count);
            T_item<T_data> *parent = nodes[idx];
            if(parent) {
                nodes[count] = parent->left();
                nodes[++count] = parent->right();
            }
            else
                count++;
        }

        // печать
        for(int i=0; i < depth; ++i) {
            int count = pow(2, i);
            for(int j=0; j < count; ++j) {
                int index = idx + j;
                printSpasing(depth, i, dim, 0, fout, emptyValue, dashValue);
                if((index < dim) && nodes[index])
                    fprintf(fout, "%.*lf", length, (double)(nodes[index]->data()));
                else
                    fprintf(fout, "%s", emptyValue);
                printSpasing(depth, i, dim, 1, fout, emptyValue, dashValue);
            }
            idx += pow(2, i);
            fprintf(fout, "\n");
        }
        delete[] nodes;
        delete[] emptyValue;
    }
private:
    void printSpasing(int depth, int level, int dim, bool isRight,
                      FILE *fout, char *emptes, char *dashs) {
        {
            if(!isRight) {
                for(int s=pow(2, depth-2-level); s > 0; --s)
                    fprintf(fout, "%s", emptes);
                if(level < depth - 2)
                    for(int s=pow(2, depth-2-level)-1; s > 0; --s)
                        fprintf(fout, "%s", dashs);
            }
            if(isRight) {
                if(level < depth - 2)
                    for(int s=pow(2, depth-2-level)-1; s > 0; --s)
                        fprintf(fout, "%s", dashs);
                for(int s=pow(2, depth-2-level); s >= 0; --s)
                    fprintf(fout, "%s", emptes);
            }
        }
    }
};

#endif // BINARY_TREE_H
