#ifndef GRAPHS_DATA_H
#define GRAPHS_DATA_H

#include "../../../1_month/2_dynamic_arrays/dynamicArray/dynamic_arrays.h"

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
    bool operator > (const sctGraphArc & a) const {
        return weight > a.weight;
    }
    bool operator == (const sctGraphArc & a) const {
        return (start == a.start) && (end == a.end)
                && (weight == a.weight);
    }
};

class clsAdjacencyVector
{
protected:
    clsVector<sctAdjArc> *_array;
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
        _array = new clsVector<sctAdjArc>[_nVertex]();
    }
    ~clsAdjacencyVector() {
        delete[] _array;
    }
    int nVertex() const { return _nVertex; }

    bool addArc(sctGraphArc arc);
    bool addArc(int start, int end, int w = 1.0);
    bool addEdge(sctGraphArc arc);
    bool addEdge(int start, int end, int w = 1.0);
    int getArcWeight(int start, int end) const;
    int getArcsAmount();

    clsVector<sctGraphArc> getArcsVector() const;
    clsVector<sctGraphArc> getArcsVector(int v) const;
    clsVector<sctGraphArc> getOuterArcs(clsVector<int> *_v) const;
    clsVector<sctGraphArc> getOuterArcs(int v) const;

};

class clsAdjacencyMatrix {
protected:
    int **_matrix;
    int _nVertex;
public:
    clsAdjacencyMatrix() : _matrix(NULL), _nVertex(0) {}
    clsAdjacencyMatrix(int n) : _nVertex(n) {
        _matrix = new int*[_nVertex];
        for(int i=0; i < _nVertex; ++i) {
            _matrix[i] = new int[_nVertex];
            memset(_matrix[i], 0, _nVertex*sizeof(int));
        }
    }
    clsAdjacencyMatrix(clsAdjacencyVector const * const v) {
        _nVertex = v->nVertex();
        _matrix = new int*[_nVertex];
        for(int i=0; i < _nVertex; ++i) {
            _matrix[i] = new int[_nVertex];
        memset(_matrix[i], 0, _nVertex*sizeof(int));
    }
        clsVector<sctGraphArc> arcs = v->getArcsVector();
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

struct sctUnionFind {
    sctUnionFind *_root;
    int _index;

    sctUnionFind() : _root(NULL), _index(0) {}
    sctUnionFind *root() {
        if(_root)
            return _root->root();
        return this;
    }
    void merge(sctUnionFind *u) {
        sctUnionFind *root_ = u->root();
        if(_root)
            root_->_root = _root;
        else
            root_->_root = this;
    }
    int find() {
        if(_root)
            return _root->find();
        return _index;
    }
};

struct sctPathPoint {
    int distance;
    int index;
    int from;

    bool operator > (const sctPathPoint & a) const {
        return distance > a.distance;
    }
};

#endif // GRAPHS_DATA_H
