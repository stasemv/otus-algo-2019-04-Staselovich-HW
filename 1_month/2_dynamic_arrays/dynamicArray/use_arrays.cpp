#include "use_arrays.h"

#include <stdio.h>
#include "time.h"
#include "dynamic_arrays.h"

#define _PRINT_ARRAYS_ 0

template<class T>
void printArray(clsDynArr<T> *arr);
template<class T>
void testAddArrays(const char *name, clsDynArr<T> *arr, int amount);
template<class T>
void testAddIArrays(const char *name, clsDynArr<T> *arr, int amount);
template<class T>
void testRemoveIArrays(const char *name, clsDynArr<T> *arr, int amount);

void useAllArrays()
{
//#define _type int
#define _type double
    int total = 1000;
//    clsNoobDynArr<_type> _type_noob_dyn_arr;
//    testAddArrays<_type>("noob", &_type_noob_dyn_arr, total);
//    testAddIArrays<_type>("noob", &_type_noob_dyn_arr, total/100);
//    testRemoveIArrays<_type>("noob", &_type_noob_dyn_arr, total/100);

//    clsBlockArr<_type> _type_block_arr;
//    testAddArrays<_type>("block", &_type_block_arr, total);
//    testAddIArrays<_type>("block", &_type_block_arr, total/100);
//    testRemoveIArrays<_type>("block", &_type_block_arr, total/100);
//    testAddArrays<_type>("block_100", new clsBlockArr<_type>(100), total);

//    clsFactorArr<_type> _type_factor_arr;
//    testAddArrays<_type>("factor", &_type_factor_arr, total);
//    testAddIArrays<_type>("factor", &_type_factor_arr, total*0.5);
//    testRemoveIArrays<_type>("factor", &_type_factor_arr, total*0.33 + 1);

    clsMatrixArr<_type> _type_matr_arr(10);
    testAddArrays<_type>("matr", &_type_matr_arr, total);
    testAddIArrays<_type>("matr", &_type_matr_arr, total/100);
    testRemoveIArrays<_type>("matr", &_type_matr_arr, total/100);
}

template<class T>
void testAddArrays(const char *name, clsDynArr<T> *arr, int amount)
{
    clock_t c_start, c_finish;
    c_start = clock();

    for(int i=0; i < amount; ++i)
        arr->add(T((_type)(i)));

    printArray(arr);

    c_finish = clock();
    clock_t delta = c_finish-c_start;
    printf("%s add clocks = %li\n", name, delta);
    double operatingTimeFull = delta*1.0/CLOCKS_PER_SEC;
    printf("%s add time = %f\n", name, operatingTimeFull);
}

template<class T>
void testAddIArrays(const char *name, clsDynArr<T> *arr, int amount)
{
    clock_t c_start, c_finish;
    c_start = clock();

    for(int i=0; i < amount; ++i) {
        int amount = arr->size();
        int idx = rand() % amount;
        arr->add_i(T((_type)(amount+1)), idx);
    }

    printArray(arr);

    c_finish = clock();
    clock_t delta = c_finish-c_start;
    printf("%s add_i clocks = %li\n", name, delta);
    double operatingTimeFull = delta*1.0/CLOCKS_PER_SEC;
    printf("%s add_i time = %f\n", name, operatingTimeFull);
}

template<class T>
void testRemoveIArrays(const char *name, clsDynArr<T> *arr, int amount)
{
    clock_t c_start, c_finish;
    c_start = clock();

    for(int i=0; i < amount; ++i) {
        int amount = arr->size();
        int idx = rand() % amount;
        T item = arr->remove(idx);
    }

    printArray(arr);

    c_finish = clock();
    clock_t delta = c_finish-c_start;
    printf("%s remove clocks = %li\n", name, delta);
    double operatingTimeFull = delta*1.0/CLOCKS_PER_SEC;
    printf("%s remove time = %f\n", name, operatingTimeFull);
}

template<class T>
void printArray(clsDynArr<T> *arr)
{
#if _PRINT_ARRAYS_
    int printCount = 0;
    int _num = arr->size();
    for(int i=0; i < _num; ++i) {
        _type val = arr->get(i);
        printf("%i\t", (int)val);
        if(++printCount >= 10) {
            printf("\n");
            printCount = 0;
        }
    }
    printf("\n");
#endif
}
