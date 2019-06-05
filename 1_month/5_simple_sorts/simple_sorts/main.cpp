#include <iostream>

#include <stdlib.h>

#include "test_sorts.h"

int main()
{
    testAllSorts();
    if(0) {
        int max = 0;
        for(int i=0; i < 1000000; ++i) {
            int val = rand();
            if(val > max)
                max = val;
        }
    }
    std::cout << "Done!" << std::endl;
    return 0;
}

