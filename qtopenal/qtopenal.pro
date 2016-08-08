#-------------------------------------------------
#
# Project created by QtCreator 2016-08-02T11:29:16
#
#-------------------------------------------------

QT       -= gui

TARGET = QtOpenAl
TEMPLATE = lib

DEFINES += QOPENAL_LIBRARY

SOURCES += \
    src/openaloutputdevice.cpp \
    src/openalcontext.cpp \
    src/openaloutputdevices.cpp \
    src/openalsource.cpp \
    src/openalbuffer.cpp \
    src/openaloggstream.cpp \
    src/openalstream.cpp

HEADERS +=\
        include/qopenal_global.h \
    include/openaloutputdevice.h \
    include/openalcontext.h \
    include/openaloutputdevices.h \
    include/openalsource.h \
    include/openalbuffer.h \
    include/QtOpenalContext \
    include/QtOpenalBuffer \
    include/QtOpenalOutputDevice \
    include/QtOpenalOutputDevices \
    include/QtOpenalSource \
    include/QtOpenAl \
    include/openaloggstream.h \
    include/QtOpenalOggStream \
    include/openalstream.h \
    include/QtOpenalStream

unix {
    target.path = /usr/lib
    INSTALLS += target
}

DESTDIR = ../lib


unix: LIBS += -llibOpenAL32

win32: LIBS += -L$$PWD/win32/lib/ -llibogg.dll  -llibvorbis.dll -llibvorbisfile.dll  -llibOpenAL32.dll
win32: INCLUDEPATH += $$PWD/win32/include
win32: DEPENDPATH += $$PWD/win32/bin



