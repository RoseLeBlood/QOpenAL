
#include <QCoreApplication>
#include <openaloutputdevices.h>
#include <openalcontext.h>
#include <iostream>
//#include "oggbuffer.h"
#include "openalsource.h"

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <QtOpenalOggStream>
#include <QThread>


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QList<QtOpenalOutputDevice*> devlist = QtOpenalOutputDevices::Instance().getDevices();

    QtOpenalContext *context = new QtOpenalContext(devlist[0]);
    context->Create(48000, OpenalContextFormat::s16Bit,
                    OpenalContextChannel::Stereo);

    QtOpenalOggStream *ogg = new QtOpenalOggStream("ogg_test", context, 0, 3);
        ogg->LoadFile(argv[1]);

        ogg->Play();

        //std::cout << "\rPlay Title " << argv[i] << " " << i << "/" << argc - 1;
        while(ogg->Update())
        {
            QThread::msleep(250/3);
        }

        ogg->Release();

    return a.exec();
}
