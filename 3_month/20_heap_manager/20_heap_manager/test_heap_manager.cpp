#include "test_heap_manager.h"

#include "stdlib.h"

#include "heap_manager.h"

#define allocDebugStr(str, length) \
    char *str = (char*)allocHeap(heap, length);    \
    printf("\nalloc %s (lenght = %lu)\n", #str, length);   \
    printHeap(stdout, heap)

void test_heap_manager()
{
    size_t buf_size = 100000;
    char *buf = new char[buf_size];

    sctHeap *heap = createHeapManager(buf, buf_size);
    printHeap(stdout, heap);

    char *str1 = (char*)allocHeap(heap, 125);
    char *str2 = (char*)allocHeap(heap, 5);
    char *str3 = (char*)allocHeap(heap, 1251);
    char *str4 = (char*)allocHeap(heap, 512);
    char *str5 = (char*)allocHeap(heap, 64);
    char *str6 = (char*)allocHeap(heap, 12542);
    printHeap(stdout, heap);

    bool del_heap = 0;
//    del_heap |= freeHeap(str4, heap);
    del_heap |= freeHeap(str2, heap);
    del_heap |= freeHeap(str3, heap);
    del_heap |= freeHeap(str5, heap);
    if(del_heap)
        printf("Heap manager deleting error\n");
    else
        printHeap(stdout, heap);

    allocDebugStr(str7, 64);
    allocDebugStr(str8, 24164);
    allocDebugStr(str9, 964);

    del_heap |= freeHeap(str6, heap);
    allocDebugStr(str10, 9364);

    printHeapMemory(stdout, heap);

    delete[] buf;
}
