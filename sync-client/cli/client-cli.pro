TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle qt

LIBS += -lboost_system -lboost_filesystem -lboost_thread -lcrypto -lpthread

SOURCES += *.cpp ../*.cpp

HEADERS += *.h ../*.h
