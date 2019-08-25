#ifndef SPLAY_TREE_H
#define SPLAY_TREE_H

#include "binary_tree.h"

typedef enum {
    enm_ND_empty = 0,
    enm_ND_left,
    enm_ND_right
} enmNodeDirection;

template<class T>
class clsSplayTreeItem
{
protected:
    T _data;
    clsSplayTreeItem *_left;
    clsSplayTreeItem *_right;
//    clsSplayTreeItem *_parent;

    clsSplayTreeItem * liftToTop(T __data) {
        clsSplayTreeItem *res = NULL;
        clsSplayTreeItem **direction = NULL;
        enmNodeDirection nd = enm_ND_empty;
        if(__data == _data)
            res = this;
        else if(__data < _data) {
            direction = &_left;
            nd = enm_ND_left;
        }
        else {
            direction = &_right;
            nd = enm_ND_right;
        }
        if(direction && (*direction))
            res = (*direction)->liftToTop(__data);

        if(!res)
            return res;

        // lift node to top
        switch (nd) {
        case enm_ND_left:
            *direction = (*direction)->_right;
            res->_right = this;
            break;
        case enm_ND_right:
            *direction = (*direction)->_left;
            res->_left = this;
            break;
        default:
            res = this;
            break;
        }
        return res;
    }
public:
    clsSplayTreeItem() {
        memset(&_data, 0, sizeof(T));
        _left = _right = NULL;
    }
    clsSplayTreeItem(T __data) {
        _data = __data;
        _left = _right = NULL;
    }
    ~clsSplayTreeItem() {
        if(_left)
            delete _left;
        if(_right)
            delete _right;
        _left = _right = NULL;
    }

    void add(T __data) {
        clsSplayTreeItem *item = new clsSplayTreeItem(__data);
        insert(item);
    }
    void setData(T __data) {
        _data = __data;
    }
    T data() {
        return _data;
    }
    clsSplayTreeItem *left() {
        return _left;
    }
    clsSplayTreeItem *right() {
        return _right;
    }
    int height() {
        int lh = 0;
        if(_left)
            lh = _left->height();
        int rh = 0;
        if(_right)
            rh = _right->height();
        return ((lh > rh) ? lh : rh) + 1;
    }
    clsSplayTreeItem * insert(clsSplayTreeItem *__item) {
        clsSplayTreeItem** direction = NULL;
        enmNodeDirection nd = enm_ND_empty;
        if(__item->_data <= _data) {
            direction = &_left;
            nd = enm_ND_left;
        }
        else {
            direction = &_right;
            nd = enm_ND_right;
        }
        if(direction && *direction)
            *direction = (*direction)->insert(__item);
        else
            *direction = __item;

        clsSplayTreeItem *res = *direction;
        // lift inserted node to top
        switch (nd) {
        case enm_ND_left:
            *direction = (*direction)->_right;
            res->_right = this;
            break;
        case enm_ND_right:
            *direction = (*direction)->_left;
            res->_left = this;
            break;
        default:
            res = this;
            break;
        }
        return res;
    }
    clsSplayTreeItem * remove(T __data) {
        clsSplayTreeItem *res = this;
        clsSplayTreeItem** direction = NULL;
        enmNodeDirection nd = enm_ND_empty;
//        res = liftToTop(__data);

        if(__data == _data) {
            int lh = 0;
            if(_left)
                lh = _left->height();
            int rh = 0;
            if(_right)
                rh = _right->height();
            if(_left || _right) {
                if(lh > rh) {
                    direction = &_left;
                    nd = enm_ND_left;
                }
                else {
                    direction = &_right;
                    nd = enm_ND_right;
                }
                res = *direction;
            }

            switch (nd) {
            case enm_ND_left:
                *direction = (*direction)->_right;
                res->_right = this;
                direction = &res->_right;
                break;
            case enm_ND_right:
                *direction = (*direction)->_left;
                res->_left = this;
                direction = &res->_left;
                break;
            default:
                res = _left = _right = NULL;
                delete this;
                break;
            }
        }
        else
            if(__data < _data)
                direction = &_left;
            else
                direction = &_right;
        if(direction && *direction)
            *direction = (*direction)->remove(__data);
        return res;
    }
    clsSplayTreeItem * find(T __data) {
        clsSplayTreeItem *res = NULL;
        clsSplayTreeItem* direction = NULL;
        if(__data == _data)
            res = this;
        else if(__data < _data)
            direction = _left;
        else
            direction = _right;
        if(direction)
            return direction->find(__data);
        return res;
    }

};

template<class T>
class clsSplayTree : public clsBinaryTree<clsSplayTreeItem, T>
{
protected:

public:
    clsSplayTree() : clsBinaryTree<clsSplayTreeItem, T>() {}
    clsSplayTree(T data) : clsBinaryTree<clsSplayTreeItem, T>(data) {}    
    ~clsSplayTree() {
        ~clsBinaryTree<clsSplayTreeItem, T>();
    }
};

#endif // SPLAY_TREE_H
