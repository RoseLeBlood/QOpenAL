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
#include "include/openaloutputdevice.h"
#include <AL/al.h>
#include <AL/alc.h>
#include <AL/alext.h>

QtOpenalOutputDevice::QtOpenalOutputDevice(ALCdevice* device, QObject *parent)
    : QObject(parent), m_strName(""), m_pDevice(device), m_bIsOpen(false)
{
    Open();
   m_strName = getName();
}

QtOpenalOutputDevice::QtOpenalOutputDevice(QString name, QObject *parent)
    : QObject(parent), m_strName(name), m_pDevice(0), m_bIsOpen(false)
{

}
bool QtOpenalOutputDevice::Open()
{
     if(m_bIsOpen) return true;

     m_pDevice = alcOpenDevice(m_strName.toStdString().c_str());
     if(m_pDevice == 0)
     {
         OnError(alGetError());
         return false;
     }
     return m_bIsOpen = true;
}
bool QtOpenalOutputDevice::Close()
{
    if(!m_bIsOpen) return true;

    if(alcCloseDevice(m_pDevice) == ALC_TRUE)
    {
        m_bIsOpen = false;
        return true;
    }
    return false;
}
bool QtOpenalOutputDevice::IsExtensionPresent(QString extension)
{
    return alcIsExtensionPresent(m_pDevice, extension.toStdString().c_str());
}
void* QtOpenalOutputDevice::GetProcAddress(QString strproc)
{
    return alcGetProcAddress(m_pDevice, strproc.toStdString().c_str());
}
bool QtOpenalOutputDevice::IsEAXSupport()
{
    return IsExtensionPresent("ALC_EXT_EFX");
}
MaxAuxiliarySends::MaxAuxiliarySends_t QtOpenalOutputDevice::getMaxAuxiliarySends()
{
    ALCint value[] = { 0 };
    alcGetIntegerv(m_pDevice, 131075, 1, value );

    return (MaxAuxiliarySends::MaxAuxiliarySends_t)value[0];
}
QString QtOpenalOutputDevice::getName()
{
    return alcGetString(m_pDevice, ALC_DEVICE_SPECIFIER);
}

QString QtOpenalOutputDevice::getError()
{
    return alcGetString(m_pDevice, alcGetError(m_pDevice));
}


