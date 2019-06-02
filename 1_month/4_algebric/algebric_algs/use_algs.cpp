#include "use_algs.h"

#include <stdio.h>
#include <time.h>
#include <iostream>
#include <fstream>

#include "algebric_algs.h"

void use_algs()
{
    clock_t c_start, c_finish;
    c_start = clock();

    // Алгоритм Евклида
    if(0)
    {
        unsigned long long a = 123456789000;
        unsigned long long b = 12;
        unsigned long long nod = calcEvclidNOD(a, b);
        printf("a = %lu\n", a);
        printf("b = %lu\n", b);
        printf("NOD = %lu\n", nod);
    }

    // быстрое возведение в степень
    if(0)
    {
        double a = 2;
        unsigned long pow = 10;
        a = 1.00000001;
        pow = 1000000000;
        double res = calcFastPow2(a, pow);
        printf("a = %lf\n", a);
        printf("pow = %lu\n", pow);
        printf("a^pow = %lf\n", res);
    }

    // нахождение простых чисел
    if(0)
    {
        unsigned long a = 1;
//        a = 29; printf("a = %lu, a is%s prime\n", a, isPrime(a) ? "" : " not");

        a = 100000;
//        printf("poor: a = %lu has %u prime numbers\n", a, calcPrimeNumbersAmount(a));
//        printf("sqrt: a = %lu has %u prime numbers\n", a, calcPrimeNumbersAmountSQRT(a));
//        printf("sqrt + add: a = %lu has %u prime numbers\n", a, calcPrimeNumbersAmountSQRT_ODD(a));
        printf("eratosfen: a = %lu has %u prime numbers\n", a, calcEratosfenSieve(a));
    }

    // числа Фибоначчи
    {
        unsigned long a = 120;
        printf("DP: a = %lu, Fibonachi number is %lf\n", a, calcFibonachiDP(a));
        printf("Rec: a = %lu, Fibonachi number is %lf\n", a, calcFibonachiRec(a));

    }

    c_finish = clock();
    clock_t delta = c_finish-c_start;
    printf("clocks = %lu\n", delta);
    double time = delta*1.0/CLOCKS_PER_SEC;
    printf("time = %f\n", time);
//    return time;
}


















