#ifndef TREE_SORTS_H
#define TREE_SORTS_H

#include <stdio.h>
#include <math.h>
#include <cstring>

#include "trees.h"

int heapLeft(int index);
int heapRight(int index);
int heapParent(int index);

template<class T>
void printArray(T *arr, int dim, FILE *fout, const char *title) {
    fprintf(fout, "%s\n", title);
    for(int i=0; i < dim; ++i)
        fprintf(fout, "%.6lf\t", (double)(arr[i]));
    fprintf(fout, "\n");
}

template<class T>
void printHeap(T *arr, int dim, FILE *fout, const char *title) {
    printArray<T>(arr, dim, fout, title);
    int depth = log(dim)/log(2) + 1;
    int length = 4;
    char *emptyValue = new char[length+3];
    for(int i=0; i < length+2; ++i)
        emptyValue[i] = ' ';
    emptyValue[length+2] = '\0';
    int idx = 0;

    for(int i=0; i < depth; ++i) {
        int count = pow(2, i);
        for(int j=0; j < count; ++j) {
            for(int s=pow(2, depth-1-i)-1; s > 0; --s)
                fprintf(fout, "%s", emptyValue);
            int index = idx + j;
            if(index < dim)
                fprintf(fout, "%.*lf", length, (double)(arr[idx + j]));
            else
                fprintf(fout, "%s", emptyValue);
            for(int s=pow(2, depth-1-i)-1; s >= 0; --s)
                fprintf(fout, "%s", emptyValue);
        }
        idx += pow(2, i);
        fprintf(fout, "\n");
    }
    delete[] emptyValue;
}

template<class T>
void swapHeapItems(T *arr, int ai, int bi)
{
    T buf = arr[ai];
    arr[ai] = arr[bi];
    arr[bi] = buf;
}

template<class T>
void heapDrown(T *arr, int idx, int dim)
{
    int left = heapLeft(idx);
    int right = heapRight(idx);
    int largest = idx;
    if((left < dim) &&(arr[left] > arr[largest]))
        largest = left;
    if((right < dim) && (arr[right] > arr[largest]))
        largest = right;
    if(largest != idx) {
        swapHeapItems<T>(arr, idx, largest);
        heapDrown<T>(arr, largest, dim);
    }
}

template<class T>
void buildHeap(T *arr, int dim)
{
    for(int i=heapParent(dim-1); i >= 0; --i)
        heapDrown(arr, i, dim);
}

template<class T>
void heapSort(T *arr, int dim)
{
    buildHeap<T>(arr, dim);
    for(int i=dim-1; i > 0; --i) {
        swapHeapItems(arr, 0, i);
        heapDrown(arr, 0, i);
    }
}

template<class T>
class clsHeapItem : clsBinTreeItem<T>
{
protected:
    int index;
public:
    clsHeapItem() : clsBinTreeItem<T>() {
        index = 0;
    }
    clsHeapItem(T data, int idx) : clsBinTreeItem<T>(data) {
        index = idx;
    }
};

template<class T>
void mergeArrays(T *arr,
                 int start, int middle, int end)
{
    int i = start;
    int j = middle;
    int size = end - start;
    T *newarr = new T[size];
    for(int k = 0; k < size; ++k) {
        if(i != middle) {
            if(j != end) {
                if(arr[i] < arr[j])
                    newarr[k] = arr[i++];
                else
                    newarr[k] = arr[j++];
            }
            else
                newarr[k] = arr[i++];
        }
        else
            newarr[k] = arr[j++];
    }
    memcpy(&arr[start], &newarr[0], size*sizeof(T));
    delete[] newarr;
}

template<class T>
void partialMergeSort(T *arr, int dim,
                      int start, int end)
{
    if((end - start) < 2)
        return;
    int middle = (start + end) / 2;
    partialMergeSort(arr, dim, start, middle);
    partialMergeSort(arr, dim, middle, end);
    mergeArrays<T>(arr, start, middle, end);
}

template<class T>
void mergeSort(T *arr, int dim)
{
    partialMergeSort(arr, dim, 0, dim);
}









#endif // TREE_SORTS_H
