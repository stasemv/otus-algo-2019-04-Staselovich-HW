#ifndef HEAP_MANAGER_H
#define HEAP_MANAGER_H

#include "stdlib.h"
#include "stdio.h"

#ifdef __cplusplus
extern "C" {
#endif

//#define MAX_BLOCKS_AMOUNT 256
#define MAX_BLOCKS_LIMIT 256
#define MIN_BLOCKS_SIZE 64
#define BLOCKS_ALLIGN 8

typedef struct sctHeapBlock {
    void *ptr;
    size_t size;
    sctHeapBlock *prev;
    sctHeapBlock *next;
    char isBisy;
    char allign[7]; // allign by 64 bits

    bool operator>(const sctHeapBlock b) const {
        return ptr > b.ptr;
    }
} sctHeapBlock;

typedef struct sctHeap {
    void *memory;
    size_t size;
    size_t blocksAmount;
    size_t maxBlocksAmount;
    sctHeapBlock *blocks;
    sctHeapBlock *lastBlock;
//    sctHeapBlock blocks[MAX_BLOCKS_AMOUNT];
} sctHeap;

sctHeap * createHeapManager(void *buf, size_t bufSize);
sctHeap * createHeapManager(void *buf, size_t bufSize);
//void deleteHeapManager(sctHeap * heap);
void * allocHeap(sctHeap *heap, const size_t objSize);
void * allocNHeap(sctHeap *heap, const size_t objSize, const size_t objAmount);
bool freeHeap(void *ptr, sctHeap *heap);

void printHeap(FILE *fout, sctHeap *heap);
void printHeapMemory(FILE *fout, sctHeap *heap);

#ifdef __cplusplus
}
#endif

#endif // HEAP_MANAGER_H
