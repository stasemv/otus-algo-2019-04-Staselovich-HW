TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

DESTDIR = ../bin
OBJECTS_DIR = ../bin/.obj
MOC_DIR = ../bin/.moc

SOURCES += main.cpp \
    use_algs.cpp \
    algebric_algs.cpp

HEADERS += \
    use_algs.h \
    algebric_algs.h

