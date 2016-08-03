
#include <QCoreApplication>
#include <openaloutputdevices.h>
#include <openalcontext.h>
#include <iostream>
#include "oggbuffer.h"
#include "openalsource.h"

int main(int argc, char *argv[])
{


    QCoreApplication a(argc, argv);
    QList<QtOpenalOutputDevice*> devlist = QtOpenalOutputDevices::Instance().getDevices();

    QtOpenalContext *context = new QtOpenalContext(devlist[0]);
    context->Create(48000, 0, false, false);

    QtOpenalBuffer *buffer = new QtOpenAlOggBuffer("Ogg_Buffer", context);
    QtOpenalSource* source = new QtOpenalSource("ogg_Source", context);

    buffer->Load(argv[1]);
   source->Bind(buffer);
   source->Play();
    do
    {

    }while(source->getState() == SourceState::Playing);


    return a.exec();
}
