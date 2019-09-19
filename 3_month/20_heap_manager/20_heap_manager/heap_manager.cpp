#include "heap_manager.h"

#include "cstring"
#include "../../../1_month/6_heap_tree_sort/heap_tree_sort/tree_sorts.h"

#ifdef __cplusplus
extern "C" {
#endif

size_t allignSizeHigh(size_t size, size_t allign) {
    return size +
            ((size % allign) ? allign - (size % allign) : 0);
}
size_t allignSizeLow(size_t size, size_t allign) {
    return size - (size % allign);
}

sctHeap * createHeapManager(void *buf, size_t bufSize)
{
    size_t reserved = bufSize - sizeof(sctHeap) - sizeof(sctHeapBlock);
    reserved = allignSizeLow(reserved, BLOCKS_ALLIGN);
    long int blocksAmount = reserved / MIN_BLOCKS_SIZE;
    if(blocksAmount < 1)
        return NULL;
    sctHeap *heap = (sctHeap*)buf;
    heap->memory = buf + sizeof(sctHeap);
    heap->size = reserved;
    heap->blocksAmount = 1;
    heap->blocks = (sctHeapBlock*)(heap->memory + reserved);
    heap->blocks->ptr = heap->memory;
    heap->blocks->size = reserved;
    heap->blocks->isBisy = 0;
    heap->blocks->prev = heap->blocks->next = NULL;
    heap->lastBlock = heap->blocks;
    return heap;
}

//void deleteHeapManager(sctHeap * heap)
//{

//}

void splitBlock(sctHeapBlock *bl, size_t newSize, sctHeap *heap)
{
    sctHeapBlock *newBlock = --heap->lastBlock;
    newBlock->isBisy = 0;
    newBlock->size = bl->size - newSize - sizeof(sctHeapBlock);
    newBlock->ptr = bl->ptr + newSize;
    newBlock->prev = bl;
    newBlock->next = bl->next;
    bl->size = newSize;
    bl->isBisy = 1;
    bl->next = newBlock;
    heap->blocksAmount++;
}

bool mergeBlocks(sctHeapBlock **block, sctHeapBlock *neirbour, sctHeap *heap)
{
    sctHeapBlock *left, *right;
    if((*block)->ptr > neirbour->ptr) {
        left = neirbour;
        right = (*block);
    }
    else {
        right = neirbour;
        left = (*block);
    }
    if(right->ptr != left->ptr + left->size)
        return 1;
    (*block) = left;
    (*block)->size += right->size;
    (*block)->next = right->next;
    if((*block) == heap->lastBlock) {
        *right = *left;
        (*block) = right;
    }
    else
        *right = *(heap->lastBlock);
    heap->lastBlock++;
    heap->blocksAmount--;

    return 0;
}

void * allocHeap(sctHeap *heap, const size_t objSize)
{
    size_t realSize = allignSizeHigh(objSize, BLOCKS_ALLIGN);
    sctHeapBlock *best = NULL;  // best fit
    size_t i = 0;
    sctHeapBlock *block = &heap->blocks[0];
    bool isEquals = 0;
    while(i < heap->blocksAmount) {
        if(!block->isBisy) {
            if(block->size == realSize) {
                best = block;
                isEquals = 1;
                break;
            }
            else
                if(block->size > realSize)
                    if(!best || (block->size < best->size))
                        best = block;
        }
        i++;
        block--;
    }
    if(!isEquals) {
        if(best) {
            if(best->ptr + realSize + sizeof(sctHeapBlock) > heap->lastBlock)
                return NULL;
            else
                splitBlock(best, realSize, heap);
        }
        else
            return NULL;
    }
    best->isBisy = 1;
    return best->ptr;
}

void * allocNHeap(sctHeap *heap, const size_t objSize, const size_t objAmount)
{
    return allocHeap(heap, objSize*objAmount);
}

#define checkMerge(block, neirbour) \
    if(neirbour && !neirbour->isBisy) \
        mergeBlocks(&block, neirbour, heap)

bool freeHeap(void *ptr, sctHeap *heap)
{
    sctHeapBlock *block = heap->blocks;
    int i = 0;
    while(i < heap->blocksAmount) {
        if(ptr == block->ptr)
            break;
        block = block--;
        i++;
    }
    if(i >= heap->blocksAmount)
        return 1;
    block->isBisy = 0;
    // merges
    checkMerge(block, block->next);
    checkMerge(block, block->prev);
    return 0;
}

void printHeap(FILE *fout, sctHeap *heap)
{
    if(!heap)
        return;
    fprintf(fout, "heap:\n");
    fprintf(fout, "ptr - %p\n", heap);
    fprintf(fout, "size = %lu\n", heap->size);
    fprintf(fout, "memory - %p\n", heap->memory);
    fprintf(fout, "blocks amount = %lu\n", heap->blocksAmount);

    fprintf(fout, "blocks:\n");
    sctHeapBlock *block = heap->blocks;
    for(size_t i=0; i < heap->blocksAmount; i++) {
        fprintf(fout, "block[%lu] (", i);
        fprintf(fout, "%p): { ", block);
        fprintf(fout, "isBisy = %d, ", block->isBisy);
        fprintf(fout, "size = %lu, ", block->size);
        fprintf(fout, "ptr = %p }\n", block->ptr);
        block--;
    }
}

void printHeapMemory(FILE *fout, sctHeap *heap)
{
    size_t n = heap->blocksAmount;
    sctHeapBlock *blocks = new sctHeapBlock[n];
    memcpy(blocks, heap->lastBlock, n*sizeof(sctHeapBlock));
    heapSort<sctHeapBlock>(blocks, n);

    fprintf(fout, "memory:\n");
    for(size_t i=0; i < heap->blocksAmount; i++) {
        sctHeapBlock *block = &blocks[i];
        fprintf(fout, "block[%lu] (", i);
        fprintf(fout, "%p): { ", block);
        fprintf(fout, "isBisy = %d, ", block->isBisy);
        fprintf(fout, "size = %lu, ", block->size);
        fprintf(fout, "ptr = %p }\n", block->ptr);
    }
    delete[] blocks;
}
#ifdef __cplusplus
}
#endif
