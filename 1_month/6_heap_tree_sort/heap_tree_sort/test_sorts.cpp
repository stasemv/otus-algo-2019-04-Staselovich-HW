#include "test_sorts.h"

#include "tree_sorts.h"
#include <stdlib.h>

void test_sorts()
{
    int dim = 100;
    double *array = new double[dim];
    for(int i=0; i < dim; ++i)
        array[i] = rand()/(double)RAND_MAX;

    FILE *fout = stdout;
//    printHeap<double>(array, dim, fout);
//    buildHeap<double>(array, dim);
//    printHeap<double>(array, dim, fout);
//    heapSort<double>(array, dim);
//    printHeap<double>(array, dim, fout);

    printArray<double>(array, dim, fout, "origin:");
    mergeSort<double>(array, dim);
    printArray<double>(array, dim, fout, "sorted");
//    mergeSort<double>(array, dim);
//    printArray<double>(array, dim, fout, "sorted");

    delete array;
}
