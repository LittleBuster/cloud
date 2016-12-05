TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

LIBS +=-lpthread -lcrypto

HEADERS += *.h

SOURCES += *.cpp
