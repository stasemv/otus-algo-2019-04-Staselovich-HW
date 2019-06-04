#include "test_sorts.h"

#include "tree_sorts.h"
#include <stdlib.h>

void test_sorts()
{
    int dim = 10;
    double *array = new double[dim];
    for(int i=0; i < dim; ++i)
        array[i] = rand()/(double)RAND_MAX;

    FILE *fout = stdout;
    printHeap<double>(array, dim, fout);
    buildHeap<double>(array, dim);
    printHeap<double>(array, dim, fout);
    heapSort<double>(array, dim);
    printHeap<double>(array, dim, fout);

    delete array;
}
