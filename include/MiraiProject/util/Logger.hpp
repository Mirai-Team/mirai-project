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

#include <fstream>
#include <memory>
#include <sstream>
#include <string>

#include <boost/thread/mutex.hpp>

#include "MiraiProject/util/LogStream.hpp"

/** @file Logger.hpp
 * \brief This file define Logger class and variables for logging.
 */

namespace mp
{
    class Logstream; // Because Logger use Logstream and Logstream use Logger..

    /** \class Logger
     * \brief Class for logging.
     */

    class Logger
    {
        public:
            /** \brief Constructor
             *
             * \param filename : Path to file.
             */
            Logger(std::string filename);

            /** \brief Deconstructor */
            virtual ~Logger();

            /** \brief Write msg in log file.
             *
             * \param priority : a string which contains Priority name.
             * \param msg : message to write.
             */
            void log(std::string priority, std::string msg);

            /** \brief Operator() with Info Priority.
             *
             * \return a Logstream using Info priority.
             */
            Logstream operator()();

            /** \brief Operator() with string parameter.
             *
             * \param priority : the priority name.
             * 
             * \return a Logstream using the given priority name.
             */
            Logstream operator()(std::string priority);

            /** \brief True to enable logging, false to disable logging. */
            static bool debugMode;

            /** \brief  For severe logs. */
            static const std::string prioritySevere;

            /** \brief For error logs. */
            static const std::string priorityError;

            /** \brief For warning logs. */
            static const std::string priorityWarning;

            /** \brief For info logs. */
            static const std::string priorityInfo;

            /** \brief For config logs. */
            static const std::string priorityConfig;

        private:
            const tm* getLocalTime();

            boost::mutex    mutex_;
            std::ofstream   file_;
            tm              time_;
    };
}

#endif // LOGGER_HPP_INCLUDED