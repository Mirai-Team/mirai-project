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

#ifndef MP_MPLOGGER_HPP
#define MP_MPLOGGER_HPP

#include <iostream>
#include <streambuf>
#include "MiraiProject/util/Logger.hpp"

namespace mp
{

/**
 * @brief Change Mirai Logger output.
 *
 * @param buf : the new output for MP Logger.
 */
void changeMPLoggerOutput(std::streambuf* buf = std::cout.rdbuf());

/**
 * @brief Disable or enable Mirai Project Logger output. (true by default)
 *
 * @param state : false to disable and true to enable.
 */
void enableMPLogger(bool state);

namespace priv
{

class MPLogger : public Logger
{
public:
    static MPLogger& instance();

    // namespace precision is a compulsory here
    friend void mp::changeMPLoggerOutput(std::streambuf*);
    friend void mp::enableMPLogger(bool);

private:
    void enableLogger(bool state);
    void changeOutput(std::streambuf* buf);

    MPLogger();
    MPLogger( const MPLogger& other ) = delete;
    MPLogger& operator=( const MPLogger& ) = delete;

    bool isEnabled;
    std::streambuf* backup;


};

} // priv

} // mp

#endif // MP_MPLOGGER_HPP
