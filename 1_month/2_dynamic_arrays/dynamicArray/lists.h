#ifndef LISTS_H
#define LISTS_H

#include "stddef.h"

template<class T>
class clsListNode
{
protected:
    T data;
    clsListNode<T> *next;
public:
    clsListNode() {
        next = NULL;
    }
    clsListNode(T &item) {
        data = item;
        next = NULL;
    }
    clsListNode(T &item, clsListNode<T> *_next) {
        data = item;
        next = _next;
    }
    T getItem() {
        return data;
    }
    T *getItemPtr() {
        return &data;
    }
    clsListNode<T> * getNext() {
        return next;
    }
    void setNext(clsListNode<T> *_next) {
        next = _next;
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
class clsQueue : clsListNode<T>
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
