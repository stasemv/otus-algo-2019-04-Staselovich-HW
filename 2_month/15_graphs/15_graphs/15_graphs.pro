TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH += ../../../1_month/2_dynamic_arrays/dynamicArray

DEFINES += _PRINT_GRAPHS_INFO_

SOURCES += main.cpp \
    test_graphs.cpp \
    graphs.cpp \
    shortest_path.cpp \
    ../../../1_month/6_heap_tree_sort/heap_tree_sort/tree_sorts.cpp

HEADERS += \
    test_graphs.h \
    graphs.h \
    ../../../1_month/2_dynamic_arrays/dynamicArray/dynamic_arrays.h \
    ../../../1_month/2_dynamic_arrays/dynamicArray/lists.h \
    shortest_path.h \
    graphs_data.h \
    ../../../1_month/6_heap_tree_sort/heap_tree_sort/test_sorts.h

