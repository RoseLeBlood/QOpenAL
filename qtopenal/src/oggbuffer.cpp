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
#include "include/oggbuffer.h"
#include <vorbis/vorbisfile.h>
#include <cstdio>
#include <iostream>
#include <vector>
#include "include/QtOpenalContext"

#define BUFFER_SIZE   32768     // 32 KB buffers



using namespace std;


void QtOpenAlOggBuffer::Load(QString fileName)
{
    vorbis_info *pInfo;
    OggVorbis_File oggFile;

    vector < char > bufferData;
    int endian = 0;             // 0 for Little-Endian, 1 for Big-Endian
    int bitStream;
    long bytes;
    char array[BUFFER_SIZE];    // Local fixed size array
    FILE *f;

    f = fopen(fileName.toStdString().c_str(), "rb");

    ov_open(f, &oggFile, NULL, 0);
    pInfo = ov_info(&oggFile, -1);

    do
    {
        // Read up to a buffer's worth of decoded sound data
        bytes = ov_read(&oggFile, array, BUFFER_SIZE, endian, 2, 1, &bitStream);
        // Append to end of buffer
        bufferData.insert(bufferData.end(), array, array + bytes);
      } while (bytes > 0);

    this->BufferData((pInfo->channels == 1 ? BufferFormat::Mono16 :
                                             BufferFormat::Stereo16),
                     &bufferData[0], bufferData.size(), pInfo->rate);
    ov_clear(&oggFile);

}
