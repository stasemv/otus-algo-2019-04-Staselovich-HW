#ifndef GRAPHS_H
#define GRAPHS_H

#include "graphs_data.h"
//#include "../../../1_month/5_simple_sorts/simple_sorts/sorts.h"
#include <stddef.h>

// functions:
int calcKorasaju(clsAdjacencyVector const * const adjVector,
                  int *components);

clsList<clsVector<int> > calcDemucron(clsAdjacencyMatrix const * const _matrix);
//clsList<clsVector<int> > calcTarjan(clsAdjacencyMatrix const * const _matrix);

clsVector<sctGraphArc> calcPrim(clsAdjacencyVector const * const G);
clsVector<sctGraphArc> calcBoruvka(clsAdjacencyVector const * const G);
clsVector<sctGraphArc> calcKruskal(clsAdjacencyVector const * const G);

#endif // GRAPHS_H
