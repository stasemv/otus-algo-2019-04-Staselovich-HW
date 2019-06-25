TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

DESTDIR = ../bin
OBJECTS_DIR = ../bin/.obj
MOC_DIR = ../bin/.moc

SOURCES += main.cpp \
    test_hash_tables.cpp \
    hash_tables.cpp

HEADERS += \
    test_hash_tables.h \
    hash_tables.h

