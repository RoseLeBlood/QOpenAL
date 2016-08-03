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
#include "include/openaloutputdevices.h"
#include <AL/al.h>
#include <AL/alc.h>


QtOpenalOutputDevices* QtOpenalOutputDevices::m_pInstance = 0;

QList<QtOpenalOutputDevice*> QtOpenalOutputDevices::getDevices()
{
    ALboolean enumeration;
    QList<QtOpenalOutputDevice*> dev;

    dev.push_back(new QtOpenalOutputDevice(""));

    enumeration = alcIsExtensionPresent(NULL, "ALC_ENUMERATION_EXT");
    if (enumeration == AL_TRUE)
    {
        const ALCchar *devices = alcGetString(NULL, ALC_DEVICE_SPECIFIER);
        const ALCchar *device = devices, *next = devices + 1;
        size_t len = 0;

        while (device && *device != '\0' && next && *next != '\0')
        {
            QtOpenalOutputDevice* _dev = new QtOpenalOutputDevice(device);
            if(enumDevices(_dev) == true)
            {
                dev.push_back(_dev);
            }
            else
                delete[] _dev;

            len = strlen(device);
            device += (len + 1);
            next += (len + 2);
        }
    }

    return dev;
}
bool QtOpenalOutputDevices::enumDevices(QtOpenalOutputDevice* device)
{
    Q_UNUSED(device)
    return true;
}
