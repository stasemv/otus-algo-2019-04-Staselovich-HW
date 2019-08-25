#ifndef TEST_TREES_H
#define TEST_TREES_H

#include "binary_tree.h"

#include <time.h>
#include <stdio.h>

void test_trees();

template<template<class> class T_item, class T>
double test_tree(clsBinaryTree<T_item, T> *tree,
                 const char *name,
                 int amount, double deleted_part,
                 bool isPrintToFile)
{
    FILE *fout = stdout;
    char name_str[1024];
    snprintf(name_str, 1023, "%s.txt", name);
    fout = fopen(name_str, "w");
    if(!fout) {
        printf("Cannot open file %s\n", name_str);
        return -1;
    }

    clock_t c_start, c_finish;
    c_start = clock();

    for(int i=0; i < amount; ++i) {
        int index = rand() % (amount*10);
        while(tree->find(index))
            index = rand() % (amount*10);
        tree->insert(index);
//        tree->printTree(fout, name, 1);
    }

    sprintf(name_str, "%s_all", name);
    if(isPrintToFile)
        tree->printTree(fout, name_str, 1);

    int deletes = amount * deleted_part;
    for(int i=0; i < deletes; ++i) {
        int index = rand() % (amount*10);
        while(!tree->find(index))
            index = rand() % (amount*10);
//        fprintf(fout, "%i : removing item = %i\n", i, index);
        tree->remove(index);
    }
    sprintf(name_str, "%s_del(part = %f)", name, deleted_part);
    if(isPrintToFile)
        tree->printTree(fout, name_str, 1);

    c_finish = clock();
    clock_t delta = c_finish-c_start;
    double time = delta*1.0/CLOCKS_PER_SEC;
    printf("%s handle time = %f\n", name, time);

    fclose(fout);

    return time;
}

template<template<class> class T_item, class T>
double test_average_tree_time(clsBinaryTree<T_item, T> *tree,
                              const char *name,
                              int items_amount, double del_part,
                              bool isPrintToFile,
                              int stat_amount)
{
    double time = 0.0;
    for(int i=0; i < stat_amount; ++i) {
        if(!tree->isEmpty()) {
            delete tree;
            tree = new clsBinaryTree<T_item, T>();
        }

        time += test_tree<T_item, T>(tree, name,
                                     items_amount, del_part, isPrintToFile);
    }
    time /= (double)stat_amount;
    return time;
}

#endif // TEST_TREES_H
