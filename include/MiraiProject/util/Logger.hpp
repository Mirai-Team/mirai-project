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

#ifndef LOGGER_HPP_INCLUDED
#define LOGGER_HPP_INCLUDED

#include <iostream>
#include <fstream>
#include <streambuf>
#include <chrono>
#include <iomanip>

#include "MiraiProject/util/StringUtilities.hpp"

/** @file Logger.hpp
 * \brief This file define Logger class and variables for logging.
 */

namespace mp
{

class Priority
{
    public:
        explicit Priority(std::string priority);

        std::string getPriorityName() const;
    private:
        std::string m_priority;
};

class Logger : public virtual std::ostream
{
    public:
        /**
         * \brief Constructor
         *
         * \param buf : a streambuf where the Logger writes the data.
         */
        explicit Logger(std::streambuf* buf = std::cout.rdbuf());

        /** \brief  For severe logs. */
        const static Priority prioritySevere;

        /** \brief For error logs. */
        const static Priority priorityError;

        /** \brief For warning logs. */
        const static Priority priorityWarning;

        /** \brief For info logs. */
        const static Priority priorityInfo;

        /** \brief For config logs. */
        const static Priority priorityConfig;

        /**
         * \brief Add time to each line.
         *
         * \param data [description]
         */
        template <typename T>
        std::ostream& operator<<(const T& data);

    private:
        void displayPrefix();

        const tm* getLocalTime();

};
}

std::ostream& operator<<(std::ostream& stream, const mp::Priority& priority);

#include "MiraiProject/util/Logger.tpp"

#endif // LOGGER_HPP_INCLUDED
