#ifndef ALGEBRIC_ALGS_H
#define ALGEBRIC_ALGS_H


unsigned long long calcEvclidNOD(unsigned long long a,
                                 unsigned long long b);

double calcFastPow(double a,
                   unsigned long b);
double calcFastPow2(double a,
                    unsigned long pow);
bool isPrime(unsigned long num);
int calcPrimeNumbersAmount(unsigned int num);
int calcPrimeNumbersAmountSQRT(unsigned int num);
int calcPrimeNumbersAmountSQRT_ODD(unsigned int num);
int calcEratosfenSieve(unsigned int num);
double calcFibonachiDP(unsigned long num);
double calcFibonachiRec(unsigned long num);

#endif // ALGEBRIC_ALGS_H
