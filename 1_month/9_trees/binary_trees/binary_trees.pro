TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

DESTDIR = ../bin
OBJECTS_DIR = ../bin/.obj
MOC_DIR = ../bin/.moc

SOURCES += main.cpp \
    trees.cpp \
    test_trees.cpp \
    ../../6_heap_tree_sort/heap_tree_sort/tree_sorts.cpp

HEADERS += \
    trees.h \
    test_trees.h \
    ../../6_heap_tree_sort/heap_tree_sort/tree_sorts.h

