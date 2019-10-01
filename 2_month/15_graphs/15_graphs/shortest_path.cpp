#include "shortest_path.h"

#include "../../../1_month/9_trees/binary_trees/avl_tree.h"

clsVector<sctGraphArc> calcDeikstra(clsAdjacencyVector const * const G,
                                    int start, int end)
{
    clsVector<sctGraphArc> path;
    size_t N = G->nVertex();
    if((start >= N) || (end >= N) || (start == end))
        return path;

    char *handeledVertexes = new char[N];
    memset(handeledVertexes, 0, N);
    sctPathPoint *points = new sctPathPoint[N];
    memset(points, 0, N*sizeof(sctPathPoint));
    for(size_t i=0; i < N; ++i) {
        points[i].distance = 0x7fffffff;
        points[i].index = i;
    }
    points[start].distance = 0;
//    handeledVertexes[start] = 1;
    size_t counter = 0;
    while(counter++ < N) {
        sctPathPoint *_points = new sctPathPoint[N];
        memcpy(_points, points, N*sizeof(sctPathPoint));
        heapSort<sctPathPoint>(_points, N);
        sctPathPoint *point = &_points[0];
        size_t lim = 0;
        while((handeledVertexes[point->index])
              && (lim++ < N)) // TODO: add limit
            point = &point[1];
        point = &points[point->index];
        if(point->index == end)
            break;
        clsVector<sctGraphArc> arcs = G->getOuterArcs(point->index);
        for(size_t i=0; i < arcs.size(); ++i)
            if(!handeledVertexes[arcs[i].end])
                if(point->distance + arcs[i].weight < points[arcs[i].end].distance) {
                    points[arcs[i].end].distance = point->distance + arcs[i].weight;
                    points[arcs[i].end].from = point->index;
                }
        handeledVertexes[point->index] = 1;
    }

    counter = 0;
    sctPathPoint *point = &points[end];
    while((point->index != start) && (counter++ < N)) {
        sctGraphArc arc(point->from, point->index,
                        point->distance - points[point->from].distance);
        path.add_i(arc, 0);
        point = &points[point->from];
    }

    delete[] points;
    delete[] handeledVertexes;
    return path;
}
