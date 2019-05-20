#include "use_lists.h"

#include <stdio.h>

#include "lists.h"

#define _type int

template<class T> void testStack();
template<class T> void testQueue();

void use_lists()
{
    testStack<_type>();
    testQueue<_type>();

}

template<class T>
void testStack()
{
    clsStack<T> stack;

    stack.push(4);
    stack.push(5);
    stack.push(1);
    stack.push(2);

    printf("stack:\n");
    while(!stack.isEmpty())
        printf("%i\n", stack.pop());
    printf("\n");
}

template<class T>
void testQueue()
{
    clsQueue<T> queue;

    queue.enqueue(4);
    queue.enqueue(5);
    queue.enqueue(1);
    queue.enqueue(2);

    printf("queue:\n");
    while(!queue.isEmpty())
        printf("%i\n", queue.dequeue());
    printf("\n");
}

