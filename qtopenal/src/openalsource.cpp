/*"""
    This file is part of QtOpenAl (unoficiale libary)
    Copyright (C) 2013  Anna-Sophia Schröck <annasophia.schroeck@outlook.de>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
"""
*/

#include "include/openalsource.h"
#include "include/openalbuffer.h"

#include <AL/al.h>
#include <AL/alc.h>
#include "include/openalsoft.h"


QtOpenalSource::QtOpenalSource()
    : m_pContext(0)
{

}

QtOpenalSource::QtOpenalSource(QString name, QtOpenalContext *context)
    : m_pContext(context), m_strName(name)
{
    alGenSources(1, &m_iId);

    setGain(1.0f);
    setPitch(1.0f);
    setPosition(glm::vec3(0, 0, 0));
    setVelocity(glm::vec3(0, 0, 0));
    setLooping(false);
}
QtOpenalSource::QtOpenalSource(QtOpenalSource& other)
   : m_pContext(other.m_pContext), m_strName(other.m_strName), m_iId(other.handle())
{

}

QtOpenalSource::~QtOpenalSource()
{
    alDeleteSources(1, &m_iId);
}

void QtOpenalSource::setPosition(glm::vec3 position)
{
   // m_vecPosition = position;
    alSource3f(m_iId, AL_POSITION, position.x, position.y, position.z);
}
void QtOpenalSource::setDirection(glm::vec3 direction)
{
    alSource3f(m_iId, AL_DIRECTION, direction.x, direction.y, direction.z);
}

void QtOpenalSource::setVelocity(glm::vec3 velocity)
{
    //m_vecVelocity = velocity;
    alSource3f(m_iId, AL_VELOCITY, velocity.x, velocity.y, velocity.z);
}
void QtOpenalSource::setGain(float gain)
{
    //m_fGain = gain;
    alSourcef(m_iId, AL_GAIN, gain);
}
void QtOpenalSource::setPitch(float pitch)
{
   // m_fPitch = pitch;
    alSourcef(m_iId, AL_PITCH, pitch);
}
void QtOpenalSource::setLooping(bool looping)
{
  //   m_bLooping = looping;
    alSourcei(m_iId, AL_LOOPING, (looping ? AL_TRUE : AL_FALSE));
}
void QtOpenalSource::Bind(QtOpenalBuffer* buffer)
{
    alSourcei(m_iId, AL_BUFFER, buffer->handle());
}
void QtOpenalSource::QueueBuffers(QVector<QtOpenalBuffer*> buffers)
{
    unsigned int *_buffers = new unsigned int[buffers.size()];
    for(int i= 0; i < buffers.size(); i++)
        _buffers[i] = buffers[i]->handle();

    alSourceQueueBuffers(m_iId, buffers.size(), _buffers);
}
void QtOpenalSource::QueueBuffers(unsigned int size, const unsigned int *ids)
{
    alSourceQueueBuffers(m_iId, size, ids);
}

void QtOpenalSource::UnqueueBuffers(QVector<QtOpenalBuffer*> buffers)
{
    unsigned int *_buffers = new unsigned int[buffers.size()];
    for(int i= 0; i < buffers.size(); i++)
        _buffers[i] = buffers[i]->handle();

    alSourceUnqueueBuffers(m_iId, buffers.size(), _buffers);
}
void QtOpenalSource::UnqueueBuffers(unsigned int size, unsigned int *id)
{
    alSourceUnqueueBuffers(m_iId, size, id);
}

void QtOpenalSource::Play()
{
    alSourcePlay(m_iId);
}
void QtOpenalSource::Stop()
{
    alSourceStop(m_iId);
}
void QtOpenalSource::Pause()
{
    alSourcePause(m_iId);
}
void QtOpenalSource::Rewind()
{
    alSourceRewind(m_iId);
}
SourceState::SourceState_t QtOpenalSource::getState()
{
    int state = 0;
    alGetSourcei(m_iId, AL_SOURCE_STATE, &state);

    return (SourceState::SourceState_t)state;
}
void QtOpenalSource::setMaxDistance(float maxDist)
{
    alSourcef(m_iId, AL_MAX_DISTANCE, maxDist);
}
void QtOpenalSource::setRollOffFactor(float rollOff)
{
    alSourcef(m_iId, AL_ROLLOFF_FACTOR, rollOff);
}
void QtOpenalSource::setReferenceDistance(float refDis)
{
    alSourcef(m_iId, AL_REFERENCE_DISTANCE, refDis);
}
void QtOpenalSource::setMinGain(float mGain)
{
    alSourcef(m_iId, AL_MIN_GAIN, mGain);
}
void QtOpenalSource::setMaxGain(float mGain)
{
    alSourcef(m_iId, AL_MAX_GAIN, mGain);
}
void QtOpenalSource::setConeOuterGain(float cone)
{
    alSourcef(m_iId, AL_CONE_OUTER_GAIN, cone);
}
void QtOpenalSource::setConeInnerAngle(int angle)
{
    alSourcei(m_iId, AL_CONE_INNER_ANGLE, angle);
}

void QtOpenalSource::setConeOuterAngle(int angle)
{
    alSourcei(m_iId, AL_CONE_OUTER_ANGLE, angle);
}


glm::vec3 QtOpenalSource::getPosition()
{
    float f1, f2, f3;
    alGetSource3f(m_iId, AL_POSITION, &f1, &f2, &f3);
    return glm::vec3(f1,f2,f3);
}
glm::vec3 QtOpenalSource::getVelocity()
{
    float f1, f2, f3;
    alGetSource3f(m_iId, AL_VELOCITY, &f1, &f2, &f3);
    return glm::vec3(f1,f2,f3);

}
glm::vec3 QtOpenalSource::getDirection()
{

    float f1, f2, f3;
    alGetSource3f(m_iId, AL_DIRECTION, &f1, &f2, &f3);
    return glm::vec3(f1,f2,f3);
}
float QtOpenalSource::getGain()
{
    float f = 0;
    alGetSourcef(m_iId, AL_GAIN, &f );
    return f;
}
float QtOpenalSource::getPitch()
{
    float f = 0;
    alGetSourcef(m_iId, AL_PITCH, &f );
    return f;
}
bool QtOpenalSource::getLooping()
{
    int f = 0;
    alGetSourcei(m_iId, AL_LOOPING, &f );
    return f == AL_TRUE;
}
float QtOpenalSource::getMaxDistance()
{
    float f = 0;
    alGetSourcef(m_iId, AL_MAX_DISTANCE, &f );
    return f;
}
float QtOpenalSource::getRollOffFactor()
{
    float f = 0;
    alGetSourcef(m_iId, AL_ROLLOFF_FACTOR, &f );
    return f;
}
float QtOpenalSource::getReferenceDistance()
{
    float f = 0;
    alGetSourcef(m_iId, AL_REFERENCE_DISTANCE, &f );
    return f;
}
float QtOpenalSource::getMinGain()
{
    float f = 0;
    alGetSourcef(m_iId, AL_MIN_GAIN, &f );
    return f;
}
float QtOpenalSource::getMaxGain()
{
    float f = 0;
    alGetSourcef(m_iId, AL_MAX_DISTANCE, &f );
    return f;
}
float QtOpenalSource::getConeOuterGain()
{
    float f = 0;
    alGetSourcef(m_iId, AL_CONE_OUTER_GAIN, &f );
    return f;
}
int QtOpenalSource::getConeInnerAngle()
{
    int f = 0;
    alGetSourcei(m_iId, AL_CONE_INNER_ANGLE, &f );
    return f;
}
int QtOpenalSource::getConeOuterAngle()
{
    int f = 0;
    alGetSourcei(m_iId, AL_CONE_OUTER_ANGLE, &f );
    return f;

}
double QtOpenalSource::getLatency()
{
    double offset[2];
     alGetSourcedvSOFT(m_iId, AL_SEC_OFFSET_LATENCY_SOFT, offset);
     return offset[0];
}

double QtOpenalSource::getOffsetLastRead()
{
 return 0;
}
