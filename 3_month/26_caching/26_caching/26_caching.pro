TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH += ../../../1_month/2_dynamic_arrays/dynamicArray

SOURCES += main.cpp \
    test_cache.cpp \
    cache.cpp

HEADERS += \
    test_cache.h \
    cache.h \
    ../../../1_month/9_trees/binary_trees/avl_tree.h

