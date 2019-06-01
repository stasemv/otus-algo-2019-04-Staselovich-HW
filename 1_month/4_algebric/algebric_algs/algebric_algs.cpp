#include "algebric_algs.h"

#include <stdio.h>
#include <math.h>
#include <cstring>

unsigned long long calcEvclidNOD(unsigned long long a,
                                 unsigned long long b)
{
    while(a != 0 && b != 0)
        if(a > b)
            a = a % b;
        else
            b = b % a;
    return a > b ? a : b;
}


double calcFastPow(double a,
                          unsigned long pow)
{
    switch(pow) {
    case 0: return 1;
    case 1 : return a;
    default: {
        unsigned long tail = pow % 2;
        printf("raise a(%f) to pow(%lu)\n", a, pow);
        return calcFastPow(a*a, pow / 2)
                * calcFastPow(a, tail);
    }
    }
    return a;
}

double calcFastPow2(double a,
                    unsigned long pow)
{
    double res = 1;
    while(pow > 1) {
//        printf("raise a(%f) to pow(%lu)\n", a, pow);
        if(pow % 2 == 1)
            res *= a;
        a *= a;
        pow /= 2;
    }
    if(pow > 0)
        res *= a;

    return a;
}

bool isPrime(unsigned long num)
{
    unsigned int a = 1;
    if(num <= 2)
        return 1;
    while(++a < num) {
        if(num % a == 0)
            return 0;
    }
    return 1;
}

bool isPrimeSQRT(unsigned long num)
{
    unsigned int a = 1;
    if(num <= 2)
        return 1;
    while(++a < sqrt(num+1)) {
        if(num % a == 0)
            return 0;
    }
    return 1;
}
int calcPrimeNumbersAmount(unsigned int num)
{
    unsigned int a = 1;
    int count = 0;
    while(++a <= num) {
        if(isPrime(a))
            count++;
    }
    return count;
}
int calcPrimeNumbersAmountSQRT(unsigned int num)
{
    unsigned int a = 1;
    int count = 0;
    while(++a <= num) {
        if(isPrimeSQRT(a))
            count++;
    }
    return count;
}
int calcPrimeNumbersAmountSQRT_ODD(unsigned int num)
{
    unsigned int a = 2;
    int count = 1;
    while(++a <= num) {
        if(isPrimeSQRT(a))
            count++;
        a++;
    }
    return count;
}

bool getBit(unsigned int index, char *array)
{
    return (array[index/8] >> (index % 8)) & 1;
}

void setBit(int val, unsigned int index, char *array)
{
    if(val)
        array[index/8] |= 1 << (index % 8);
    else
        array[index/8] &= (1 << (index % 8)) ^ 0xFF;
}

int calcEratosfenSieve(unsigned int num)
{
    int arrSize = num/8 + 1;
    char *arr = new char[arrSize];
    memset(arr, 0, arrSize);

    unsigned int a = 1;
    int count = 0;
    while(++a <= num) {
        if(getBit(a, arr) == 0) {
            count++;
            unsigned int b = a*a;
            while(b <= num) {
                setBit(1, b, arr);
                b += a;
            }
        }
    }

    delete[] arr;
    return count;
}

double calcFibonachiDP(unsigned long num)
{
    double a = 1;
    double b = 1;

    double f = a;
    for(unsigned long i = 3; i < num; ++i) {
        f = a + b;
        b = a;
        a = f;
    }
    return f;
}

double calcFibonachiRec(unsigned long num)
{
    double phi = (1.0 + sqrt(5.0)) * 0.5;
    double f = floor(calcFastPow2(phi, num)/sqrt(5.0) + 0.5);
    return f;
}


