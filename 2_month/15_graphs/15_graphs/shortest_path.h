#ifndef SHORTEST_PATH_H
#define SHORTEST_PATH_H

#include "graphs_data.h"

clsVector<sctGraphArc> calcDeikstra(clsAdjacencyVector const * const G,
                                    int start, int end);


#endif // SHORTEST_PATH_H
