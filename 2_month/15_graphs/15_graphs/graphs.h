#ifndef GRAPHS_H
#define GRAPHS_H

//#include "../../../1_month/2_dynamic_arrays/dynamicArray/dynamic_arrays.h"

#include <vector>

struct sctAdjArc {
    int end;
    int weight;

    sctAdjArc() : end(0), weight(0) {}
    sctAdjArc(int e, int w) : end(e), weight(w) {}
};

struct sctGraphArc {
    int start;
    int end;
    int weight;

    sctGraphArc() : start(0), end(0), weight(0) {}
    sctGraphArc(int s, int e, int w = 1) : start(s), end(e), weight(w) {}
};

class clsAdjacencyVector
{
protected:
    std::vector<std::vector<sctAdjArc> > _array;
    int _nVertex;
    int _nArcs;
    int _nMaxEdges;
    bool isIndexValid(int index) {
        return (index >= 0) && (index < _nVertex);
    }

public:
    clsAdjacencyVector() :
    _nVertex(0), _nArcs(0), _nMaxEdges(0) { }
    clsAdjacencyVector(int n_vertex) :
    _nVertex(n_vertex), _nArcs(0)  {
        std::vector<sctAdjArc> arr;
        for(int i=0; i < _nVertex; ++i)
            _array.push_back(arr);
    }
    int getNVertex() const { return _nVertex; }

    bool addArc(sctGraphArc arc);
    bool addArc(int start, int end, int w = 1.0);
    bool addEdge(sctGraphArc arc);
    bool addEdge(int start, int end, int w = 1.0);
    int getArcWeight(int start, int end) const;
    int getArcsAmount();

    std::vector<sctGraphArc> getArcVector() const;

};

struct clsAdjacencyMatrix {

};

int calcKorasaju(clsAdjacencyVector const * const adjVector,
                  int *components);


#endif // GRAPHS_H
