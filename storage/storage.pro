TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle qt

LIBS += -lsqlite3 -lpthread

SOURCES += *.cpp \
    filesbase.cpp \
    usersbase.cpp

HEADERS += *.h \
    filesbase.h \
    usersbase.h
