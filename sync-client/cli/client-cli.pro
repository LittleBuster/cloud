TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle qt

LIBS += -lboost_system -lboost_filesystem -lcrypto -lpthread

SOURCES += *.cpp ../*.cpp

HEADERS += *.h ../*.h
