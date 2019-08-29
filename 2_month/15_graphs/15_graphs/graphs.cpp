#include "graphs.h"

#include "stdlib.h"
#include "../../../1_month/2_dynamic_arrays/dynamicArray/dynamic_arrays.h"

#include <algorithm>
#include <set>

bool clsAdjacencyVector::addArc(sctGraphArc arc) {
    return addArc(arc.start, arc.end, arc.weight);
}

bool clsAdjacencyVector::addArc(int start, int end, int w) {
    if(!isIndexValid(start) || !isIndexValid(end))
        return 0;
#ifdef _USE_STD_VECTOR_
    std::vector<sctAdjArc> *list = &_array[start];
#else
    clsList<sctAdjArc> *list = &_array[start];
#endif
    for(int i=0; i < (int)list->size(); ++i)
    if(list->at(i).end == end)
        return 0;       // arc alredy exist
    sctAdjArc arc(end, w);
    list->push_back(arc);
    if((int)list->size() > _nMaxEdges)
        _nMaxEdges = list->size();
    _nArcs++;
    return 1;
}

bool clsAdjacencyVector::addEdge(sctGraphArc arc) {
    return addEdge(arc.start, arc.end, arc.weight);
}

bool clsAdjacencyVector::addEdge(int start, int end, int w) {
    return addArc(start, end, w) | addArc(end, start, w);
}

#ifdef _USE_STD_VECTOR_
std::vector<sctGraphArc> clsAdjacencyVector::getArcsVector() const {
    std::vector<sctGraphArc> v;
#else
clsVector<sctGraphArc> clsAdjacencyVector::getArcVector() const {
    clsVector<sctGraphArc> v;
#endif
    for(int i=0; i < _nVertex; ++i) {
        int n = _array[i].size();
        for(int j=0; j < n; ++j) {
            sctGraphArc arc(i, _array[i][j].end, _array[i][j].weight);
            v.push_back(arc);
        }
    }
    return v;
}

#ifdef _USE_STD_VECTOR_
std::vector<sctGraphArc> clsAdjacencyVector::getArcsVector(int u) const {
    std::vector<sctGraphArc> v;
#else
clsVector<sctGraphArc> clsAdjacencyVector::getArcVector(int u) const {
    clsVector<sctGraphArc> v;
#endif
    int n = _array[u].size();
    for(int j=0; j < n; ++j) {
        sctGraphArc arc(u, _array[u][j].end, _array[u][j].weight);
        v.push_back(arc);
    }
    return v;
}

#ifdef _USE_STD_VECTOR_
std::vector<sctGraphArc> clsAdjacencyVector::getOuterArcs(std::vector<int> *_v) const {
    std::vector<sctGraphArc> v;
#else
clsVector<sctGraphArc> clsAdjacencyVector::getOuterArcs(std::vector<int> _v) const {
    clsVector<sctGraphArc> v;
#endif
    std::set<int> vert;
    int n = _v->size();
    for(int i=0; i < n; ++i)
        vert.insert(_v->at(i));

    for(std::set<int>::iterator it = vert.begin();
        it != vert.end(); ++it) {
        int u = *it;
        int n = _array[u].size();
        for(int j=0; j < n; ++j)
            if(vert.find(_array[u][j].end) == vert.end()) {
                sctGraphArc arc(u, _array[u][j].end, _array[u][j].weight);
                v.push_back(arc);
            }
    }
    return v;
}

int clsAdjacencyVector::getArcWeight(int start, int end) const
{
#ifdef _USE_STD_VECTOR_
    const std::vector<sctAdjArc> *list = &_array[start];
#else
    const clsList<sctAdjArc> *list = &_array[start];
#endif
    for(int i=0; i < (int)list->size(); ++i)
    if(list->at(i).end == end)
        return list->at(i).weight;
    return 0;
}

int clsAdjacencyVector::getArcsAmount()
{
//    int n = 0;
//    for(int i=0; i < _nVertex; ++i)
//        n += _array[i].size();
//    return n;
    return _nArcs;
}



clsStack<int> DFS(clsAdjacencyVector const * const G)
{
    clsStack<int> path;
    int N = G->nVertex();
    char *checked = new char[N];
    memset(checked, 0, N);
    int v = 0;
    clsStack<int> path_DFS;
    checked[v] = 1;
    path.push(v);
    while((int)path.size() < N) {
        int next = -1;
        for(int i=0; i < N; ++i)
            if(G->getArcWeight(v, i))
                if(!checked[i]) {
                    next = i;
                    break;
                }
        if(next > -1) {
            path_DFS.push(v);
            v = next;
            checked[v] = 1;
            path.push(v);
        }
        else if(!path_DFS.empty()) {
            v = path_DFS.top();
            path_DFS.pop();
        }
        else {
            for(int i=0; i < N; ++i)
                if(!checked[i]) {
                    v = i;
                    path_DFS.push(v);
                    checked[v] = 1;
                    path.push(v);
                    break;
                }
        }
    }
    return path;
}

int calcKorasaju(clsAdjacencyVector const * const adjVector,
                  int *components)
{
    int v_amount = adjVector->nVertex();
    clsAdjacencyVector *H = new clsAdjacencyVector(v_amount);
#ifdef _USE_STD_VECTOR_
    std::vector<sctGraphArc> in_arcs = adjVector->getArcsVector();
#else
    clsVector<sctGraphArc> in_arcs = adjVector->getArcVector();
#endif
    for(int i=0; i < (int)in_arcs.size(); ++i)
        H->addArc(in_arcs[i].end, in_arcs[i].start, in_arcs[i].weight);

    clsStack<int> path_H = DFS(H);

    // 3
    char *checked = new char[v_amount];
    clsStack<int> path_DFS;
    memset(components, 0, v_amount*sizeof(int));
    memset(checked, 0, v_amount);
    int v_G = path_H.top();
    path_H.pop();
    path_DFS = clsStack<int>();
    checked[v_G] = 1;
    int component_num = 1;
    components[v_G] = component_num;
    while(!path_H.empty()) {
        int next = -1;
        for(int i=0; i < v_amount; ++i)
            if(adjVector->getArcWeight(v_G, i))
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

    delete[] checked;
    delete H;
    return component_num;
}

std::vector<std::vector<int> > calcDemucron(clsAdjacencyMatrix const * const _matrix)
{
    std::vector<std::vector<int> > levels;
    int N = _matrix->nVertex();
    int *sums = new int[N];
    std::vector<int> vertexes;
    for(int i=0; i < N; ++i) {
        sums[i] = _matrix->colSum(i);
        vertexes.push_back(i);
    }

    int level = 0;
    int amount = N;
    while(amount) {
        std::vector<int> zeros;
        for(int i=0; i < N; ++i)
            if(sums[vertexes[i]] == 0)
                zeros.push_back(vertexes[i]);
        if(zeros.empty())
            break;
        levels.push_back(std::vector<int>());
        for(int i=0; i < (int)zeros.size(); ++i) {
            int v = zeros[i];
            levels[level].push_back(v);
            int *row = _matrix->at(v);
            for(int j=0; j < N; ++j)
                if(row[j])
                    sums[j]--;
            amount--;
            sums[v]--;
        }
        level++;
    }

    delete[] sums;
    return levels;
}

enum enmVertexColor {
    enm_VC_white = 0,
    enm_VC_gray,
    enm_VC_black
};

std::vector<std::vector<int> > calcTarjan(clsAdjacencyMatrix const * const _matrix)
{
    std::vector<std::vector<int> > levels;
    int N = _matrix->nVertex();

    enmVertexColor *vColors = new enmVertexColor[N];

//    clsStack<int> path;
//    char *checked = new char[N];
//    memset(checked, 0, N);
//    int v = 0;
//    clsStack<int> path_DFS;
//    checked[v] = 1;
//    path.push(v);
//    while((int)path.size() < N) {
//        int next = -1;
//        for(int i=0; i < N; ++i)
//            if(G->getArcWeight(v, i))
//                if(!checked[i]) {
//                    next = i;
//                    break;
//                }
//        if(next > -1) {
//            path_DFS.push(v);
//            v = next;
//            checked[v] = 1;
//            path.push(v);
//        }
//        else if(!path_DFS.empty()) {
//            v = path_DFS.top();
//            path_DFS.pop();
//        }
//        else {
//            for(int i=0; i < N; ++i)
//                if(!checked[i]) {
//                    v = i;
//                    path_DFS.push(v);
//                    checked[v] = 1;
//                    path.push(v);
//                    break;
//                }
//        }
//    }

    delete[] vColors;
    return levels;
}

sctGraphArc * findMinArc(std::vector<sctGraphArc> *arcs)
{
    if(arcs->size() <= 0)
        return NULL;
    size_t size = arcs->size();
    sctGraphArc * min = &arcs->at(0);
    for(size_t i=1; i < size; ++i)
        if(arcs->at(i).weight < min->weight)
            min = &arcs->at(i);
    return min;
}

std::vector<int> getVertexList(std::vector<sctGraphArc> * arcs)
{
    std::set<int> v;
    int n = arcs->size();
    for(int i=0; i < n; ++i) {
        v.insert(arcs->at(i).start);
        v.insert(arcs->at(i).end);
    }

    std::vector<int> vert;
    for(std::set<int>::iterator it = v.begin();
        it != v.end(); ++it)
        vert.push_back(*it);
    return vert;
}

std::vector<sctGraphArc> calcPrim(clsAdjacencyVector const * const G)
{
    std::vector<sctGraphArc> ostov;
    int v0 = rand() % G->nVertex();
    std::vector<sctGraphArc> edges = G->getArcsVector(v0);
    sctGraphArc * minArc = findMinArc(&edges);
    ostov.push_back(*minArc);
    while(((int)ostov.size()+1) < G->nVertex()) {
        std::vector<int> verts = getVertexList(&ostov);
        edges = G->getOuterArcs(&verts);
        minArc = findMinArc(&edges);
        if(!minArc)
            break;
        ostov.push_back(*minArc);
    }
    return ostov;
}

std::vector<sctGraphArc> calcKraskal(clsAdjacencyVector const * const G)
{
    std::vector<sctGraphArc> ostov;
    size_t n = G->nVertex();
    if(n <= 0)
        return ostov;

    std::set<int> ostovVerts;
    std::vector<sctGraphArc> arcs = G->getArcsVector();
    std::sort(arcs.begin(), arcs.end());
    ostov.push_back(arcs[0]);
    ostovVerts.insert(arcs[0].start);
    ostovVerts.insert(arcs[0].end);
    arcs.erase(arcs.begin());

    while((ostov.size()+1) < n) {
        bool isNewArcFound = false;
        for(std::vector<sctGraphArc>::iterator it = arcs.begin();
            it != arcs.end(); ++it) {
            if((ostovVerts.find((*it).start) != ostovVerts.end())
                    || (ostovVerts.find((*it).end) != ostovVerts.end()))
                if((ostovVerts.find((*it).start) == ostovVerts.end())
                        || (ostovVerts.find((*it).end) == ostovVerts.end())) {
                    ostov.push_back(*it);
                    ostovVerts.insert((*it).start);
                    ostovVerts.insert((*it).end);
                    arcs.erase(it);
                    isNewArcFound = true;
                    break;
                }
        }
        if(!isNewArcFound)
            break;
    }

    return ostov;
}