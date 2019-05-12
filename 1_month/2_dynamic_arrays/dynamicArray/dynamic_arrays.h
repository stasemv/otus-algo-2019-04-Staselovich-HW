#ifndef DYNAMIC_ARRAYS_H
#define DYNAMIC_ARRAYS_H

#include <stddef.h>
#include <cstring>

template<class T> class clsDynArr
{
protected :
    T *_array;
    int _size;
    virtual void resize() {}

public:
    explicit clsDynArr() {
        _size = 0;
        _array = NULL;
    }

    virtual int size() { return 0; }
    virtual void add(T item) {}
    virtual T get( int index) {}

//    virtual void add_i(T item, int index); // + shift to tail
//    virtual T remove(int index);
};

template<class T> class clsNoobDynArr : public clsDynArr<T>
{
protected :
    void resize() {
        T *newArr = new T[clsDynArr<T>::_size + 1];
        memcpy(newArr, clsDynArr<T>::_array, clsDynArr<T>::_size*sizeof(T));
        clsDynArr<T>::_size++;
        if(clsDynArr<T>::_array)
            delete clsDynArr<T>::_array;
        clsDynArr<T>::_array = newArr;
    }

public:
    explicit clsNoobDynArr() {
        clsDynArr<T>::_size = 0;
        clsDynArr<T>::_array = NULL;
    }
    int size() {
        return clsDynArr<T>::_size;
    }
    void add(T item) {
        resize();
        clsDynArr<T>::_array[clsDynArr<T>::_size-1] = item;
    }
    T get( int index) {
        if((index >= 0) && (index < clsDynArr<T>::_size))
            return clsDynArr<T>::_array[index];
        return T();
    }
    T* getPtr(int index) {
        if((index >= 0) && (index < clsDynArr<T>::_size))
            return &(clsDynArr<T>::_array[index]);
        return NULL;
    }
};

template<class T> class clsBlockArr : public clsDynArr<T>
{
private:
    int _block;
    int _capacity;
    void resize() {
        T *newArr = new T[_capacity + _block];
        memcpy(newArr, clsDynArr<T>::_array, _capacity*sizeof(T));
        _capacity += _block;
        if(clsDynArr<T>::_array)
            delete clsDynArr<T>::_array;
        clsDynArr<T>::_array = newArr;
    }

public:
    clsBlockArr(int block_size) {
        clsDynArr<T>::_array = NULL;
        _block = block_size;
        clsDynArr<T>::_size = 0;
        _capacity = 0;
    }
    clsBlockArr() : clsBlockArr(10) { }

    int size() {
        return clsDynArr<T>::_size;
    }
    void add(T item) {
        if(clsDynArr<T>::_size == _capacity)
            resize();
        clsDynArr<T>::_array[clsDynArr<T>::_size] = item;
        clsDynArr<T>::_size++;
    }
    T get( int index) {
        if((index >= 0) && (index < clsDynArr<T>::_size))
            return clsDynArr<T>::_array[index];
        return T();
    }
};

template<class T> class clsFactorArr : public clsDynArr<T>
{
private:
    int _factor;
    int _capacity;
    void resize() {
        int extention = _capacity * _factor / 100;
        T *newArr = new T[_capacity + extention];
        memcpy(newArr, clsDynArr<T>::_array, _capacity*sizeof(T));
        _capacity += extention;
        if(clsDynArr<T>::_array)
            delete clsDynArr<T>::_array;
        clsDynArr<T>::_array = newArr;
    }

public:
    clsFactorArr(int factor, int init_length) {
        clsDynArr<T>::_array = new T[init_length];
        _factor = factor;
        clsDynArr<T>::_size = 0;
        _capacity = init_length;
    }
    clsFactorArr() : clsFactorArr(50, 10) { }

    int size() {
        return clsDynArr<T>::_size;
    }
    void add(T item) {
        if(clsDynArr<T>::_size == _capacity)
            resize();
        clsDynArr<T>::_array[clsDynArr<T>::_size] = item;
        clsDynArr<T>::_size++;
    }
    T get(int index) {
        if((index >= 0) && (index < clsDynArr<T>::_size))
            return clsDynArr<T>::_array[index];
        return T();
    }
};

template<class T> class clsMatrixArr : public clsDynArr<T>
{
private:
    int _vector;
    int _capacity;
    clsNoobDynArr<clsBlockArr<T> > *_matrix;
    void resize() {
        _matrix->add(clsBlockArr<T>(_vector));
        _capacity += _vector;
    }

public:
    clsMatrixArr(int vector) {
        _matrix = new clsNoobDynArr<clsBlockArr<T> >;
        _vector = vector;
        clsDynArr<T>::_size = 0;
        _capacity = 0;
    }
    clsMatrixArr() : clsMatrixArr(10) { }

    int size() {
        return clsDynArr<T>::_size;
    }
    void add(T item) {
        if(clsDynArr<T>::_size >= _capacity)
            resize();
        clsBlockArr<T> *_block = _matrix->getPtr(clsDynArr<T>::_size / _vector);
        if(_block)
            _block->add(item);
        clsDynArr<T>::_size++;
    }
    T get(int index) {
        if((index >= 0) && (index < clsDynArr<T>::_size)) {
            clsBlockArr<T> block = _matrix->get(index / _vector);
            return block.get(index % _vector);
        }
        return T();
    }
};

#endif // DYNAMIC_ARRAYS_H
