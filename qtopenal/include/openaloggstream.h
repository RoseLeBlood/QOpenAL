#ifndef QTOPENALOGGFILE_H
#define QTOPENALOGGFILE_H

#include "openalstream.h"

struct ogg_internal;

class QOPENALSHARED_EXPORT QtOpenalOggStream : public QtOpenalStream
{
    Q_OBJECT
public:
    QtOpenalOggStream(QString name, QtOpenalContext *context,  QObject* p = 0,
                      int iNnumBuffer = 3, int iBufferSizre = 32768);

    bool LoadFile(QString strFile);
    void Release();

    QString getInformation(StreamInfo::StreamInfo_t) { return QString("NOT INCLUDED"); }
protected:
    virtual bool stream(QtOpenalBuffer* buffer);
private:
    ogg_internal    *m_pI;
};

#endif // QTOPENALOGGFILE_H
