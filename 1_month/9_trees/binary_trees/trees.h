#ifndef TREES_H
#define TREES_H

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
        memset(&data, 0, sizeof(T));
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

template<class T>
class clsAVLTreeItem // : public clsBinTreeItem<T>
{
protected:
    int _height;
    T _data;
    clsAVLTreeItem<T> *_left;
    clsAVLTreeItem<T> *_right;
public:
    clsAVLTreeItem() {
        _height = 1;
        memset(&_data, 0, sizeof(T));
        _left = _right = NULL;
    }
    clsAVLTreeItem(T __data) {
        _height = 1;
        _data = __data;
        _left = _right = NULL;
    }
    void add(T __data) {
        clsAVLTreeItem *item = new clsAVLTreeItem(__data);
        insert(item);
    }
    void setData(T __data) {
        _data = __data;
    }
    T data() {
        return _data;
    }
    int height() {
        return _height;
    }
    clsAVLTreeItem *left() {
        return _left;
    }
    clsAVLTreeItem *right() {
        return _right;
    }
//private:
    clsAVLTreeItem * insert(clsAVLTreeItem *__item) {
        clsAVLTreeItem** direction = NULL;
        if(__item->_data <= _data)
            direction = &_left;
        else
            direction = &_right;
        if(direction && *direction)
            *direction = (*direction)->insert(__item);
        else
            *direction = __item;
        clsAVLTreeItem *res = this;
        res = rebalance();
        res->updateHeight();
        return res;
    }
    clsAVLTreeItem * remove(T __data) {
        clsAVLTreeItem *res = this;
        clsAVLTreeItem** direction = NULL;
        if(__data == _data) {
            if(_left) {
                if(_left->right()) {
                    res = smallRightRotation();
                    direction = &res->_left;
                }
                else {
                    res = _left;
                    res->_right = _right;
                    _left = _right = NULL;
                    delete this;
                }
            }
            else {
                res = _right;
                _left = _right = NULL;
                delete this;
            }
        }
        else
            if(__data < _data)
                direction = &_left;
            else
                direction = &_right;
        if(direction && *direction)
            *direction = (*direction)->remove(__data);
        if(res) {
            res = res->rebalance();
            res->updateHeight();
        }
        return res;
    }
    clsAVLTreeItem* rebalance() {
        clsAVLTreeItem* res = this;
        int lh = 0;
        if(_left)
            lh = _left->_height;
        int rh = 0;
        if(_right)
            rh = _right->_height;
        if(abs(lh - rh) >= 2) {
            if(lh > rh)
                res = bigLeftRotation();
            else
                res = bigRightRotation();
        }
        return res;
    }
    int calcHeight() {
        int lh = 0;
        if(_left)
            lh = _left->_height;
        int rh = 0;
        if(_right)
            rh = _right->_height;
        return ((lh > rh) ? lh : rh) + 1;
    }
    void updateHeight() {
        if(_left)
            _left->_height = _left->calcHeight();
        if(_right)
            _right->_height = _right->calcHeight();
        _height = calcHeight();
    }

    clsAVLTreeItem * smallLeftRotation() {
        clsAVLTreeItem *newRoot = _right;
        _right = _right->_left;
        newRoot->_left = this;
        newRoot->updateHeight();
        return newRoot;
    }
    clsAVLTreeItem * smallRightRotation() {
        clsAVLTreeItem *newRoot = _left;
        _left = _left->_right;
        newRoot->_right = this;
        newRoot->updateHeight();
        return newRoot;
    }
    clsAVLTreeItem * bigLeftRotation() {
        if(_left->right())
            _left = _left->smallLeftRotation();
        clsAVLTreeItem *newRoot = smallRightRotation();
        newRoot->_left = newRoot->_left->rebalance();
        newRoot->updateHeight();
        return newRoot;
    }
    clsAVLTreeItem * bigRightRotation() {
        if(_right->left())
            _right = _right->smallRightRotation();
        clsAVLTreeItem *newRoot = smallLeftRotation();
        newRoot->_right = newRoot->_right->rebalance();
        newRoot->updateHeight();
        return newRoot;
    }
};

template<class T>
class clsAVLTree
{
protected:
    clsAVLTreeItem<T> *_root;
public:
    clsAVLTree() {
        _root = NULL;
    }
    clsAVLTree(T __data) {
        _root = new clsAVLTreeItem<T>(__data);
    }
    void insert(T __data) {
        clsAVLTreeItem<T> *item = new clsAVLTreeItem<T>(__data);
        if(!_root)
            _root = item;
        else
            _root = _root->insert(item);
    }
    void remove(T __data) {
        if(_root)
            _root = _root->remove(__data);
    }
    void printTree(FILE* fout, const char *title, int length = 4) {
        fprintf(fout, "%s:\n", title);
//        int length = 4;
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
        clsAVLTreeItem<T> **nodes = new clsAVLTreeItem<T>*[dim];
        memset(nodes, 0, dim * sizeof(void*));
        nodes[0] = _root;
        int count = 0;
        while(count < dim) {
            int idx = heapParent(++count);
            clsAVLTreeItem<T> *parent = nodes[idx];
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
//                for(int s=pow(2, depth-1-i)-1; s > 0; --s)
//                    fprintf(fout, "%s", emptyValue);
                if((index < dim) && nodes[index])
                    fprintf(fout, "%.*lf", length, (double)(nodes[index]->data()));
                else
                    fprintf(fout, "%s", emptyValue);
                printSpasing(depth, i, dim, 1, fout, emptyValue, dashValue);
//                for(int s=pow(2, depth-1-i)-1; s >= 0; --s)
//                    fprintf(fout, "%s", emptyValue);
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
//        if(level < depth - 1)
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


#endif // TREES_H
