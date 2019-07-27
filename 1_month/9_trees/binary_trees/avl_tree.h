#ifndef AVL_TREE_H
#define AVL_TREE_H

#include "binary_tree.h"
#include "../../6_heap_tree_sort/heap_tree_sort/tree_sorts.h"

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
class clsAVLTree : public clsBinaryTree<clsAVLTreeItem, T>
{
//protected:
//    clsAVLTreeItem<T> *_root;
public:
    clsAVLTree() : clsBinaryTree<clsAVLTreeItem, T>() { }
    clsAVLTree(T __data) : clsBinaryTree<clsAVLTreeItem, T>(__data) {}
};

#endif // AVL_TREE_H
