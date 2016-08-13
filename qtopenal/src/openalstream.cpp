#include "include/openalstream.h"
#include "include/QtOpenalContext"
#include <al/al.h>
#include <AL/alext.h>

//static LPALBUFFERSAMPLESSOFT alBufferSamplesSOFT ;
//static LPALISBUFFERFORMATSUPPORTEDSOFT alIsBufferFormatSupportedSOFT;

QtOpenalStream::QtOpenalStream(QString name, QtOpenalContext *context,  QObject* p,
               int iNnumBuffer)
                : QObject(p), m_pContext(context), m_iBufferSize(0)
{
    for(int i= 0; i < iNnumBuffer; i++)
        m_pBuffers.push_back(new QtOpenalBuffer(name + "_Buffer_" + QString::number(i),
                                                m_iBufferSize, m_pContext));

    m_pSource = new QtOpenalSource(name + "_source", m_pContext);

    if(int err = alGetError() != AL_NO_ERROR)
    {
        throw QString("OpenAL:  Error generating :: " +  QString(alGetString(err)));
    }

}
bool QtOpenalStream::LoadFile(QString)
{
    m_iBufferSize = (m_uiFrequency * m_uiChannels * 2)>>2;
    m_iBufferSize -= (m_iBufferSize % (m_uiChannels*2));


    m_pBuffer = (char*)malloc(m_iBufferSize);

    return true;
}

QtOpenalStream::~QtOpenalStream()
{
    free(m_pBuffer);
}

bool QtOpenalStream::Play()
{
    for(int i=0; i < m_pBuffers.size(); i++)
        if(!stream(m_pBuffers[i]))
            return false;

    m_pSource->QueueBuffers(m_pBuffers);
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
    m_pSource->UnqueueBuffers(m_pBuffers);
}
bool QtOpenalStream::Update()
{
    int processed;
    bool active = true;

    if(!m_pContext->IsCurrent())
        m_pContext->MakeCurrent();

    alGetSourcei(m_pSource->handle(), AL_BUFFERS_PROCESSED, &processed);
    while(processed--)
    {
        ALuint buffer;
        m_pSource->UnqueueBuffers(1, &buffer);
        active = stream(find(buffer));
        m_pSource->QueueBuffers(1, &buffer);
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
bool QtOpenalStream::stream(QtOpenalBuffer* buffer, int size)
{

     buffer->BufferData((BufferFormat::BufferFormat_t)m_uiFormat, m_pBuffer, size, m_uiFrequency);


     return true;
}
void QtOpenalStream::setFormat(unsigned short channels, unsigned short bits, bool rear)
{
    unsigned short hash = (channels<<8)|bits;

      switch(hash)

      {

      case ((1<<8)|8): m_uiFormat = AL_FORMAT_MONO8;break;

      case ((1<<8)|16):  m_uiFormat = AL_FORMAT_MONO16;break;

      case ((1<<8)|32):  m_uiFormat = AL_FORMAT_MONO_FLOAT32;break;

      case ((1<<8)|64):  m_uiFormat = AL_FORMAT_MONO_DOUBLE_EXT;break;

      case ((2<<8)|8):  m_uiFormat = rear?AL_FORMAT_REAR8:AL_FORMAT_STEREO8;break;

      case ((2<<8)|16):  m_uiFormat = rear?AL_FORMAT_REAR16:AL_FORMAT_STEREO16;break;

      case ((2<<8)|32):  m_uiFormat = rear?AL_FORMAT_REAR32:AL_FORMAT_STEREO_FLOAT32;break;

      case ((2<<8)|64):  m_uiFormat = AL_FORMAT_STEREO_DOUBLE_EXT;break;

      case ((4<<8)|8):  m_uiFormat = AL_FORMAT_QUAD8;break;

      case ((4<<8)|16):  m_uiFormat = AL_FORMAT_QUAD16;break;

      case ((4<<8)|32):  m_uiFormat = AL_FORMAT_QUAD32;break;

      case ((6<<8)|8):  m_uiFormat = AL_FORMAT_51CHN8;break;

      case ((6<<8)|16):  m_uiFormat = AL_FORMAT_51CHN16;break;

      case ((6<<8)|32):  m_uiFormat = AL_FORMAT_51CHN32;break;

      case ((7<<8)|8):  m_uiFormat = AL_FORMAT_61CHN8;break;

      case ((7<<8)|16):  m_uiFormat = AL_FORMAT_61CHN16;break;

      case ((7<<8)|32):  m_uiFormat = AL_FORMAT_61CHN32;break;

      case ((8<<8)|8):  m_uiFormat = AL_FORMAT_71CHN8;break;

      case ((8<<8)|16):  m_uiFormat = AL_FORMAT_71CHN16;break;

      case ((8<<8)|32):  m_uiFormat = AL_FORMAT_71CHN32;break;

      }

      return;
}
