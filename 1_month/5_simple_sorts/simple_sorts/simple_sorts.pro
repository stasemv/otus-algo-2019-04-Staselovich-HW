TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

DESTDIR = ../bin
OBJECTS_DIR = ../bin/.obj
MOC_DIR = ../bin/.moc

SOURCES += main.cpp \
    test_sorts.cpp \
    sorts.cpp

HEADERS += \
    test_sorts.h \
    sorts.h

