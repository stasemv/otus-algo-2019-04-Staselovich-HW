#include "test_cache.h"

#include <time.h>
#include <stdio.h>

#include "cache.h"

int fibn(int n)
{
    if(n < 2)
        return 1;
    return fibn(n-1) + fibn(n-2);
}

int callFiboWithCache(int x, clsCache<int> * cache)
{
    if(cache) {
        int *res = cache->get(x);
        if(res)
            return *res;
    }
    int r = 1;
    if(x > 1)
        r =  callFiboWithCache(x-1, cache) + callFiboWithCache(x-2, cache);
    if(cache)
        cache->set(x, r);
    return r;
}

void testFiboWithCache(int num, int calc_func(int), clsCache<int> * cache)
{
    clock_t c_start, c_finish;
    c_start = clock();

    for(int i=0; i < num; ++i) {
        int fibo = callFiboWithCache(i, cache);
        printf("%d\t", fibo);
    }

    c_finish = clock();
    clock_t delta = c_finish - c_start;
    double time = delta*1.0/CLOCKS_PER_SEC;
    printf("\ncalc time = %f\n", time);
}

void test_cache()
{
    int num = 45;
    testFiboWithCache(num, fibn, NULL); // without cache

    clsCache<int> cache(128, 5);
    for(int i=10; i > 0; --i) {
        cache.set_ttl(i);
        testFiboWithCache(num, fibn, &cache); // with cache
        cache.printState(stdout);
        printf("\n\n");
        cache.clear();
    }
}
