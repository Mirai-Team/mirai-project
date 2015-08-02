////////////////////////////////////////////////////////////
//
// MiraiProject
// Copyright (C) 2014-2015 CORTIER Benoît (benoit.cortier@gmail.com), BOULMIER Jérôme (jerome.boulmier@outlook.fr)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
// you must not claim that you wrote the original software.
// If you use this software in a product, an acknowledgment
// in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
// and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
////////////////////////////////////////////////////////////

#include "MiraiProject/util/MPLogger.hpp"

void mp::changeMPLoggerOutput(std::streambuf* buf)
{
    priv::MPLogger::instance()->changeOutput(buf);
}

void mp::enableMPLogger(bool state)
{
    priv::MPLogger::instance()->enableLogger(state);
}

mp::priv::MPLogger::MPLogger()
    : isEnabled {true}
    , backup {this->rdbuf()}
{}

mp::priv::MPLogger* mp::priv::MPLogger::instance()
{
    static MPLogger* instance = new MPLogger;
    return instance;
}

void mp::priv::MPLogger::enableLogger(bool state)
{
    if (!(isEnabled = state))
    {
        backup = this->rdbuf(nullptr);
    }
    else
    {
        this->rdbuf(backup);
    }
}

void mp::priv::MPLogger::changeOutput(std::streambuf* buf)
{
    this->rdbuf(buf);
}
