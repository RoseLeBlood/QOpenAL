QT += core
QT -= gui

CONFIG += c++11

TARGET = test
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp

DESTDIR = ../lib

LIBS += -L$$OUT_PWD/../lib -lQtOpenAl

INCLUDEPATH += $$PWD/../qtopenal/include/
DEPENDPATH += $$PWD/../qtopenal/

