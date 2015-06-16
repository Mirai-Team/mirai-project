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

#include <iostream>
#include <chrono>
#include <iomanip>

#include "MiraiProject/util/Logger.hpp"

namespace
{
std::ostream& operator<< (std::ostream& stream, const tm* time)
{
    // We write values on two digits.
    return stream << 1900 + time->tm_year << '-'
        << std::setfill('0') << std::setw(2) << time->tm_mon + 1 << '-'
        << std::setfill('0') << std::setw(2) << time->tm_mday << ' '
        << std::setfill('0') << std::setw(2) << time->tm_hour << ':'
        << std::setfill('0') << std::setw(2) << time->tm_min << ':'
        << std::setfill('0') << std::setw(2) << time->tm_sec;
}
}


const mp::Priority mp::Logger::prioritySevere = mp::Priority("SEVERE");
const mp::Priority mp::Logger::priorityError = mp::Priority("ERROR");
const mp::Priority mp::Logger::priorityWarning = mp::Priority("WARNING");
const mp::Priority mp::Logger::priorityInfo = mp::Priority("INFO");
const mp::Priority mp::Logger::priorityConfig = mp::Priority("CONFIG");

mp::Priority::Priority(std::string priority)
    : m_priority(priority)
{
}

std::string mp::Priority::getPriorityName() const
{
    return m_priority;
}
mp::Logger::Logger(std::streambuf* buf)
    : std::ostream(buf)
    , m_displayHeader(true)
{
}

void mp::Logger::displayHeader()
{
    if (m_displayHeader)
        static_cast<std::ostream&>(*this) << "[" << getLocalTime() << "] ";
    m_displayHeader = false;
}

const tm* mp::Logger::getLocalTime()
{
    time_t tt = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    tm *time;
    time = std::localtime(&tt);
    return time;
}

void mp::Logger::endl()
{
    m_displayHeader = true;
}

std::ostream& operator<<(std::ostream& stream, const mp::Priority& priority)
{
    return stream << "["
        << mp::StringUtilities::upper(priority.getPriorityName())
        << "] ";
}

mp::Logger& operator<<(mp::Logger& logger, std::ostream& (*pf)(std::ostream&))
{
    logger.endl();
    static_cast<std::ostream&>(logger) << pf;
    return logger;
}
