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
#ifndef OGGBUFFER_H
#define OGGBUFFER_H

#include "openalbuffer.h"

class QtOpenalContext;

class QOPENALSHARED_EXPORT QtOpenAlOggBuffer : public QtOpenalBuffer
{
public:
    QtOpenAlOggBuffer(QString name, QtOpenalContext *con)
         : QtOpenalBuffer(name, con) {}

    virtual void Load(QString fileName);
};

#endif // OGGBUFFER_H
