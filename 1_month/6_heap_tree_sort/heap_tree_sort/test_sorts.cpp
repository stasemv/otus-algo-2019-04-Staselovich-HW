#include "test_sorts.h"

#include <stdlib.h>

#include "tree_sorts.h"
#include "special_sorts.h"

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

//    printArray<double>(array, dim, fout, "origin");
//    mergeSort<double>(array, dim);
//    printArray<double>(array, dim, fout, "sorted");
//    quickSort<double>(array, 0, dim);
//    printArray<double>(array, dim, fout, "sorted");

    {
//    int intArr[] = { 1, 3, 6, 9, 10, 12, 4, 2, 0, 5, 7, 8, 19, 15, 13 };
//    int intArrDim = sizeof(intArr)/sizeof(intArr[0]);
//    printArray<int>(intArr, intArrDim, fout, "origin");
//    timSort<int>(intArr, intArrDim);
    }

    {
//    int intArr[] = { 1, 3, 6, 9, 10, 12, 4, 2, 0, 5, 7, 8, 19, 15, 13 };
//    int intArrDim = sizeof(intArr)/sizeof(intArr[0]);
//    printArray<int>(intArr, intArrDim, fout, "origin");
//    int power = arrayMax<int>(intArr, intArrDim);
//    countedSort(intArr, intArrDim, power+1);
//    printArray<int>(intArr, intArrDim, fout, "sorted");
    }
    {
        int intArr[] = { 35621, 43653, 74586, 75629, 57561,
                         78212, 45724, 57222, 58560, 13655,
                           457, 54638, 23419,   311,  2162 };
        int intArrDim = sizeof(intArr)/sizeof(intArr[0]);
        printArray<int>(intArr, intArrDim, fout, "origin");
        int power = arrayMax<int>(intArr, intArrDim);
        radixSort(intArr, intArrDim, 10);
        printArray<int>(intArr, intArrDim, fout, "sorted");
    }

    delete array;
}
