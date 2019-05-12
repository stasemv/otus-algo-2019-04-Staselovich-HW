#include "use_arrays.h"

#include <stdio.h>
#include "time.h"
#include "dynamic_arrays.h"

template<class T>
void testAddArrays(const char *name, clsDynArr<T> *arr, int amount);

void useAllArrays()
{
//#define _type int
#define _type double
    int total = 100000;
    clsNoobDynArr<_type> _type_noob_dyn_arr;
    testAddArrays<_type>("noob", &_type_noob_dyn_arr, total);

    clsBlockArr<_type> _type_block_arr;
    testAddArrays<_type>("block", &_type_block_arr, total);
    testAddArrays<_type>("block_100", new clsBlockArr<_type>(100), total);

    clsFactorArr<_type> _type_factor_arr;
    testAddArrays<_type>("factor", &_type_factor_arr, total);

    clsMatrixArr<_type> _type_matr_arr(10);
    testAddArrays<_type>("matr", &_type_matr_arr, total);
}

template<class T>
void testAddArrays(const char *name, clsDynArr<T> *arr, int amount)
{
#define _PRINT_ARRAYS_ 0
#if _PRINT_ARRAYS_
    int printCount = 0;
#endif
    clock_t c_start, c_finish;
    c_start = clock();

    for(int i=0; i < amount; ++i) {
//        T *added = new T((_type)i);
//        arr->add(*added);
        arr->add(T((_type)(i+1)));
#if _PRINT_ARRAYS_
        _type val = arr->get(i);
        printf("%i\t", (int)val);
    if(++printCount >= 10) {
        printf("\n");
        printCount = 0;
    }
#endif
    }

    c_finish = clock();
    clock_t delta = c_finish-c_start;
    printf("%s add clocks = %li\n", name, delta);
    double operatingTimeFull = delta*1.0/CLOCKS_PER_SEC;
    printf("%s add time = %f\n", name, operatingTimeFull);
}

