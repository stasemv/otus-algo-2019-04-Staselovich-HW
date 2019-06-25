#ifndef LISTS_H
#define LISTS_H

#include "stddef.h"

template<class T>
class clsListNode
{
protected:
    clsListNode<T> *_next;
    T _data;
public:
    clsListNode() {
        _next = NULL;
    }
    clsListNode(T *__item) {
        _data = *__item;
        _next = NULL;
    }
    clsListNode(T *__item, clsListNode<T> *__next) {
        _data = *__item;
        _next = __next;
    }
    T getItem() {
        return _data;
    }
    T *getItemPtr() {
        return &_data;
    }
    clsListNode<T> * getNext() {
        return _next;
    }
    void setNext(clsListNode<T> *__next) {
        _next = __next;
    }
};

template<class T>
class clsList
{
protected:
    clsListNode<T> *_head;
    clsListNode<T> *_tail;
    void deleteNode(clsListNode<T> *node) {
        if(node) {
            clsListNode<T> *next = node->getNext();
            if(next)
                deleteNode(next);
            delete node;
        }
    }
    bool removeNext(int &__k, clsListNode<T> *node) {
        if(node) {
            clsListNode<T> *next = node->getNext();
            if(next) {
                if(next->getItem().key() == __k) {
                    node->setNext(next->getNext());
                    delete next;
                    return true;
                }
                else
                    return removeNext(__k, next);
            }
            else
                return false;
        }
        else
            return false;
        return false;
    }

public:
    clsList() {
        _head = _tail = NULL;
    }
    ~clsList() {
        deleteNode(_head);
    }
    clsListNode<T> *head() {
        return _head;
    }
    clsListNode<T> *tail() {
        return _tail;
    }

    void add(T *__item) {
        clsListNode<T> *newItem = new clsListNode<T>(__item);
        if(_head) {
            if(_tail) {
                _tail->setNext(newItem);
                _tail = newItem;
            }
            else {
                _tail = newItem;
                _head->setNext(_tail);
            }
        }
        else
            _head = newItem;
    }
    bool remove(int &__k) {
        if(_head) {
            if(_head->getItem().key() == __k) {
                clsListNode<T> *next = _head->getNext();
                delete _head;
                _head = next;
                return true;
            }
            else
                return removeNext(__k, _head);
        }
        else
            return false;
    }
};

template<class T>
class clsStack : clsListNode<T>
{
private:
    clsListNode<T> *head;
public:
    clsStack() : clsListNode<T>() {
        head = new clsListNode<T>();
    }

    void push(T item) {
        head = new clsListNode<T>(item, head);
    }
    T pop() {
        if(!isEmpty()) {
            T item = head->getItem();
            head = head->getNext();
            return item;
        }
    }
    bool isEmpty() {
        return head->getNext() == NULL;
    }
};

template<class T>
class clsQueue : protected clsListNode<T>
{
private:
    clsListNode<T> *head;
    clsListNode<T> *tail;
public:
    clsQueue() : clsListNode<T>() {
        tail = head = NULL;
    }

    void enqueue(T item) {
        clsListNode<T> *node = new clsListNode<T>(item, NULL);
        if(isEmpty())
            tail = head = node;
        else {;
            tail->setNext(node);
            tail = node;
        }
    }
    T dequeue() {
        if(!isEmpty()) {
            T item = head->getItem();
            head = head->getNext();
            return item;
        }
    }
    bool isEmpty() {
        return head == NULL;
    }
};

#endif // LISTS_H
