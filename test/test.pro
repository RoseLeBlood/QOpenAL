QT += core
QT -= gui

CONFIG += c++11

TARGET = test
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp

DESTDIR = ../lib

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../qtopenal/release/ -lQtOpenAl
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../qtopenal/debug/ -lQtOpenAl
else:unix: LIBS += -L$$OUT_PWD/../qtopenal/ -lQtOpenAl

INCLUDEPATH += $$PWD/../qtopenal/include/
DEPENDPATH += $$PWD/../qtopenal/

