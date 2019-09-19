#ifndef DYNAMIC_ARRAYS_H
#define DYNAMIC_ARRAYS_H

#include <stddef.h>
#include <cstring>
#include <stdexcept>
#include <stdio.h>

#include <lists.h>

template<class T> class clsDynArr
{
protected :
    T *_array;
    int _size;
    virtual void resize(int index) {}
    virtual void decrsize() {}

public:
    explicit clsDynArr() {
        _size = 0;
        _array = NULL;
    }
//    virtual ~clsDynArr() {}

    virtual int size() { return 0; }
    virtual void add(T &item) {}
    virtual T get( int index) {}

    virtual void add_i(T item, int index) {} // + shift to tail
    virtual T remove(int index) {}
    T& operator [](int idx) const {
        return _array[idx];
    }
    T& at(int idx) const {
        return _array[idx];
    }

    void push_back(T item) {
        add(item);
    }
    bool empty() const {
        return (_size == 0);
    }
    virtual void printArray() {}
    virtual void reverse() {
        for(int i=0; i < _size/2; ++i) {
            T buf = _array[i];
            _array[i] = _array[_size - i - 1];
            _array[_size - i - 1] = buf;
        }
    }
};

template<class T> class clsNoobDynArr : public clsDynArr<T>
{
protected :
    void resize(int index) {
        int tail = clsDynArr<T>::_size - index;
        T *newArr = new T[clsDynArr<T>::_size + 1];
        memcpy(newArr, clsDynArr<T>::_array, index*sizeof(T));
        memcpy(&newArr[index+1],
               &(clsDynArr<T>::_array[index]),
               tail*sizeof(T));
        if(clsDynArr<T>::_array)
            delete[] clsDynArr<T>::_array;
        clsDynArr<T>::_size++;
        clsDynArr<T>::_array = newArr;
    }
    void decrsize(int index) {
        if(clsDynArr<T>::_size > 0) {
            clsDynArr<T>::_size--;
            int tail = clsDynArr<T>::_size - index;
            T *newArr = new T[clsDynArr<T>::_size];
            memcpy(newArr, clsDynArr<T>::_array, index*sizeof(T));
            memcpy(&newArr[index],
                   &clsDynArr<T>::_array[index+1],
                   tail*sizeof(T));
            if(clsDynArr<T>::_array)
                delete[] clsDynArr<T>::_array;
            clsDynArr<T>::_array = newArr;
        }
    }

public:
    explicit clsNoobDynArr() {
        clsDynArr<T>::_size = 0;
        clsDynArr<T>::_array = NULL;
    }
    int size() {
        return clsDynArr<T>::_size;
    }
    void add(T &item) {
        resize(clsDynArr<T>::_size);
        clsDynArr<T>::_array[clsDynArr<T>::_size-1] = item;
    }
    T get( int index) {
        if((index >= 0) && (index < clsDynArr<T>::_size))
            return clsDynArr<T>::_array[index];
        return T();
    }
    void add_i(T item, int index) {
        if((index >= 0) && (index <= clsDynArr<T>::_size)) {
            resize(index);
            clsDynArr<T>::_array[index] = item;
        }
    }
    virtual T remove(int index) {
        if((index >= 0) && (index < clsDynArr<T>::_size)) {
            T item = get(index);
            decrsize(index);
            return item;
        }
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
    void decrsize() {
        if(clsDynArr<T>::_size <= _capacity - _block) {
//            printf("remove block\n");
            _capacity -= _block;
            T *newArr = new T[_capacity];
            memcpy(newArr, clsDynArr<T>::_array, _capacity*sizeof(T));
            if(clsDynArr<T>::_array)
                delete clsDynArr<T>::_array;
            clsDynArr<T>::_array = newArr;
        }
    }
    void construct(int block_size) {
        clsDynArr<T>::_array = NULL;
        _block = block_size;
        clsDynArr<T>::_size = 0;
        _capacity = 0;
    }

public:
    clsBlockArr(int block_size) { construct(block_size); }
    clsBlockArr() { construct(10); }

    int size() {
        return clsDynArr<T>::_size;
    }
    void add(T &item) {
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

    void add_i(T item, int index) {
        if((index >= 0) && (index <= clsDynArr<T>::_size)) {
            if(clsDynArr<T>::_size == _capacity)
                resize();
//            printf(" add %i to %i place\n", (int)item, index);
            int tail = clsDynArr<T>::_size - index;
            memcpy(&(clsDynArr<T>::_array[index+1]),
                   &(clsDynArr<T>::_array[index]),
                   tail*sizeof(T));
            clsDynArr<T>::_array[index] = item;
            clsDynArr<T>::_size++;
        }
    }
    virtual T remove(int index) {
        if((index >= 0) && (index < clsDynArr<T>::_size)) {
            T item = get(index);
//            printf("removed %i\n", (int)item);
            int tail = clsDynArr<T>::_size - index - 1;
            memcpy(&clsDynArr<T>::_array[index],
                   &clsDynArr<T>::_array[index+1],
                    tail*sizeof(T));
            clsDynArr<T>::_size--;
            decrsize();
            return item;
        }
        return T();
    }
};

template<class T> class clsFactorArr : public clsDynArr<T>
{
private:
    int _factor;
    int _capacity;
    int _init_length;
    void resize() {
        int extention = _capacity * _factor / 100;
        T *newArr = new T[_capacity + extention];
        memcpy(newArr, clsDynArr<T>::_array, _capacity*sizeof(T));
        _capacity += extention;
        if(clsDynArr<T>::_array)
            delete clsDynArr<T>::_array;
        clsDynArr<T>::_array = newArr;
    }
    void decrsize() {
        int residue = (double)_capacity
                * ((double)_factor / ((double)_factor + 100.0));
        if((clsDynArr<T>::_size <= _capacity - residue)
                && (_capacity - residue > _init_length)) {
//            printf("remove block\n");
            _capacity -= residue;
            T *newArr = new T[_capacity];
            memcpy(newArr, clsDynArr<T>::_array, _capacity*sizeof(T));
            if(clsDynArr<T>::_array)
                delete clsDynArr<T>::_array;
            clsDynArr<T>::_array = newArr;
        }
    }
    void construct(int factor, int init_length) {
        _init_length = init_length;
        clsDynArr<T>::_array = new T[init_length];
        _factor = factor;
        clsDynArr<T>::_size = 0;
        _capacity = init_length;
    }
public:
    clsFactorArr(int factor, int init_length) { construct(factor, init_length); }
    clsFactorArr() { construct(50, 10); }

    size_t size() const {
        return clsDynArr<T>::_size;
    }
    void add(T &item) {
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
    void add_i(T item, int index) {
        if((index >= 0) && (index <= clsDynArr<T>::_size)) {
            if(clsDynArr<T>::_size == _capacity)
                resize();
//            printf(" add %i to %i place\n", (int)item, index);
            int tail = clsDynArr<T>::_size - index;
            memcpy(&(clsDynArr<T>::_array[index+1]),
                   &(clsDynArr<T>::_array[index]),
                   tail*sizeof(T));
            clsDynArr<T>::_array[index] = item;
            clsDynArr<T>::_size++;
        }
    }
    virtual T remove(int index) {
        if((index >= 0) && (index < clsDynArr<T>::_size)) {
            T item = get(index);
//            printf("removed %i\n", (int)item);
            int tail = clsDynArr<T>::_size - index - 1;
            memcpy(&clsDynArr<T>::_array[index],
                   &clsDynArr<T>::_array[index+1],
                    tail*sizeof(T));
            clsDynArr<T>::_size--;
            decrsize();
            return item;
        }
        return T();
    }
    virtual void printArray(FILE *fout) {

        int n = clsDynArr<T>::_size;
        for(int i=0; i < n; ++i) {
            fprintf(fout, "%i\t", (int)clsDynArr<T>::_array[i]);
        }
        printf("\n");
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
    void decrsize() {
        if(clsDynArr<T>::_size <= _capacity - _vector) {
//            printf("remove block\n");
            int last_idx = _matrix->size() - 1;
            _capacity -= _vector;
            _matrix->remove(last_idx);
        }
    }
    void construct (int vector) {
        _matrix = new clsNoobDynArr<clsBlockArr<T> >;
        _vector = vector;
        clsDynArr<T>::_size = 0;
        _capacity = 0;
    }

public:
    clsMatrixArr(int vector) { construct(vector); }
    clsMatrixArr() { construct(10); }

    int size() {
        return clsDynArr<T>::_size;
    }
    void add(T &item) {
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
    void add_i(T item, int index) {
        if((index >= 0) && (index <= clsDynArr<T>::_size)) {
            if(clsDynArr<T>::_size == _capacity)
                resize();
//            printf(" add %i to %i place\n", (int)item, index);

            int row = index / _vector;
            for(int i=clsDynArr<T>::_size / _vector; i > row; --i) {
                int last_idx = _matrix->getPtr(i-1)->size() - 1;
                T val = _matrix->getPtr(i-1)->get(last_idx);
                _matrix->getPtr(i)->add_i(val, 0);
                _matrix->getPtr(i-1)->remove(last_idx);
            }
            _matrix->getPtr(row)->add_i(item, index % _vector);
            clsDynArr<T>::_size++;
        }
    }
    virtual T remove(int index) {
        if((index >= 0) && (index < clsDynArr<T>::_size)) {
            T item = get(index);
//            printf("removed %i (idx = %i)\n", (int)item, index);

            int row = index / _vector;
            _matrix->getPtr(row)->remove(index % _vector);
            clsDynArr<T>::_size--;
            for(int i=row; i < clsDynArr<T>::_size / _vector; ++i) {
                T val = _matrix->getPtr(i+1)->get(0);
                _matrix->getPtr(i)->add(val);
                _matrix->getPtr(i+1)->remove(0);
            }
            decrsize();
            return item;
        }
        return T();
    }
};

template<class T> class clsSpaceArr : public clsDynArr<T>
{
private:
    int _vector;
    clsListNode<clsBlockArr<T> > *_matrix;
    clsListNode<clsBlockArr<T> > *_lastBlock;
    int _listSize;
    void resize() {
        if(_lastBlock->getItem().size() >= _vector) {
            clsListNode<clsBlockArr<T> > *_newNode = new clsListNode<clsBlockArr<T> >;
            _lastBlock->setNext(_newNode);
            _lastBlock = _lastBlock->getNext();
            _listSize++;
        }        
    }
    void resize(clsListNode<clsBlockArr<T> > *node, int offset) {
        if(node->getItem().size() >= _vector) {
            clsListNode<clsBlockArr<T> > *_newNode = new clsListNode<clsBlockArr<T> >;
            _newNode->setNext(node->getNext());
            node->setNext(_newNode);

            clsBlockArr<T> *block = node->getItemPtr();
            clsBlockArr<T> *newBlock = _newNode->getItemPtr();
            for(int i=offset; i < block->size(); ++i)
                newBlock->add(block->get(i));
            for(int i=block->size()-1; i >= offset; --i)
                block->remove(i);

            _listSize++;
        }
    }

//    clsMatrixArr<T>::_matrix->add_i(clsBlockArr<T>(clsMatrixArr<T>::_vector),
//                                    blockIndex+1);
//    clsMatrixArr<T>::_capacity += clsMatrixArr<T>::_vector;
//    clsBlockArr<T> *nextBlock = clsMatrixArr<T>::_matrix->getPtr(blockIndex+1);
//    for(int i=offset; i < block->size(); ++i)
//        nextBlock->add(block->get(i));
//    for(int i=block->size()-1; i >= offset; --i)
//        block->remove(i);

    void decrsize(clsListNode<clsBlockArr<T> > *node) {
        if(node->getItemPtr()->size() < 1) {
            printf("remove block\n");
            clsListNode<clsBlockArr<T> > *prevNode = _matrix;
            if(node == _matrix) {
                if(_matrix->getNext()) {
                    _matrix = _matrix->getNext();
                    delete node;
                    _listSize--;
                }
            }
            else {
                while(prevNode && (prevNode->getNext() != node))
                    prevNode = prevNode->getNext();
                if(prevNode) {
                    prevNode->setNext(node->getNext());
                    delete node;
                    _listSize--;
                }
            }
        }
    }
    clsListNode<clsBlockArr<T> > * getNode(const int index,
                                           int * const offset) {
        int idx = index;
        clsListNode<clsBlockArr<T> > *node;
        clsListNode<clsBlockArr<T> > *prevNode = _matrix;
        do {
            node = prevNode;
            idx -= node->getItemPtr()->size();
            if(idx < 0)
                break;
            prevNode = prevNode->getNext();
        } while(prevNode != NULL);
        *offset = node->getItemPtr()->size() + idx;
        return node;
    }
    clsBlockArr<T> * getBlock(const int index,
                              int * const offset) {
        clsListNode<clsBlockArr<T> > *node = getNode(index, offset);
        return node->getItemPtr();
    }    
    void construct (int vector) {
        _matrix = new clsListNode<clsBlockArr<T> >;
        _lastBlock  =_matrix;
        _vector = vector;
        clsDynArr<T>::_size = 0;
        _listSize = 0;
    }

public:
    clsSpaceArr(int vector) { construct(vector); }
    clsSpaceArr() { construct(10); }

    int size() {
        return clsDynArr<T>::_size;
    }
    void add(T &item) {
        resize();
        _lastBlock->getItemPtr()->add(item);
        clsDynArr<T>::_size++;
    }
    T get(int index) {
        if((index >= 0) && (index < clsDynArr<T>::_size)) {
            int offset = 0;
            clsBlockArr<T> *block = getBlock(index, &offset);
            return block->get(offset);
        }
        return T();
    }
    virtual void printArray() {
        clsListNode<clsBlockArr<T> > *node = _matrix;
        do {
            clsBlockArr<T> *block = node->getItemPtr();
            int n2 = block->size();
            for(int j=0; j < n2; ++j) {
                T val = block->get(j);
                printf("%i\t", (int)val);
            }
            printf("\n");
            node = node->getNext();
        } while(node != NULL);
        printf("\n");
    }

    void add_i(T item, int index) {
        if((index >= 0) && (index <= clsDynArr<T>::_size)) {
            int offset = 0;
            clsListNode<clsBlockArr<T> > *node = getNode(index, &offset);
            printf(" add %i to %i place\n", (int)item, index);
            resize(node, offset);

            node->getItemPtr()->add_i(item, offset);
            clsDynArr<T>::_size++;
        }
    }
    virtual T remove(int index) {
        if((index >= 0) && (index < clsDynArr<T>::_size)) {
            int offset = 0;
            clsListNode<clsBlockArr<T> > *node = getNode(index, &offset);
            T item = node->getItemPtr()->remove(offset);
            printf("removed %i (idx = %i)\n", (int)item, index);

            clsDynArr<T>::_size--;
            decrsize(node);
            return item;
        }
        return T();
    }
};

template<class T> class clsVector : public clsFactorArr<T>
{
public:
    clsVector() : clsFactorArr<T>() {}

};

#endif // DYNAMIC_ARRAYS_H
