#ifndef SPECIAL_SORTS_H
#define SPECIAL_SORTS_H

void countedSort(int *arr, int dim, int power);
void radixSort(int *arr, int dim, int base);

template<class T>
T arrayMax(T *arr, int dim)
{
    T max = arr[0];
    for(int i=1; i < dim; ++i)
        if(arr[i] > max)
            max = arr[i];
    return max;
}

#endif // SPECIAL_SORTS_H
