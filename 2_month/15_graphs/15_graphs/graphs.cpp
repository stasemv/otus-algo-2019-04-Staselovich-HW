#include "graphs.h"

#include "../../../1_month/2_dynamic_arrays/dynamicArray/dynamic_arrays.h"



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
std::vector<sctGraphArc> clsAdjacencyVector::getArcVector() const {
    std::vector<sctGraphArc> v;
#else
clsVector<sctGraphArc> clsAdjacencyVector::getArcVector() const {
    clsVector<sctGraphArc> v;
#endif
    for(int i=0; i < _nVertex; ++i)
        for(int j=_array[i].size()-1; j >= 0; --j) {
            sctGraphArc arc(i, _array[i][j].end, _array[i][j].weight);
            v.push_back(arc);
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


int calcKorasaju(clsAdjacencyVector const * const adjVector,
                  int *components)
{
    int v_amount = adjVector->getNVertex();
    clsAdjacencyVector *H = new clsAdjacencyVector(v_amount);
#ifdef _USE_STD_VECTOR_
    std::vector<sctGraphArc> in_arcs = adjVector->getArcVector();
#else
    clsVector<sctGraphArc> in_arcs = adjVector->getArcVector();
#endif
    for(int i=0; i < (int)in_arcs.size(); ++i)
        H->addArc(in_arcs[i].end, in_arcs[i].start, in_arcs[i].weight);

    clsStack<int> path_H;
    // depth-first search (DFS)
    char *checked = new char[v_amount];
    memset(checked, 0, v_amount);
    int v_H = 0;
    clsStack<int> path_DFS;
    checked[v_H] = 1;
    path_H.push(v_H);
    while((int)path_H.size() < v_amount) {
        int next = -1;
        for(int i=0; i < v_amount; ++i)
            if(H->getArcWeight(v_H, i))
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
