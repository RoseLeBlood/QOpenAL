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
    src/oggbuffer.cpp

HEADERS +=\
        include/qopenal_global.h \
    include/openaloutputdevice.h \
    include/openalcontext.h \
    include/openaloutputdevices.h \
    include/openalsource.h \
    include/openalbuffer.h \
    include/QtOpenalContext \
    include/QtOpenalBuffer \
    include/oggbuffer.h \
    include/QtOpenAlOggBuffer \
    include/QtOpenalOutputDevice \
    include/QtOpenalOutputDevices \
    include/QtOpenalSource \
    include/QtOpenAl

unix {
    target.path = /usr/lib
    INSTALLS += target
}


unix: LIBS += -llibOpenAL32

INCLUDEPATH += $$PWD/win32/include
DEPENDPATH += $$PWD/win32/include

win32: LIBS += -L$$PWD/win32/libogg-1.3.2/ -llibogg.dll

INCLUDEPATH += $$PWD/win32/libogg-1.3.2/include
DEPENDPATH += $$PWD/win32/libogg-1.3.2/include


win32: LIBS += -L$$PWD/win32/libvorbis-1.3.5/ -llibvorbis.dll -llibvorbisfile.dll

INCLUDEPATH += $$PWD/win32/libvorbis-1.3.5/include
DEPENDPATH += $$PWD/win32/libvorbis-1.3.5/include


win32: LIBS += -L$$PWD/win32/openalsoft/ -llibOpenAL32.dll

INCLUDEPATH += $$PWD/win32/openalsoft/
DEPENDPATH += $$PWD/win32/openalsoft/
