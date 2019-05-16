TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

DESTDIR = ../bin
OBJECTS_DIR = ../bin/.obj
MOC_DIR = ../bin/.moc

QMAKE_CXXFLAGS += -std=c++11

SOURCES += main.cpp \
    use_chess.cpp \
    chess.cpp \
    use_lists.cpp \
    lists.cpp \
    bit_knidht.cpp \
    fen_utils.cpp \
    fen_parcer.cpp

HEADERS += \
    use_chess.h \
    chess.h \
    use_lists.h \
    lists.h \
    bit_knidht.h \
    fen_utils.h \
    fen_parcer.h
