#include "test_graphs.h"

#include <cstring>
#include <vector>
#include <stack>
#include <stdio.h>

//#include "../../../1_month/2_dynamic_arrays/dynamicArray/lists.h"
#include "../../../1_month/2_dynamic_arrays/dynamicArray/dynamic_arrays.h"

void test_Kosaraju()
{
    int v_amount = 8;
    clsVector<clsVector<int> > G;
    G.push_back(clsVector<int>());
    for(int i=0; i < v_amount; ++i)
        G[0].push_back(0);
    for(int i=1; i < v_amount; ++i)
        G.push_back(G[0]);
    G[0][1] = // a
    G[1][2] = G[1][4] = G[1][5] = // b
    G[2][3] = G[2][6] = // c
    G[3][2] = G[3][7] = // d
    G[4][0] = G[4][5] = // e
    G[5][6] = // f
    G[6][5] = // g
    G[7][3] = G[7][6] = 1; // h

    clsVector<clsVector<int> > H = G;
    for(int i=0; i < v_amount; ++i)
        for(int j=0; j < v_amount; ++j)
            H[i][j] = G[j][i];

    clsStack<int> path_H;
    // depth-first search (DFS)
    int *checked = new int[v_amount];
    memset(checked, 0, v_amount*sizeof(int));
    int v_H = 0;
    clsStack<int> path_DFS;
    checked[v_H] = 1;
    path_H.push(v_H);
    while(path_H.size() < v_amount) {
        int next = -1;
        for(int i=0; i < v_amount; ++i)
            if(H[v_H][i])
                if(!checked[i]) {
                    next = i;
                    break;
                }
        if(next > -1) {
            path_DFS.push(v_H);
            v_H = next;
            checked[v_H] = 1;
            path_H.push(v_H);
        }
        else if(!path_DFS.empty()) {
            v_H = path_DFS.top();
            path_DFS.pop();
        }
        else {
            for(int i=0; i < v_amount; ++i)
                if(!checked[i]) {
                    v_H = i;
                    path_DFS.push(v_H);
                    checked[v_H] = 1;
                    path_H.push(v_H);
                    break;
                }
        }
    }

    // 3
    int *components = new int[v_amount];
    memset(components, 0, v_amount*sizeof(int));
    memset(checked, 0, v_amount*sizeof(int));
    int v_G = path_H.top();
    path_H.pop();
    path_DFS = clsStack<int>();
    checked[v_G] = 1;
    int component_num = 1;
    components[v_G] = component_num;
    while(!path_H.empty()) {
        int next = -1;
        for(int i=0; i < v_amount; ++i)
            if(G[v_G][i])
                if(!checked[i]) {
                    next = i;
                    break;
                }
        if(next > -1) {
            v_G = path_H.top();
            path_H.pop();
            path_DFS.push(v_G);
            checked[v_G] = 1;
            components[v_G] = component_num;
        }
        else if(!path_DFS.empty()) {
            v_G = path_DFS.top();
            path_DFS.pop();
        }
        else {
            component_num++;

            v_G = path_H.top();
            path_H.pop();

            path_DFS.push(v_G);
            checked[v_G] = 1;
            components[v_G] = component_num;
        }
    }

    printf("Components:\n");
    for(int i=0; i < v_amount; ++i)
        printf("V[%i] = %i\n", i, components[i]);


    delete[] checked;
    delete[] components;
}

void DZ_graphs()
{
    int v_amount = 1000;
    int e_amount = 1000;

}

void test_graphs()
{
    test_Kosaraju();

}


