#include "special_sorts.h"

#include <cstring>
#include <math.h>

#include "tree_sorts.h"

int getDigit(int number, int k, int base)   // k = 0, 1, ...
{
    for(int i=0; i < k; ++i)
        number /= base;
    return number % base;
}

#define __countedSort(arrItem, dim, power) \
{ \
    int *sorted = new int[dim];     \
    int *counters = new int[power]; \
    memset(counters, 0, sizeof(int)*power); \
    for(int i=0; i < dim; ++i)  \
        counters[arrItem]++;     \
    for(int i=1; i < power; ++i)    \
        counters[i] += counters[i-1];   \
    for(int i=dim-1; i >=0; --i)    \
        sorted[--(counters[arrItem])] = arr[i];  \
    memcpy(arr, sorted, dim*sizeof(arr[0]));    \
    delete[] sorted;    \
    delete[] counters;  \
}

void countedSort(int *arr, int dim, int power)
{
    __countedSort(arr[i], dim, power);
}

void radixSort(int *arr, int dim, int base)
{
    int maxDigits = 0;
    for(int i=0; i < dim; ++i) {
        int digits = log(arr[i])/log(base) + 1;
        if(digits > maxDigits)
            maxDigits = digits;
    }
    for(int d=0; d < maxDigits; ++d) {
        __countedSort(getDigit(arr[i], d, base), dim, base);
        char str[64];
        memset(str, 0, 64);
        sprintf(str, "%i digit", d);
        printArray<int>(arr, dim, stdout, str);
    }
}
