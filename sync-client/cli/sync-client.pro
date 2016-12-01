TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

LIBS += -lboost_system -lboost_filesystem -lpthread -lcrypto

HEADERS += app.h  ../*.h

SOURCES += *.cpp ../*.cpp
