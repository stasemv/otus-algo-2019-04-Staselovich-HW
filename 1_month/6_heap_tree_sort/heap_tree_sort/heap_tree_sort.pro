TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

DESTDIR = ../bin
OBJECTS_DIR = ../bin/.obj
MOC_DIR = ../bin/.moc

SOURCES += main.cpp \
    test_sorts.cpp \
    tree_sorts.cpp \
    trees.cpp

HEADERS += \
    test_sorts.h \
    tree_sorts.h \
    trees.h

