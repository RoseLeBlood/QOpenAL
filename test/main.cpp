
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

int main(int argc, char *argv[])
{
    /*if(argc < 2)
    {
        fprintf(stderr, "Usage: %s <audiofile>\n", argv[0]);
        return 0;
    }*/

    QCoreApplication a(argc, argv);
    QList<QtOpenalOutputDevice*> devlist = QtOpenalOutputDevices::Instance().getDevices();

    QtOpenalContext *context = new QtOpenalContext(devlist[0]);
    context->Create(48000, 0, true, true);

    QtOpenalOggStream *ogg = new QtOpenalOggStream("ogg_test", context, 0, 3);

    for(int i=1; i < argc; i++  ) {

        ogg->LoadFile(argv[i]);
        ogg->Play();
        std::cout << "\rPlay Title " << i << "/" << argc - 1;
        while(ogg->Update())
        {

        }
        ogg->Release();
    }
    std::cout << "Fertig";
    return a.exec();
}
