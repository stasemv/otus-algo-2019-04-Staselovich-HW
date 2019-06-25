#ifndef HASH_TABLES_H
#define HASH_TABLES_H

#include <stdio.h>
#include <cstring>

#include "../../../1_month/2_dynamic_arrays/dynamicArray/lists.h"

int simpleHash(int k, int M);

template<class T>
class clsHashTableItem
{
protected:
    int _key;
    T *_item;
public:
    clsHashTableItem() {
        clsHashTableItem(0, NULL);
    }
    clsHashTableItem(int __key, T *__item) {
        _key = __key;
        _item = new T;
        if(__item)
            memcpy(_item, __item, sizeof(T));
    }
    ~clsHashTableItem() {
        if(_item)
            delete _item;
    }
    T *item() {
        return _item;
    }
    int key() {
        return _key;
    }
};

template<class T>
class clsHashTable
{
protected:
    int _dim;
    clsList<clsHashTableItem<T> > *_items;
//    int _hash(int, int);
public:
    clsHashTable() {
        clsHashTable(10);
    }
    clsHashTable(int __dim) {
        _dim = __dim;
        _items = new clsList<clsHashTableItem<T> >[_dim];
//        clsHashTable(__dim, simpleHash);
    }
//    clsHashTable(int __dim, int __hash(int, int)) {
//        _dim = __dim;
//        _items = new clsList<clsHashTableItem<T> >[_dim];
//        _hash = __hash;
//    }
    ~clsHashTable() {
        if(_items)
            delete[] _items;
    }    
    void addItem(int index, T item) {
        clsHashTableItem<T> *newItem = new clsHashTableItem<T>(index, &item);
        int idx = simpleHash(index, _dim);
        _items[idx].add(newItem);
    }
    bool remove(int key) {
        int idx = simpleHash(key, _dim);
        return _items[idx].remove(key);
    }

    void print(FILE *fout, const char *title) {
        fprintf(fout, "%s:\n", title);
        int shift0 = 10;
        for(int i=0; i < _dim; ++i) {
            clsListNode<clsHashTableItem<T> > *node = _items[i].head();
            int shift = shift0;
            fprintf(fout, "item[%0d]: ", i);
            while(node) {
                fprintf(fout, "\n");
                for(int j=0; j<shift; ++j)
                    fprintf(fout, " ");
                fprintf(fout, "%i - %f", node->getItem().key(),
                        (double)(*(node->getItem().item())));
                node = node->getNext();
            }
            fprintf(fout, "\n");
        }
    }
};

#endif // HASH_TABLES_H
