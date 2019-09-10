TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH += ../../../1_month/2_dynamic_arrays/dynamicArray

DEFINES += _PRINT_GRAPHS_INFO_

SOURCES += main.cpp \
    test_graphs.cpp \
    graphs.cpp

HEADERS += \
    test_graphs.h \
    graphs.h \
    ../../../1_month/2_dynamic_arrays/dynamicArray/dynamic_arrays.h \
    ../../../1_month/2_dynamic_arrays/dynamicArray/lists.h

