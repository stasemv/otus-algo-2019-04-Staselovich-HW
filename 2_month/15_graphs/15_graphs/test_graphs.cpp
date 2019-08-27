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

void test_graphs()
{
    simple_test_Kosaraju();
    test_Kosaraju(1000, 1000);
}
