TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH += ../../../1_month/2_dynamic_arrays/dynamicArray

SOURCES += main.cpp \
    test_heap_manager.cpp \
    heap_manager.cpp

HEADERS += \
    test_heap_manager.h \
    heap_manager.h

