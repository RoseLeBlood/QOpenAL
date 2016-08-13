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
#include "include/openalbuffer.h"
#include <AL/al.h>
#include <AL/alc.h>
#define AL_ALEXT_PROTOTYPES
#include <AL/alext.h>

QtOpenalBuffer::QtOpenalBuffer(QString name,  unsigned int bufferSize, QtOpenalContext* context )
    : m_pContext(context), m_strName(name)
{
    alGenBuffers((ALuint)1, &m_iId);
    //m_pBuffer = malloc(bufferSize);
    if(alIsExtensionPresent("AL_SOFT_buffer_samples"))
    {

    }

}
QtOpenalBuffer::QtOpenalBuffer(unsigned int id, QtOpenalContext* context)
 : m_pContext(context), m_iId(id)
{

}

void QtOpenalBuffer::Delete()
{
    alDeleteBuffers(1, &m_iId);
    //free(m_pBuffer);
}
void QtOpenalBuffer::BufferData(BufferFormat::BufferFormat_t format,
                                const void *data, size_t size,
                                size_t freq)
{
    alBufferData(m_iId, (int)format, data, size, freq);
}
int QtOpenalBuffer::getBits()
{
    int bits = 0;
    alGetBufferi(m_iId, AL_BITS, &bits);
    return bits;
}
int QtOpenalBuffer::getChannels()
{
    int c = 0;
    alGetBufferi(m_iId, AL_CHANNELS, &c);
    return c;
}
int QtOpenalBuffer::getFrequenz()
{
    int f = 0;
    alGetBufferi(m_iId, AL_FREQUENCY, &f);
    return f;
}
int QtOpenalBuffer::getSize()
{
    int s = 0;
    alGetBufferi(m_iId, AL_SIZE, &s);
    return s;
}
bool QtOpenalBuffer::IsBuffer(const QtOpenalBuffer& buffer)
{
    return alIsBuffer(buffer.m_iId);
}
