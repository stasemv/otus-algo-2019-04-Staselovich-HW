#ifndef GRAPHS_H
#define GRAPHS_H

//#define _USE_STD_VECTOR_

#include "../../../1_month/2_dynamic_arrays/dynamicArray/dynamic_arrays.h"
#include <stddef.h>

#ifdef _USE_STD_VECTOR_
#include <vector>
#endif

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
    bool operator < (const sctGraphArc & a) const {
        return weight < a.weight;
    }
};

class clsAdjacencyVector
{
protected:
#ifdef _USE_STD_VECTOR_
    std::vector<std::vector<sctAdjArc> > _array;
#else
    clsVector<sctAdjArc> *_array;
#endif
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
#ifdef _USE_STD_VECTOR_
        std::vector<sctAdjArc> arr;
        for(int i=0; i < _nVertex; ++i)
            _array.push_back(arr);
#else
        _array = new clsVector<sctAdjArc>[_nVertex]();
//        clsList<sctAdjArc> arr;
//        for(int i=0; i < _nVertex; ++i)
//            _array.push_back(arr);
#endif
    }
    ~clsAdjacencyVector() {
#ifdef _USE_STD_VECTOR_
#else
        delete[] _array;
#endif
    }
    int nVertex() const { return _nVertex; }

    bool addArc(sctGraphArc arc);
    bool addArc(int start, int end, int w = 1.0);
    bool addEdge(sctGraphArc arc);
    bool addEdge(int start, int end, int w = 1.0);
    int getArcWeight(int start, int end) const;
    int getArcsAmount();

#ifdef _USE_STD_VECTOR_
    std::vector<sctGraphArc> getArcsVector() const;
    std::vector<sctGraphArc> getArcsVector(int v) const;
    std::vector<sctGraphArc> getOuterArcs(std::vector<int> *v) const;
#else
    clsVector<sctGraphArc> getArcsVector() const;
    clsVector<sctGraphArc> getArcsVector(int v) const;
    clsVector<sctGraphArc> getOuterArcs(clsVector<int> *_v) const;
#endif

};

class clsAdjacencyMatrix {
protected:
    int **_matrix;
    int _nVertex;
public:
    clsAdjacencyMatrix() : _matrix(NULL), _nVertex(0) {}
    clsAdjacencyMatrix(int n) : _nVertex(n) {
        _matrix = new int*[_nVertex];
        for(int i=0; i < _nVertex; ++i)
            _matrix[i] = new int[_nVertex];
    }
    clsAdjacencyMatrix(clsAdjacencyVector const * const v) {
        _nVertex = v->nVertex();
        _matrix = new int*[_nVertex];
        for(int i=0; i < _nVertex; ++i)
            _matrix[i] = new int[_nVertex];
#ifdef _USE_STD_VECTOR_
        std::vector<sctGraphArc> arcs = v->getArcsVector();
#else
        clsVector<sctGraphArc> arcs = v->getArcsVector();
#endif
        for(int i=arcs.size()-1; i >= 0; --i){
            sctGraphArc *arc = &arcs[i];
            at(arc->start)[arc->end] = arc->weight;
        }
    }

    ~clsAdjacencyMatrix() {
        if(_matrix)
            delete[] _matrix;
        _matrix = NULL;
    }
    int * at(int row) const {
        return _matrix[row];
    }

    int * operator[] (int index) const {
        return at(index);
    }
    int nVertex() const {
        return _nVertex;
    }
    int colSum(int col) const {
        if(col >= _nVertex)
            return 0;
        int sum = 0;
        for(int i=0; i < _nVertex; ++i)
            sum += _matrix[i][col];
        return sum;
    }
    int rowSum(int row) const {
        if(row >= _nVertex)
            return 0;
        int sum = 0;
        for(int i=0; i < _nVertex; ++i)
            sum += _matrix[row][i];
        return sum;
    }
};


// functions:
int calcKorasaju(clsAdjacencyVector const * const adjVector,
                  int *components);

clsList<clsVector<int> > calcDemucron(clsAdjacencyMatrix const * const _matrix);
clsList<clsVector<int> > calcTarjan(clsAdjacencyMatrix const * const _matrix);

clsVector<sctGraphArc> calcPrim(clsAdjacencyVector const * const G);
clsVector<sctGraphArc> calcKraskal(clsAdjacencyVector const * const G);

#endif // GRAPHS_H
