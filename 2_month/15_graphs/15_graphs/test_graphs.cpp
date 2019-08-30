#include "test_graphs.h"

#include <stdlib.h>
#include <cstring>
#include <vector>
#include <stack>
#include <stdio.h>

#include "graphs.h"

void simple_test_Kosaraju()
{
    printf("\nSimple Kosaraju test:\n");
    int v_amount = 8;
    clsAdjacencyVector *G = new clsAdjacencyVector(v_amount);
    G->addArc(0, 1);
    G->addArc(1, 2); G->addArc(1, 4); G->addArc(1, 5);
    G->addArc(2, 3); G->addArc(2, 6);
    G->addArc(3, 2); G->addArc(3, 7);
    G->addArc(4, 0); G->addArc(4, 5);
    G->addArc(5, 6);
    G->addArc(6, 5);
    G->addArc(7, 3); G->addArc(7, 6);

    int *components = new int[v_amount];
    calcKorasaju(G, components);

    printf("Components:\n");
    for(int i=0; i < v_amount; ++i)
        printf("V[%i] = %i\n", i, components[i]);

    delete[] components;
    delete G;
}

void test_Kosaraju(int v_amount, int e_amount)
{
    printf("\nKosaraju test:\n");
    printf("vertex amount = %d\n", v_amount);

    clsAdjacencyVector *G = new clsAdjacencyVector(v_amount);
    for(int i=0, lim = 0; i < e_amount; ++i, lim = 0) {
        while(!G->addArc(rand() % v_amount, rand() % v_amount)
               && (lim++ < v_amount*2)) {}
    }
    printf("G arcs amount = %d\n", G->getArcsAmount());

    int *components = new int[v_amount];
    int components_amount = calcKorasaju(G, components);

    printf("Components amount = %d:\n", components_amount);
    printf("Components:\n");
    for(int i=0; i < v_amount; ++i)
        printf("V[%i] = %i\n", i, components[i]);

    delete[] components;
    delete G;
}

void simple_test_topologic_sort(
        clsList<clsVector<int> > sort_func(clsAdjacencyMatrix const * const))
{
    int v_amount = 10;
    clsAdjacencyVector *G = new clsAdjacencyVector(v_amount);
    G->addArc(0, 1);
    G->addArc(1, 3); G->addArc(1, 4);
    G->addArc(2, 1);
    G->addArc(3, 5); G->addArc(3, 6);
    G->addArc(4, 6);
    G->addArc(5, 6); G->addArc(5, 9);
    G->addArc(6, 7); G->addArc(6, 8);

// 0----> 1-----> 3 -----> 5 -----> 9
//       /\\       \       |
//       |  \|      \|     \/
//       2   -4 --->------> 6 -----> 8
//                          |
//                          \/
//                           7

// expected result:
// lvl0: 0, 2
// lvl1: 1
// lvl2: 3, 4
// lvl3: 5
// lvl4: 6, 9
// lvl5: 7, 8

    clsAdjacencyMatrix *mG = new clsAdjacencyMatrix(G);
    clsList<clsVector<int> > levels = sort_func(mG);
    for(size_t i=0; i < levels.size(); ++i) {
        printf("level[%lu]: ", i);
        for(int j=0; j < levels[i].size(); ++j)
            printf("v_%d, ", levels[i][j]);
        printf("\n");
    }
//    delete[] levels;
}

void simple_test_min_ostov_tree(
        clsVector<sctGraphArc> ostov_func(clsAdjacencyVector const * const))
{
    int v_amount = 7;
    clsAdjacencyVector *G = new clsAdjacencyVector(v_amount);
    G->addEdge(0, 1, 7); G->addEdge(0, 3, 5);
    G->addEdge(1, 2, 8); G->addEdge(1, 3, 9); G->addEdge(1, 4, 7);
    G->addEdge(2, 4, 5);
    G->addEdge(3, 4, 15); G->addEdge(3, 5, 6);
    G->addEdge(4, 5, 8); G->addEdge(4, 6, 9);
    G->addEdge(5, 6, 11);

// expected result:
// 0-3
// 0-1
// 1-4
// 4-2
// 3-5
// 4-6
// weight sum = 5 + 7 + 7 + 5 + 6 + 9 = 39

    clsVector<sctGraphArc> ostTree = ostov_func(G);
    printf("ostov tree edges:\n");
    int sum = 0;
    for(size_t i=0; i < ostTree.size(); ++i) {
        printf("{%d - %d}\n", ostTree[i].start, ostTree[i].end);
        sum += ostTree[i].weight;
    }
    printf("ostov tree sum = %d\n", sum);
}

void test_graphs()
{
//    simple_test_Kosaraju();
//    test_Kosaraju(1000, 1000);

//    simple_test_topologic_sort(calcDemucron);
//    simple_test_topologic_sort(calcTarjan);

    simple_test_min_ostov_tree(calcPrim);
    simple_test_min_ostov_tree(calcKraskal);
}
