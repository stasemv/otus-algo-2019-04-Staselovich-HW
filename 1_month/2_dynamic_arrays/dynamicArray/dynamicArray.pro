TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXXFLAGS += -std=c++11

SOURCES += main.cpp \
    dynamic_arrays.cpp \
    use_arrays.cpp

HEADERS += \
    use_arrays.h \
    dynamic_arrays.h

