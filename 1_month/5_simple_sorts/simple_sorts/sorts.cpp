#include "sorts.h"

#include <math.h>

void insertionSort(double *array, const int dim)
{
    for(int i=1; i < dim; ++i) {
        double buf = array[i];
        int j = i-1;
        while((j >= 0) && (buf < array[j]))
            array[j+1] = array[j--];
        array[j+1] = buf;
    }
}

int ShellStep(int k, int N)
{
    return N / pow(2, k);
}

int FrankAndLazarusStep(int k, int N)
{
    return 2 * (int)(N / pow(2, k+1)) + 1;
}

int HibbardStep(int k, int N)
{
    return pow(2, k) - 1;
}

void shellSort(double *array, const int dim,
               int fstep(int, int))
{
    int step = 1;
    int k = 0;
    int dk = 1;
    if(fstep(1, dim) == 1) {
        while(step < dim / 3)
            step = fstep(++k, dim);
        dk = -1;
    }

    do {
        k += dk;
        step = fstep(k, dim);
        for(int n=0; n < step; ++n) {
            int i = n + step;
            while(i < dim) {
//            for(int i=1; i < dim; ++i) {
                double buf = array[i];
                int j = i - step;
                while((j >= 0) && (buf < array[j])) {
                    array[j+step] = array[j];
                    j -= step;
                }
                array[j+step] = buf;
                i += step;
            }
        }
    } while(step > 1);
}

void ShellSort(double *array, const int dim)
{
    shellSort(array, dim, ShellStep);
}

void FrankAndLazarusSort(double *array, const int dim)
{
    shellSort(array, dim, FrankAndLazarusStep);
}

void HibbardSort(double *array, const int dim)
{
    shellSort(array, dim, HibbardStep);
}







