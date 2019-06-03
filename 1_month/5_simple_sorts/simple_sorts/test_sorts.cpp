#include "test_sorts.h"

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
//#include <iostream>
//#include <fstream>

#include <sorts.h>

void getRaisingArray(double *array, const int dim)
{
    for(int i=0; i < dim; ++i)
        array[i] = (double)i / (double)dim;
}

void shuffleArray(double *array, const int dim,
                  const int shuffle_count)
{
    for(int i=0; i < shuffle_count; ++i) {
        int i1 = rand() % dim;
        int i2 = rand() % dim;
        double buf = array[i1];
        array[i1] = array[i2];
        array[i2] = buf;
    }
}

double sortArray(double *array, const int dim,
                  void sortFunc(double*, int))
{
    clock_t c_start, c_finish;
    c_start = clock();

    sortFunc(array, dim);

    c_finish = clock();
    clock_t delta = c_finish - c_start;
//    printf("clocks = %lu\n", delta);
    double time = (double)delta*1.0/(double)CLOCKS_PER_SEC;
//    printf("time = %.6f\n", time);
    return time;
}

void printArray(double *array, const int dim)
{
    int printCount = 0;
    for(int i=0; i < dim; ++i) {
        printf("%.6lf\t", array[i]);
        if(++printCount >= 10) {
            printf("\n");
            printCount = 0;
        }
    }
    printf("\n");
}

void testSort(FILE *fout, void sortFunc(double*, int), const char* name)
{
    int dStart = 200;
    int dFinish = 100000;
    int iterations = 100;

    fprintf(fout, "%s\n", name);
    int dim = dStart;
    fprintf(fout, "shaffled\t");
    while(dim < dFinish) {
        fprintf(fout, "%i\t", dim);
        dim *= 2;
    }
    fprintf(fout, "%i\n", dFinish);

    for(int i=0; i < 3; ++i) {
        switch(i) {
        case 0 :
            fprintf(fout, "all\t"); break;
        case 1 :
            fprintf(fout, "_10%%\t"); break;
        case 2 :
            fprintf(fout, "5_items\t"); break;
        default :
            break;
        }

        int dimention = dStart;
        int shaffled;
        bool isLast = false;
        bool isEnd = false;
        double time;
        while(!isEnd)
        {
            switch(i) {
            case 0 :
                shaffled = dimention; break;
            case 1 :
                shaffled = dimention * 0.1; break;
            case 2 :
                shaffled = 5; break;
            default :
                break;
            }
            double *array = new double[dimention];
            getRaisingArray(array, dimention);

            time = 0.0;
            for(int sub=0; sub < iterations; ++sub) {
                shuffleArray(array, dimention, shaffled);
                time += sortArray(array, dimention, sortFunc);
                printf("time = %f\n", time);
            }
            fprintf(fout, "%.6f\t", time/(double)iterations);

            delete[] array;

            if(isLast)
                isEnd = true;
            else {
                dimention *= 2;
                if(dimention >= dFinish) {
                    dimention = dFinish;
                    isLast = true;
                }
            }
//            isEnd = true;
        }
        fprintf(fout, "\n");
    }
    fprintf(fout, "\n");
}

void testAllSorts()
{
    FILE *fout = fopen("../sortsCompare.xls", "w");

    testSort(fout, insertionSort, "insertion sort");
    testSort(fout, ShellSort, "origin shell sort");
    testSort(fout, FrankAndLazarusSort, "shell sort with Frank/Lazarus's gap sequence");
    testSort(fout, HibbardSort, "shell sort with Hibbard's gap sequence");

    fclose(fout);
}
