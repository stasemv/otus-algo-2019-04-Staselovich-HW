TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH += ../../../1_month/2_dynamic_arrays/dynamicArray

SOURCES += main.cpp \
    test_matching.cpp \
    string_matching.cpp

HEADERS += \
    test_matching.h \
    string_matching.h

