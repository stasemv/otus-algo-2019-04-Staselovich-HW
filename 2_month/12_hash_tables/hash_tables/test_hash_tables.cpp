#include "test_hash_tables.h"

#include <stdlib.h>

#include "hash_tables.h"

void test_hash_tables()
{
    int dim = 15;
    clsHashTable<double> table(dim);
    int amount = 15;
    int *keys = new int[amount];
    for(int i=0; i<amount; ++i) {
        int key = rand();
        table.addItem(key, (double)i);
        keys[i] = key;
    }

    table.print(stdout, "table");

    for(int i=amount-1; i>=0; --i) {
        fprintf(stdout, "key = %d; val = %f\n",
                keys[i], *(table.item(keys[i])));
    }
    fprintf(stdout, "\n");

    for(int i=0; i<amount/2; ++i) {
        int index = rand() % dim;
        int key = keys[index];
        bool del = table.remove(clsHashTableItem<double>(key, 0));
        fprintf(stdout, "key = %d\n", key);
        if(!del)
            fprintf(stdout, "Removing unsuccess. No such key: %d\n",
                    key);
    }
    table.print(stdout, "clean table");

    delete[] keys;
}
