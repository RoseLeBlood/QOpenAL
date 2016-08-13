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
#include "include/openalcontext.h"
#include <QVector>
#include <AL/al.h>
#include <AL/alc.h>
#include "include/openalsoft.h"

QtOpenalContext::QtOpenalContext(ALCcontext *context, QObject *parent) : QObject(parent), m_pContext(context)
{
    m_pDevice = new QtOpenalOutputDevice(alcGetContextsDevice(context));
}

QtOpenalContext::QtOpenalContext(QtOpenalOutputDevice *pDevice, QObject *parent)
    : QObject(parent), m_pDevice(pDevice)
{

}
bool QtOpenalContext::Create(int freq, OpenalContextFormat::OpenalContextFormat_t format,
                             OpenalContextChannel::OpenalContextChannel_t channels,
                             MaxAuxiliarySends::MaxAuxiliarySends_t efxAuxiliarySends)
{
    if(!m_pDevice->IsOpen())
        m_pDevice->Open();


    QVector<ALCint> attribute;
    attribute.push_back(ALC_FREQUENCY);
    attribute.push_back(freq);

    attribute.push_back(ALC_FORMAT_CHANNELS_SOFT);
    attribute.push_back((int)channels);


    attribute.push_back(ALC_FORMAT_TYPE_SOFT);
    attribute.push_back((int)format);


    if(m_pDevice->IsEAXSupport())
    {
        int num_slots;

        if(efxAuxiliarySends == MaxAuxiliarySends::Default)
            num_slots = m_pDevice->getMaxAuxiliarySends();
        else
            num_slots = (int)efxAuxiliarySends;


        attribute.push_back(131075);
        attribute.push_back(num_slots);

        qInfo() << "[OpenAL] EAX Support";
        if (alIsExtensionPresent("EAX-RAM") == AL_TRUE)
        {
              qInfo() << "[OpenAL] EAX-RAM Support";
        }
    }

     m_pContext = alcCreateContext(m_pDevice->handle(), attribute.constData());
     alCreateHelpers();
    if(m_pContext == 0)
    {
        qDebug() << "[OpenAL] Error by alcCreateContext";
        return false;
    }

    MakeCurrent();



    setPosition(glm::vec3(0.0f, 0.0f, 1.0f));
    setVelocity(glm::vec3(0.0f,0.0f,0.0f));
    setOrientation(glm::vec3(0.0f,0.0f,-1.0f));


    return true;
}
void QtOpenalContext::Release()
{
    alcMakeContextCurrent(0);
}

bool QtOpenalContext::Destroy()
{
    if(IsCurrent())
        Release();
    alcDestroyContext(m_pContext);
    return true;
}

bool QtOpenalContext::IsCurrent()
{
    return alcGetCurrentContext() == m_pContext;
}

void QtOpenalContext::MakeCurrent()
{
    alcMakeContextCurrent(m_pContext) ;
}

void QtOpenalContext::ProcessContext()
{
    alcProcessContext(m_pContext);
}

void QtOpenalContext::Suspend()
{
    alcSuspendContext(m_pContext);

}
void QtOpenalContext::setPosition(glm::vec3 position)
{
    m_vecPosition = position;
    alListener3f(AL_POSITION, position.x, position.y, position.z);
}

void QtOpenalContext::setVelocity(glm::vec3 velocity)
{
    m_vecVelocity = velocity;
    alListener3f(AL_VELOCITY, velocity.x, velocity.y, velocity.z);
}
void QtOpenalContext::setOrientation(glm::vec3 at, glm::vec3 up)
{
    ALfloat listenerOri[] = { at.x, at.y, at.z, up.x, up.y, up.z };
    m_vecAt = at;
    m_vecUp = up;
    alListenerfv(AL_ORIENTATION, listenerOri);
}

ALCcontext *QtOpenalContext::handle()
{
    return m_pContext;
}

QtOpenalContext *QtOpenalContext::getCurrentContext()
{
    return new QtOpenalContext(alcGetCurrentContext());
}
