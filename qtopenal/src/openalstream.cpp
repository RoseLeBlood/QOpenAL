#include "include/openalstream.h"
#include "include/QtOpenalContext"
#include <al/al.h>

QtOpenalStream::QtOpenalStream(QString name, QtOpenalContext *context,  QObject* p,
               int iNnumBuffer, int iBufferSizre)
                : QObject(p), m_pContext(context), m_iBufferSize(iBufferSizre)
{
    for(int i= 0; i < iNnumBuffer; i++)
        m_pBuffers.push_back(new QtOpenalBuffer(name + "_Buffer_" + QString::number(i), m_pContext));

    m_pSource = new QtOpenalSource(name + "_source", m_pContext);

    if(int err = alGetError() != AL_NO_ERROR)
    {
        throw QString("OpenAL:  Error generating :: " +  QString(alGetString(err)));
    }

    m_pBuffer = (char*)malloc(m_iBufferSize);
}
/*QtOpenalStream::~QtOpenalStream()
{
    clear();
    free(m_pBuffer);
    delete m_pSource;
}*/

bool QtOpenalStream::Play()
{
    for(int i=0; i < m_pBuffers.size(); i++)
        if(!stream(m_pBuffers[i]))
            return false;

    m_pSource->SourceQueueBuffers(m_pBuffers);
    m_pSource->Play();
}
bool QtOpenalStream::IsPlaying()
{
    return m_pSource->getState() == SourceState::Playing;
}

void QtOpenalStream::Release()
{
    if(IsPlaying()) {
        m_pSource->Stop();
    }
    m_pSource->SourceUnqueueBuffers(m_pBuffers);
}
bool QtOpenalStream::Update()
{
    int processed;
    bool active = true;

    alGetSourcei(m_pSource->handle(), AL_BUFFERS_PROCESSED, &processed);
    while(processed--)
    {
        ALuint buffer;
        m_pSource->SourceUnqueueBuffers(1, &buffer);
        active = stream(find(buffer));
        alSourceQueueBuffers(m_pSource->handle(), 1, &buffer);
    }

    return active;
}

QtOpenalBuffer* QtOpenalStream::find(int id)
{
    for(int i=0; i < m_pBuffers.size(); i++)
    {
        if(m_pBuffers[i]->handle() == id)
            return m_pBuffers[i];
    }
    return 0;
}
