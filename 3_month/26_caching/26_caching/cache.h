#ifndef CACHE_H
#define CACHE_H

#include <stdlib.h>
#include <time.h>

#include "../../../1_month/2_dynamic_arrays/dynamicArray/dynamic_arrays.h"
//#include "../../../1_month/9_trees/binary_trees/avl_tree.h"

template<class T>
struct sctTimedCacheItem {
    T _data;
    int _key;
    time_t _lastTime;

    bool operator> (const sctTimedCacheItem<T> &b) const {
        return _lastTime > b._lastTime;
    }
    bool operator< (const sctTimedCacheItem<T> &b) const {
        return _lastTime < b._lastTime;
    }
    bool operator== (const sctTimedCacheItem<T> &b) const {
        return _key == b._key;
    }
};

template<class T>
class clsCache {
protected:
    size_t _max_size;   // [bytes]
//    size_t _size;   // [bytes]
    time_t _ttl;    // [sec]
//    clsAVLTree<sctTimedCacheItem<T> > *caches;
    clsVector<sctTimedCacheItem<T> > *caches;
    size_t _hits;
    size_t _misses;
    size_t _unsets;
    size_t _item_size;
public:
    clsCache() : _max_size(1024*16), _ttl(10), _hits(0), _misses(0), _unsets(0),
    _item_size(sizeof(sctTimedCacheItem<T>)) {
//        caches = new clsAVLTree<T>();
        caches = new clsVector<sctTimedCacheItem<T> >();
    }
    clsCache(size_t size_bytes, size_t ttl_msec) : _max_size(size_bytes), _ttl(ttl_msec),
    _hits(0), _misses(0), _unsets(0), _item_size(sizeof(sctTimedCacheItem<T>)) {
//        caches = new clsAVLTree<sctTimedCacheItem<T> >();
        caches = new clsVector<sctTimedCacheItem<T> >();
    }
    ~clsCache() {
        if(caches)
            delete caches;
    }
    void set_ttl(size_t ttl) {
        _ttl = ttl;
    }
    size_t get_ttl(size_t ttl) {
        return _ttl;
    }

    T * get(int key) {
        time_t time_ = time(NULL);
        sctTimedCacheItem<T> item = {T(), key, time_ - _ttl};
        sctTimedCacheItem<T> *valid = NULL;
        for(int i=caches->size() - 1; i >=0; --i)
            if((caches->at(i) == item) && (caches->at(i) > item)) {
                valid = &caches->at(i);
                break;
            }
        if(valid)
            _hits++;
        else {
            _misses++;
            return NULL;
        }
        return &valid->_data;
    }
    bool set(int key, T value) {
        int idx = -1;
        time_t time_ = time(NULL);
        sctTimedCacheItem<T> item = {value, key, time_ - _ttl};
        if(_max_size > (caches->size() + 1) * _item_size)
            idx = caches->size();
        else
            for(int i=caches->size() - 1; i >=0; --i)
                if(caches->at(i) < item) {
                    idx = i;
                    break;
                }
        if(idx > -1) {
            time_ = time(NULL);
            item._lastTime = time_;
            if(idx != (int)caches->size())
                caches->remove(idx);
            caches->add_i(item, idx);
            return 0;
        }
        else
            _unsets++;
        return 1;
    }
    void clear() {
        if(caches)
            delete caches;
        caches = new clsVector<sctTimedCacheItem<T> >();
        _hits = _misses = _unsets = 0;
    }

    void printState(FILE *fout) {
        fprintf(fout, "size = %lu (max size = %lu) bytes, ttl = %lu sec\n",
                caches->size()*_item_size, _max_size, _ttl);
        float gets_ = _hits + _misses;
        fprintf(fout, "hits = %lu (%f%%), misses = %lu (%f%%), unsets = %lu\n",
                _hits, (float)_hits/gets_, _misses, (float)_misses/gets_, _unsets);
    }
};

#endif // CACHE_H
