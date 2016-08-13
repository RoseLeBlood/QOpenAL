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
#include "include/openaloggstream.h"

#include "include/QtOpenalContext"
#include <al/al.h>
#include "QDebug"
#include <ogg/ogg.h>
#include <vorbis/codec.h>
#include <vorbis/vorbisenc.h>
#include <vorbis/vorbisfile.h>

struct ogg_internal
{
    OggVorbis_File  m_oggStream;
    vorbis_info*    m_pVorbisInfo;
    vorbis_comment* m_pVorbisComment;
    FILE*           m_pFile;
};

QtOpenalOggStream::QtOpenalOggStream(QString name,
                                     QtOpenalContext *context,
                                     QObject *p, int iNnumBuffer)
    : QtOpenalStream(name, context, p, iNnumBuffer)
{
    m_pI = new ogg_internal();
}
bool QtOpenalOggStream::LoadFile(QString strFile)
{
    if(!(m_pI->m_pFile = fopen(strFile.toStdString().c_str(), "rb")))
    {
        qCritical() << "Could not open Ogg file.";
        return false;
    }
    if(int result = ov_open(m_pI->m_pFile, &m_pI->m_oggStream, NULL, 0))
    {
        fclose(m_pI->m_pFile);
        qCritical() << "Could not open Ogg stream.";
        return false;
    }
    m_pI->m_pVorbisInfo = ov_info(&m_pI->m_oggStream, -1);
    m_pI->m_pVorbisComment = ov_comment(&m_pI->m_oggStream, -1);


    m_uiFormat = (m_pI->m_pVorbisInfo->channels == 1 ? AL_FORMAT_MONO16 : AL_FORMAT_STEREO16);
    m_uiFrequency = m_pI->m_pVorbisInfo->rate;
    m_uiChannels = m_pI->m_pVorbisInfo->channels;

    setFormat(m_uiChannels, 16, false);

    return QtOpenalStream::LoadFile(strFile);
}

void QtOpenalOggStream::Release()
{
    if(m_pI->m_pFile)
    {
        QtOpenalStream::Release();
        ov_clear(&m_pI->m_oggStream);
        fclose(m_pI->m_pFile);
    }
}
bool QtOpenalOggStream::stream(QtOpenalBuffer* buffer, int _size)
{
    Q_UNUSED(_size);

    int  size = 0;
    int  section;
    int  result;

    while(size < m_iBufferSize)
    {
        result = ov_read(&m_pI->m_oggStream, m_pBuffer + size, m_iBufferSize - size, 0, 2, 1, &section);
        if(result > 0)
            size += result;
        else if(result < 0)
            throw QString::number(result);
        else
            break;

    }
    if(size == 0)
        return false;

    return QtOpenalStream::stream(buffer, size);
}

